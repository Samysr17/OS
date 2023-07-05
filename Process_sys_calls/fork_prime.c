#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
int pid,n,a[10],i,t,j,flag=0;
pid=fork();
printf("Pid=%d\n",pid);
if(pid==0)
{
printf("Enter a number to check whether prime or not:");
scanf("%d",&n);
if(n==1)
{
printf("number is prime");
}
else
for(j=2;j<=(n/2);j++)
{
if(n%j==0)
{
flag=1;
printf(";not a prime number");
break;
}
}
if(flag==0)
printf("\nprime number");
}
else
{
sleep(5);
printf("\nenter 10 numbers to sort");
for(j=0;j<10;j++)
scanf(";%d",&a[j]);
for(i=0;i<9;i++)
{
for(j=0;j<9-i;j++)
{
if(a[j+1]<a[j])
{
t=a[j];
a[j]=a[j+1];
a[j+1]=t;
}
}
}
printf(";sorted element:\n");
for(i=0;i<10;i++)
printf(";%d ",a[i]);
} return 0;
}