#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

sem_t hydrogen_sem;
sem_t oxygen_sem;
sem_t mutex;
sem_t mutex_o;
int hydrogen_count = 0, oxygen_count = 0;

void *hydrogen_thread(void *arg) {
  sem_wait(&mutex); 
  hydrogen_count++; 
  if (hydrogen_count >= 2 && oxygen_count >= 1) {
    sem_post(&hydrogen_sem); 
    sem_post(&hydrogen_sem);
    sem_post(&oxygen_sem);    
    hydrogen_count -= 2;     
    oxygen_count--;           
    printf("Thread made of hydrogen: Received oxygen. Bonding took place.\n");
  } else {
    sem_post(&mutex);  
    printf("Thread made of hydrogen: Waiting for oxygen...\n");
    sem_wait(&hydrogen_sem);  
  }

  pthread_exit(NULL);
}

void *oxygen_thread(void *arg) {
  sem_wait(&mutex_o);  
  oxygen_count++;
  hydrogen_count+=2;
  if (hydrogen_count%2==0 && oxygen_count >= 1) {
    sem_post(&hydrogen_sem);  
    sem_post(&hydrogen_sem);
    sem_post(&oxygen_sem);      
    oxygen_count--;           
    printf("Thread made of oxygen: Received two hydrogens. Bonding took place.\n");
  } else {
    sem_post(&mutex_o); 
    printf("Thread made of oxygen: Waiting for two hydrogens...\n");
    sem_wait(&oxygen_sem); 
  }

  pthread_exit(NULL);
}

int main() {
  pthread_t threads[31]; 
  int inp=0;

  sem_init(&hydrogen_sem, 0, 0);
  sem_init(&oxygen_sem, 0, 0);   
  sem_init(&mutex, 0, 1); 
  sem_init(&mutex_o, 0, 1); 

  while(1){
    printf("Enter 1 for H bonding and  O bonding and anything for No bonding\n");
    scanf("%d",&inp);
    if(inp==1){
       for (int i = 0; i < 4; i+=2) {
      pthread_create(&threads[i], NULL, oxygen_thread, NULL);
      pthread_create(&threads[i+1], NULL, hydrogen_thread, NULL);
      pthread_create(&threads[i+2], NULL, hydrogen_thread, NULL);
  }
  for (int i = 0; i < 30; i++) {
    pthread_join(threads[i], NULL); 
  } 
    
    }else{
        for (int i = 0; i < 4; i++) {
      pthread_create(&threads[i], NULL, hydrogen_thread, NULL);

    }
     for (int i = 0; i < 30; i++) {
    pthread_join(threads[i], NULL); 
  } 
    }
  }

  // sem_destroy(&hydrogen_sem);  
  // sem_destroy(&oxygen_sem);    
  // sem_destroy(&mutex);         

  return 0;
}