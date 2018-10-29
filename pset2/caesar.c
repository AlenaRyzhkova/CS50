#include<stdio.h>
#include<ctype.h>
#include<cs50.h>
#include<string.h>

char ceaserEncryptCh(char chPl, int key);

int main(int argc, string argv[])
{
    int key = 0;

    // 1. parse command lines argument, convert string key to int
    if(argc<2)
    {
        printf("Usage: ./caesar [key]\n");
        return 1;
    }
    key = atoi(argv[1]);

    // 2. get plain text from user
    string plaintext = get_string("Please, enter a text for encryption: ");
    printf("Plaintext: %s\n",plaintext);

    // 3. encipher plain text
    char ciphertext[strlen(plaintext)];
    for(int i=0; i< strlen(plaintext); i++)
        ciphertext[i] = ceaserEncryptCh(plaintext[i], key);

    // 4. print enciphered text
    printf("Ciphertext: %s\n",ciphertext);
}


char ceaserEncryptCh(char chPl, int key)
{
    if(isalpha(chPl))
    {
        if(isupper(chPl))
            return (chPl -'A'+key)%26+'A';
        else
            return (chPl-'a'+key)%26+'a';
    }
       return chPl;
}