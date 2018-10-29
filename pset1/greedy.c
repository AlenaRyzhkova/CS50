#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Promt user for an amount of chanage and validate it
    float a=0;
    do
    {
        a = get_float("Please enter the change amount, it shoould be positeve value in format 0.XX: ");
    }while(a<=0);

    // Convert dollars ($) into cents (c)
    int n = (int)round(a*100);

    int quarters=0, dimes=0, nickels=0, pennies=0;
    quarters = n/25;
    dimes = (n%25)/10;
    nickels = ((n%25)%10)/5;
    pennies = ((n%25)%10)%5;

    printf("Greedy cashier have used %i coins.\n", quarters + dimes + nickels + pennies);

}