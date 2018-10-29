import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Retrieve data from database
    stocks = db.execute("SELECT stockSymbol, SUM(numShares) AS numberShares FROM transactions GROUP BY stockSymbol HAVING user_id=:user_id", user_id=session["user_id"])
    # Add current information using lookup
    stTotalValue = 0.0
    for stock in stocks:
        quoteInfo = lookup(stock["stockSymbol"])
        stock["company"] = quoteInfo["name"]
        stock["currentPrice"] = quoteInfo["price"]
        stock["totalValue"] = stock["currentPrice"]*stock["numberShares"]
        stTotalValue += stock["totalValue"]

    cash = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])

    return render_template("index.html", stocks=stocks, stTotalValue=stTotalValue, cash=cash[0]["cash"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol and quantaty was submitted
        if not request.form.get("symbol"):
            return apology("must provide Symbol of stock's quote", 403)
        if not request.form.get("shares"):
            return apology("must provide number of stocks", 403)

        stockSymbol = request.form.get("symbol")
        numShares = int(request.form.get("shares"))

        # Ensure number of stocks was possitive numers
        if numShares<0:
            return apology("must provide positive number of stocks", 400)

        # Query database for user's cash
        rows = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=session["user_id"])
        quoteInf = lookup(stockSymbol)
        priceByShare = quoteInf['price']
        sumPurchase = numShares*priceByShare
        if rows[0]["cash"]< sumPurchase:
            return apology("you don't have enougth money", 400)

        # Add information about purchase into database
        db.execute("INSERT INTO transactions (user_id, stockSymbol, numShares, priceByShare) VALUES(:user_id,:stockSymbol,:numShares,:priceByShare)",
        user_id=session["user_id"],stockSymbol=stockSymbol,numShares=numShares,priceByShare=priceByShare)

        # Update cash value after purchase
        db.execute("UPDATE users SET cash = cash - :sumPurchase WHERE id= :id", sumPurchase=sumPurchase, id = session["user_id"])
        return render_template("buy_success.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    trans = db.execute("SELECT * FROM transactions WHERE user_id= :user_id", user_id=session["user_id"])
    for tran in trans:
        if tran["numShares"]<0:
            tran["typeOperation"]="Selling"
        else:
            tran["typeOperation"]="Purchase"

    return render_template("history.html", trans=trans)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol of stock", 403)

        quoteInf = lookup(request.form.get("symbol"))
        if not quoteInf:
            return apology("quote not found, check the spelling of symbol", 400)
        return render_template("quoted.html",name = quoteInf['name'], price = quoteInf['price'], symbol = quoteInf['symbol'])

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 403)

        # Ensure password and confirmation is equal
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("password confirmation does not match", 403)

        # Add user into database for username
        new_user_id = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                          username=request.form.get("username"),
                          hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8))

        # Ensure username wasn't in the database
        if not new_user_id:
            return apology("This username is already exists", 406)

        # Logging automatically
        session["user_id"]=new_user_id

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure symbol's chosen
        if not request.form.get("symbol"):
            return apology("must provide Symbol of stock's quote", 403)
        if not request.form.get("shares"):
            return apology("must provide number of stocks", 403)

        stockSymbolCh = request.form["symbol"]
        numShares = int(request.form.get("shares"))

        # Ensure number of stocks was possitive numers
        if numShares<0:
            return apology("must provide positive number of stocks", 400)

        # Ensure user have enough shares
        quotesPortfolio = db.execute("SELECT stockSymbol, SUM(numShares) AS numSharesAvaible FROM transactions GROUP BY stockSymbol HAVING user_id=:user_id AND stockSymbol=:stockSymbol",
        user_id=session["user_id"], stockSymbol=stockSymbolCh)

        if numShares>quotesPortfolio[0]["numSharesAvaible"]:
            return apology("you don't have enought shares", 400)

        quoteInf = lookup(stockSymbolCh)
        priceByShare = quoteInf['price']
        sumSales = numShares*priceByShare

        # Add information about selling into database
        db.execute("INSERT INTO transactions (user_id, stockSymbol, numShares, priceByShare) VALUES(:user_id,:stockSymbol,:numShares,:priceByShare)",
        user_id=session["user_id"],stockSymbol=stockSymbolCh,numShares=-numShares,priceByShare=priceByShare)

        # Update cash value after purchase
        db.execute("UPDATE users SET cash = cash + :sumSales WHERE id= :id", sumSales=sumSales, id = session["user_id"])

        return render_template("sell_success.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        quotesPortfolio = db.execute("SELECT stockSymbol, SUM(numShares) AS numberShares FROM transactions GROUP BY stockSymbol HAVING user_id=:user_id", user_id=session["user_id"])
        return render_template("sell.html", quotesPortfolio=quotesPortfolio)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
