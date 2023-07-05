#include<stdio.h>
#include<unistd.h>
int main(){
  int p;
  p=fork();
  if(p==0){
    printf("Child \n");
    printf("ID: %d\n",getpid());
    printf("Parent ID: %d\n",getppid());
  }else if(p>0){
    printf("Parent Process \n");
    printf("ID: %d",getpid());
  }else{
    printf("Error in fork");
  }
  return 0;
}