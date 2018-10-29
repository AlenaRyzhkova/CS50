from cs50 import get_int

# Ask for user input and validate it
while True:
    x = get_int("Enter positive integer: ")
    if x>0:
        break

# Draw the pyramid
for r in range(x):
    # print left pyramid
    print(" "*(x-r-1), end="")
    print("#"*(r+1),end="")
    # print gap
    print(" "*2, end="")
    # print right pyramid
    print("#"*(r+1),end="")
    print()