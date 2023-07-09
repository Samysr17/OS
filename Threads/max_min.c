#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
  int flag=0;
int MAX=-999;
int MIN=999;
int a[1000];
int max=0;
int min=0;
void *max_min(void *args){
  for(int i=0;i<1000;i++){
    if(a[i]>MAX){
      if(a[i]>max)
      max=a[i];
    }if(a[i]<min){
      if(a[i]<min)
      min=a[i];
    }
  }
}

int main(){
pthread_t t[1000];
for (int i = 0; i < 1000; i++)
{
a[i] = rand() % 1000;
}
for (int i = 0; i < 1000; i++)
{
pthread_create(&t[i], NULL,max_min, i);
}
for (int i = 0; i < 1000; i++){
  pthread_join(t[i], NULL);
}
printf("Maximum Number of the array is %d\n", max);
printf("Minimum Number of the array is %d\n", min);

  return 0;
}