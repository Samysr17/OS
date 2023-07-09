#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
  int flag=0;
void *linear_search(void *args){
  int a[10]={1,2,3,4,5,6,7,8,9,10};
  int target=2;
  for(int i=0;i<10;i++){
    if(a[i]==target){
      flag=1;
    }
  }
}

int main(){
  pthread_t thread[10];
  for(int i=0;i<10;i++){
    pthread_create(&thread[i],NULL,linear_search,(void*)i);
  }
  for(int i=0;i<10;i++){
    pthread_join(thread[i],NULL);
  }
  if(flag==1)printf("element found");
  else printf("not found");
  return 0;
}