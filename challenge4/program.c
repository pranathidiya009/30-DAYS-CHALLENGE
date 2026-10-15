//Looplab
#include <stdio.h>
int main()
{
float amount;
float smalltotal=0,mediumtotal=0,largetotal=0;
int scount=0,mcount=0,lcount=0;
printf("enter the value  of amount:\n");
scanf("%f",&amount);
while(amount!=0)
{
if(amount<0)
{
printf("entered num is negative\n");
}
else if(amount<100)
{
scount++;
smalltotal=smalltotal+amount;
}
else if (amount<500)
{
mcount++;
mediumtotal=mediumtotal+amount;
}
else if(amount>500)
{
lcount++;
largetotal=largetotal+amount;
}
printf("enter the value of amount\n");
scanf("%f",&amount);
}
printf("--------EXPENSE SUMMARY--------\n");

printf("small count is:%d\n",scount);
printf("smalltotal is : %.2f\n",smalltotal);

printf("medium count is:%d\n",mcount);
printf("medium total is:%.2f\n",mediumtotal);

printf("large count is :%d\n",lcount);
printf("large total is:%.2f\n",largetotal);

return 0;
}
