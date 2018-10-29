#include <cs50.h>
#include <stdio.h>

bool checksumValid(int checksum);
int checksumCalc(long long num);
int digit(long long num, int i);
long long power(int p, int q);
bool bankLengthValid(long long num);
int lenghtNum(long long num);


int main(void)
{
    long long n = get_long_long("Please, enter your credit card number: ");
    while(n<=0 || !checksumValid(checksumCalc(n)) || !bankLengthValid(n))
    {
        printf("Your credit card number is not valid...");
        n = get_long_long("Retry: ");
    }
    printf("Your credit card number is valid! Thank you!\n");
}

bool checksumValid(int checksum)
{
    if (digit(checksum,0) ==0)
        return true;
    else
        return false;
}

int checksumCalc(long long num)
{
    int res = 0;
    for(int i=0; num>power(10,i); i++)
    {
        if (i%2==0)
            res += digit(num, i);
        else
            res += (2*digit(num,i)/10) + (2*digit(num,i)%10);
    }
    return res;
}

int digit(long long num, int i)
{
    if(num>power(10,i))
    {
        return (num%power(10,i+1)-num%power(10,i))/power(10,i);
    }
    else
        return 0;
}

long long power(int p, int q)
{
    long long res = 1;
    for(int i = 0; i<q; i++)
    {
        res *= p;
    }
    return res;
}

bool bankLengthValid(long long num)
{
    switch(lenghtNum(num))
    {
        case 15:
            if((digit(num,14)==3) && (digit(num,13)==4 || digit(num,13)==7))
                return true;
            else
                return false;
        case 13:
            if(digit(num,12)==4)
                return true;
            else
                return false;
        case 16:
            if(digit(num,15)==4)
                return true;
            else if(digit(num,15)==5 && (digit(num,14)>0 && digit(num,14)<6))
                return true;
            else
                return false;
        default:
            return false;
    }
}

int lenghtNum(long long num)
{
    int i;
    for(i=0; num>power(10,i); i++);
    return i;
}

