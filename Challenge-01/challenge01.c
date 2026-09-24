// calculating avg,percentage,toatal of 5 students
#include <stdio.h>
int main()
{
  int eng,math,sci,soc,hin;
float totalmarks,avg,percentage;

printf("enter the students eng marks:");
scanf("%d",&eng);
printf("ENGLISH marks:  %d",eng);

printf("enter the students math marks:");
scanf("%d",&math);
printf("MATH marks:  %d",math);

printf("enter the students science marks:");
scanf("%d",&sci);
printf("SCIENCE marks:  %d",sci);

printf("enter the students social marks:");
scanf("%d",&soc);
printf("SOCIAL marks:  %d",soc);

printf("enter the students hindi marks:");
scanf("%d",&hin);
printf("HINDI marks:  %d",hin);

totalmarks=eng+math+sci+soc+hin;
printf("total marks obtained by the student :   %f",totalmarks);

avgmarks=totalmarks/5;
printf("average marks :  %f",avgmarks);

percentage=(totalmarks/500)*100;
printf("percentage :  %f",percentage);
return 0;
}
