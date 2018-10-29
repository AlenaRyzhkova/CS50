import sys
import crypt

def findPassword(hash, salt, guessPass):
    #   trying for 1-letter key
    for fst in range(ord('A'), ord('z')):
        guessPass=chr(fst)
        tryingHash = crypt.crypt(guessPass,salt)
        if tryingHash == hash:
            print(guessPass)
            return
    #   trying for 2 letters key
    for fst in range(ord('A'), ord('z')):
        for snd in range(ord('A'), ord('z')):
            guessPass=chr(fst)+chr(snd)
            tryingHash = crypt.crypt(guessPass,salt)
            if tryingHash == hash:
                print(guessPass)
                return
    #   trying for 3 letters key
    for fst in range(ord('A'), ord('z')):
        for snd in range(ord('A'), ord('z')):
            for thd in range(ord('A'), ord('z')):
                guessPass=chr(fst)+chr(snd)+chr(thd)
                tryingHash = crypt.crypt(guessPass,salt)
                if tryingHash == hash:
                    print(guessPass)
                    return
    #   trying for 4 letters key
    for fst in range(ord('A'), ord('z')):
        for snd in range(ord('A'), ord('z')):
            for thd in range(ord('A'), ord('z')):
                for fth in range(ord('A'), ord('z')):
                    guessPass = chr(fst) + chr(snd) + chr(thd) + chr(fth)
                    tryingHash = crypt.crypt(guessPass,salt)
                    if tryingHash == hash:
                        print(guessPass)
                        return

# get the hashed password
if not len(sys.argv) == 2:
    print("Usage: python crack.py <hash>")
    sys.exit(1)
hash = sys.argv[1]
salt = hash[0:2]

# crack the password
guessPass=""
findPassword(hash, salt, guessPass)

