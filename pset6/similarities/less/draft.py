from nltk.tokenize import sent_tokenize

def getSubs(str, n):
    ss = set()
    for i in range(len(str)-n):
        ss.add(str[i:i+n])
    return ss

str1 = "I feel it in my fingers. I feel it in my toes! Christmas is all around me, and so the feeling grows... It's written in the wind. It's everywhere I go, So if you really love Christmas, C'mon and let it snow? I feel it in my toes!"
str2 = "I feel it in my fingers. I feel it in my toes! Christmas is all around me,"

s1=getSubs(str1, 5)
s2=getSubs(str2, 5)
print(list(s1&s2))

