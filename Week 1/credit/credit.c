#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long num;
    int dig = 0;
    long temp;
    int temp1 = 10;
    int sum1 = 0;
    int sum2 = 0;
    int temp2 = 0;
    do
    {
        num = get_long("Number: ");
    }
    while(num<1);

    temp = num;

    while(temp > 0)
    {
        dig++;
        temp /= 10;
    }
    temp = num;

    while(temp>0){
        temp1 =temp%10;
        temp/=10;
        sum1+=temp1;

        temp2 = temp % 10;
        temp /= 10;
        temp2 *= 2;
        int d1 = temp2 % 10;
        int d2 = temp2 / 10;
        sum2 = sum2 + d1 + d2;
    }
    int total = sum1 + sum2;

    long start = num;
    do
    {
        start = start / 10;
    }
    while (start > 100);






    if (total % 10 != 0 ||(dig != 13 && dig != 15 && dig != 16))
    {
        printf("INVALID\n");
    }
    else if ((start / 10 == 5) && (0 < start % 10 && start % 10 < 6))
    {
        printf("MASTERCARD\n");
    }
     else if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (start / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    }



