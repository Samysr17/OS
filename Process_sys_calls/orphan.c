#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
printf("\nBefore");

int p;
p=fork();
  // printf("\nBefore");
if(p==0){
  printf("\nchild does something\n");
  sleep(2);
  printf("\nchild did after parent executed");
}
else{
  printf("\nparent completes");
}
  printf("\nAfter");
return 0;
}