#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int child_pid = fork();
    if (child_pid > 0){
      sleep(3);
        printf("\nparent did something");
    }    
    else{
      printf("child doing something");
        exit(0);
    }    
        
    return 0;
}