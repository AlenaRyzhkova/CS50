from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    setAL = set(a.splitlines())
    setBL= set(b.splitlines())
    return list(setAL&setBL)


def sentences(a, b):
    """Return sentences in both a and b"""
    setAS=set(sent_tokenize(a))
    setBS=set(sent_tokenize(b))
    return list(setAS&setBS)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    setASb=getSubs(a,n)
    setBSb=getSubs(b,n)
    return list(setASb&setBSb)


def getSubs(str, n):
    ss = set()
    for i in range(len(str)-n):
        ss.add(str[i:i+n])
    return ss