#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define N 5

sem_t entering_diners, exiting_diners;
sem_t enter_done, exit_done;
sem_t mutex_enter, mutex_exit;

int count_enter = 0, count_exit = 0;
int i = 0, j = 0;

void enterRestaurant()
{
    printf("Diners are entering the restaurant NOW.\n");
    sem_wait(&mutex_enter);
    
    printf("\n %dth ",count_enter);
    count_enter++;
    if (count_enter == N)
    {
        sem_post(&enter_done);
        count_enter = 0;
    }
    sem_post(&mutex_enter);

    sem_post(&entering_diners);
}

void eat(){
  printf("Diner is eating Food.\n"); 
}

void exitRestaurant()
{
    printf("Diners are exiting the restaurant.\n");
    sem_wait(&mutex_exit);
    count_exit++;
    if (count_exit == N)
    {
        sem_post(&exit_done);
        count_exit = 0;
    }

    sem_post(&mutex_exit);
    sem_post(&exiting_diners);
}

void openFrontDoor()
{
    printf("We are opening the Front Doors :\n");
    printf("Only %d diners can come in\n", N);
}

void closeFrontDoor(){
  printf("All %d diners have entered.\n", N); }

void serveFood()
{
    printf("We are ready to serve Food.\n");
    sem_post(&entering_diners);
    sem_wait(&exiting_diners);
}

void openBackDoor(){
  printf("Back door is Open.\n"); 
}

void closeBackDoor(){
    printf("Closing Back door Now.\n");
    sem_wait(&exit_done);
}
void *diner(void *args)
{
    while (j < 5)
    {
        enterRestaurant();
        eat();
        exitRestaurant();
        j++;
    }
}

void *restaurant(void *args)
{
    while (i < 5)
    {
        openFrontDoor();
        closeFrontDoor();
        serveFood();
        enterRestaurant();
        eat();
        exitRestaurant();
        openBackDoor();
        closeBackDoor();
        i++;
    }
}



int main()
{
    sem_init(&entering_diners, 0, 0);
    sem_init(&exiting_diners, 0, 0);
    sem_init(&enter_done, 0, 0);
    sem_init(&exit_done, 0, 0);
    sem_init(&mutex_enter, 0, 1);
    sem_init(&mutex_exit, 0, 1);

    pthread_t thread_diner, thread_restaurant;

    pthread_create(&thread_restaurant, NULL, restaurant, NULL);
    pthread_create(&thread_diner, NULL, diner, NULL);

    pthread_join(thread_restaurant, NULL);
    pthread_join(thread_diner, NULL);
}