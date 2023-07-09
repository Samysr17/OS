#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int g=0;

void* thread(void* args){
  int thread_id=(int)args;
  static int s=0;
  s++;
  g++;
  printf("thread id: %d  %d   %s",thread_id,s,g);
}
int main()
{
  pthread_t basic;
  for(int i=0;i<3;i++){
     pthread_create(&basic,thread,NULL,(void*)i); 
  }
  pthread_exit(NULL);
  
   return 0;
}