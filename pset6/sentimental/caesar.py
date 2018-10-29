from cs50 import get_string
import sys

# 1. get the key
if not len(sys.argv)==2:
    print("Usage: python caesar.py <key>")
    sys.exit(1)
key = int(sys.argv[1])

# 2. get plain text
plaintext = get_string("Please, enter a text for encryption: ")
print("Plaintext: " + plaintext)

# 3. encipter
ciphertext=""
for c in plaintext:
    if c.isalpha()==True:
        if c.isupper()==True:
            p = chr((ord(c) - ord('A') + key)%26 + ord('A'))
        else:
            p = chr((ord(c) - ord('a') + key)%26 + ord('a'))
    else:
        p=c
    ciphertext+=p
print()

# 4. print ciphertext
print("Ciphertext: " + ciphertext)