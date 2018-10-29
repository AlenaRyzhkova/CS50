#include<stdio.h>
#include<ctype.h>
#include<cs50.h>
#include<string.h>

bool checkArgsLenght(int argsReq, int argc, string msg);
char ceaserEncryptCh(char chPl, int key);

int main(int argc, string argv[])
{
    // 1. get the key = parse command lines argument
        //check that user types key phrase
    if(!checkArgsLenght(2,argc,"Usage: ./vigenere [key_phrase]"))
        return 1;
    string key = argv[1];
        //check that key phrase is alphabatical
    for(int i=0; i<strlen(key);i++)
        if(!isalpha(key[i]))
        {
            printf("Usage: ./vigenere [key_phrase]\nThe key_phrase must consist only of letters.\n");
            return 1;
        }

    // 2. get plain text from user
    string plaintext = get_string("Please, enter a text for encryption: ");
    printf("Plaintext: %s\n",plaintext);

    // 3. encipher plain text
    char ciphertext[strlen(plaintext)];
    int j=-1;   //index of key letter
    for(int i=0; i<strlen(plaintext);i++)   //loop for plaintext letters
    {
        //incremetnt key_phrase index only for alpabatical symbols in plaintext
        if(isalpha(plaintext[i]))
            j=(j+1)%strlen(key);

        if(isupper(key[j]))
            ciphertext[i] = ceaserEncryptCh(plaintext[i], key[j]-'A');
        else
            ciphertext[i] = ceaserEncryptCh(plaintext[i], key[j]-'a');
    }

    // 4. print enciphered text
    printf("Ciphertext: %s\n",ciphertext);
}



char ceaserEncryptCh(char chPl, int key)
{
    if(isalpha(chPl))
        {
            if(isupper(chPl))
                return (chPl-'A'+key)%26+'A';
            else
                return (chPl-'a'+key)%26+'a';
        }
        else
            return chPl;

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