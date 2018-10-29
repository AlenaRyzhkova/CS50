import cs50
import re
from model import distance
from flask import Flask, abort, redirect, render_template, request
from html import escape
from werkzeug.exceptions import default_exceptions, HTTPException

# Web app
app = Flask(__name__)

@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
def index():
    """Handle requests for / via GET (and POST)"""
    return render_template("index.html")

@app.route("/score", methods=["POST"])
def score():
    """Handle requests for /score via POST"""

    # Read strings
    s1 = request.form.get("str1")
    s2 = request.form.get("str2")
    if not s1 or not s2:
        abort(400, "missing strings")

    # Calculate distance
    matrix = distance(s1,s2)

    # Extract operations from table
    operations = []
    i = len(s1)
    j = len(s2)
    while True:
        _,operation = matrix[i][j]
        if not operation:
            break
        if operation == Operation.INSERTED:
            j -= 1
        elif operation == Operation.DELETED:
            i -= 1
        else:
            i -= 1
            j -= 1
        operations.append(operation)
    operations.reverse()

    # Maintain list of intermediate strings, operation and description
    transistions = [(s1, None, None)]
    i=0

    # Apply each operation
    prev = s1
    for operation in operations:
        # Update sting and description of operation
        if operation == Operation.INSERTED:
            s = (prev[:i],s2[i],prev[i:])
            description = f"inserted '{s2[i]}'"
            prev = prev[:i] + s2[i] + prev[i:]
            i += 1
        elif operation == Operation.DELETED:
            s = (prev[:i],prev[i], prev[i+1:])
            description = f"deleted '{prev[i]}'"
            prev = prev[:i] + prev[i+1:]
        elif prev[i]!=s2[i]:
            s = (prev[:i],s2[i],prev[i+1:])
            description = f"substituted '{prev[i]}' with '{s2[i]}'"
            prev = prev[:i] + s2[i] + prev[i+1:]
            i  += 1
        else:
            i += 1
            continue
        transistions.append((s, str(operation), description))
    transistions.append((s2, None, None))

    # Output comparison
    return render_template("score.html", matrix=matrix, s1=s1, s2=s2, operations=transistions)

@app.errorhandler(HTTPException)
def errorhandler(error):
    """Handle errors"""
    return render_template("error.html", error=error)


# https://github.com/pallets/flask/pull/2314
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)