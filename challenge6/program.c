//pattern identifier.. challenge 6
#include <stdio.h>
int main()
{
int a[12];
int n,i,k;
int r=0;

//reading input
printf("enter n ");
scanf("%d",&n);
while(n<5 || n>12)
{
printf("invalid value for n,enter again");
scanf("%d",&n);
}

for (i=0;i<n;i++)
{
printf("enter reading %d\n",i+1);
scanf("%d",&a[i]);
while(a[i]<0 || a[i]>1000)
{
printf("invalid readinng,enter again:%d\n",i+1);
scanf("%d",&a[i]);
}
}

//display
printf("original values:\n");
for(i=0;i<n;i++)
{
printf("%d\n",a[i]);
}

//task-1 (sum,avg,min,max)
int sum=0;
int min=a[0],max=a[0];
for(i=0;i<n;i++)
{
sum=sum+a[i];
if(a[i]<min)
min=a[i];
if(a[i]>max)
max=a[i];
}
printf("sum= %d\n",sum);
printf("average=%d\n",sum/n);
printf("min=%d\n",min);
printf("max=%d\n",max);

//task-2 (longest run)
int run=1,longest=1;
for(i=1;i<n;i++)
{
if(a[i]>a[i-1])
run++;
else
run=1;
if(run>longest)
longest=run;
}
printf("longest run =%d\n",longest);

//task-3 divisor
int d=(r%9)+1;
int count=0;
for(i=0;i<n;i++)
{
if(a[i]%d==0)
count++;
}
printf("d=%d,div count=%d\n",d,count);

return 0;
}
