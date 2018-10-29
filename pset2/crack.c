#define _XOPEN_SOURCE

#include<stdio.h>
#include<ctype.h>
#include <unistd.h>
#include<cs50.h>
#include<string.h>
#include <stdlib.h>

bool checkArgsLenght(int argsReq, int argc, string msg);
string findPassword(string hash, string salt);

int main(int argc, string argv[])
{
    // get the hashed password
    if(!checkArgsLenght(2, argc, "Usage: ./crack hash"))
        return 1;

    // crack the password
    string hash = argv[1];
    char salt[2] = {hash[0],hash[1]};
    printf("I guess you password is %s\n",findPassword(hash,salt));

}

bool checkArgsLenght(int argsReq, int argc, string msg)
{
    if(argc<argsReq)
    {
        printf("%s\n",msg);
        return false;
    }
    return true;
}

string findPassword(string hash, string salt)
{
    string tryingHash;
    char* guessKey = (char*) malloc(5*sizeof(char));

    //Trying for 1-letter key
    for(char fst='A'; fst<='z'; fst++)
    {
        guessKey[0] = fst;
        guessKey[1] = '\0';
        tryingHash = crypt(guessKey, salt);
        if(strcmp(hash, tryingHash)==0)
            return guessKey;
    }

    //Trying for 2-letters key
    for(char fst='A'; fst<='z'; fst++)
        for(char snd='A'; snd<='z'; snd++)
        {
            guessKey[0] = fst;
            guessKey[1] = snd;
            guessKey[2] = '\0';
            tryingHash = crypt(guessKey, salt);
            if(strcmp(hash, tryingHash)==0)
                return guessKey;
        }

    //Trying for 3-letters key
    for(char fst='A'; fst<='z'; fst++)
        for(char snd='A'; snd<='z'; snd++)
            for(char thd='A'; thd<='z'; thd++)
            {
                guessKey[0] = fst;
                guessKey[1] = snd;
                guessKey[2] = thd;
                guessKey[3] = '\0';
                tryingHash = crypt(guessKey, salt);
                if(strcmp(hash, tryingHash)==0)
                    return guessKey;
            }
    //Trying for 4-letters key
    for(char fst='A'; fst<='z'; fst++)
        for(char snd='A'; snd<='z'; snd++)
            for(char thd='A'; thd<='z'; thd++)
            for(char fth='A'; fth<='z'; fth++)
            {
                guessKey[0] = fst;
                guessKey[1] = snd;
                guessKey[2] = thd;
                guessKey[3] = fth;
                guessKey[4] = '\0';
                tryingHash = crypt(guessKey, salt);
                if(strcmp(hash, tryingHash)==0)
                    return guessKey;
            }
    return NULL;
}