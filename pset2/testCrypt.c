#define _XOPEN_SOURCE

#include<stdio.h>
#include <unistd.h>
#include<cs50.h>

int main(void)
{
    string passOrigin =  get_string("Enter you password: ");
    string sold = "hi";
    string hash = crypt(passOrigin, sold);
    printf("Your hash: %s\n", hash);
}