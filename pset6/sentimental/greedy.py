from cs50 import get_float

# Promt user input and validate it
while True:
    x = get_float("Please enter the change amount, in format 0.XX: ");
    if x>0:
        break

# Convert dollars ($) to cent
n = round(x*100)

# Always use the largest coin possible
quarters = n//25
dimes = (n%25)//10
nickels = ((n%25)%10)//5
pennies = ((n%25)%10)%5

# Print result
print("Greedy cashier have used ", end="")
print(quarters + dimes + nickels + pennies)