#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
   int status=1;
   int p=vfork(); //fork()
  int i;
   if(p==0){
      printf("\n child process");
     for( i=0;i<5;i++){
       printf(" %d ",i);
       _exit(status);
     }
   }else if(p>0){
      printf("\n parent process");
     for( i=0;i<5;i++){
       printf(" %d ",i);
     }
   }else{
     printf("error");
   }  
    return 0;
}

//fork prints  both iterations but vfork only does parent iteration because of shared memory of vfork