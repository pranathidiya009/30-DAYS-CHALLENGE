// calculating avg,percentage,toatal of 5 students marks
#include <stdio.h>
int main()
{
  int eng,math,sci,soc,hin;
float totalmarks,avgmarks,percentage;

printf("enter the students eng marks:");
scanf("%d",&eng);
printf("ENGLISH marks:  %d\n",eng);

printf(" enter the students math marks:");
scanf("%d",&math);
printf("MATH marks:  %d\n",math);

printf("enter the students science marks:");
scanf("%d",&sci);
printf("SCIENCE marks:  %d\n",sci);

printf("enter the students social marks:");
scanf("%d",&soc);
printf("SOCIAL marks:  %d\n",soc);

printf(" enter the students hindi marks: ");
scanf("%d",&hin);
printf("HINDI marks:  %d\n",hin);

totalmarks=eng+math+sci+soc+hin;
printf(" total marks obtained by the student :   %f\n",totalmarks);

avgmarks=totalmarks/5;
printf("average marks :  %f\n",avgmarks);

percentage=(totalmarks/500)*100;
printf("percentage :  %f\n",percentage);
return 0;
}
