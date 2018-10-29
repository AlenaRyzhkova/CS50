from cs50 import get_string
import sys

# 1. Get the key = parse command lines argument
#   check check that user types key phrase
if not len(sys.argv) == 2:
    print("Usage: python vigenere.py <key_phrase>")
    sys.exit(1)
key=sys.argv[1]

#   check that key phrase is alphabatical
if key.isalpha() == False:
    print("The key_phrase must consist only of letters")
    sys.exit(1)

# 2. Get the plaintext
plaintext = get_string("Please, enter a text for encryption: ")
print("Plaintext: " + plaintext)

# 3. Encipcher
ciphertext=""
j=-1
for c in plaintext:
    if c.isalpha() == True:
        j = (j+1)%len(key)
        if key[j].isupper() == True:
            k = ord(key[j])-ord('A')
        else:
            k =ord(key[j])-ord('a')

        if c.isupper() == True:
            p = chr((ord(c) - ord('A') + k)%26 + ord('A'))
        else:
            p = chr((ord(c) - ord('a') + k)%26 + ord('a'))
    else:
        p = c
    ciphertext+=p

# 4. Print enciphered text
print("Ciphertext: " + ciphertext)