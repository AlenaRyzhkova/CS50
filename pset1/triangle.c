#include<cs50.h>
#include <stdio.h>

bool valid_triangle(float a,float b,float c);

int main(void)
{
    float a = get_float("Enter 1-st triangle side: ");
    float b= get_float("The 2-nd one: ");
    float c= get_float("The 3-d one: ");

    if(valid_triangle(a,b,c))
        printf("The triangle's sides is ok :)\n");
    else
        printf("It's not really triangle :(\n");

}

bool valid_triangle(float a,float b,float c)
{
    if(a<=0 || b<=0 || c<=0)
        return false;

    if((a+b)<c || (a+c)<b || (b+c)<a)
        return false;

    return true;
}