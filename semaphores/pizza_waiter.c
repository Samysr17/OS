#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_PIZZA 3
int shelf = 0;
sem_t mutex;
void *cook(void *arg)
{
while (1)
{
if (shelf < MAX_PIZZA)
{
sem_wait(&mutex);
shelf++;
printf("Cook: Cooked a pizza, there are %d pizzas now.\n", shelf);
sem_post(&mutex);
}
sleep(1);
}
}
void *waiter(void *arg)
{
while (1)
{
if (shelf > 0)
{
sem_wait(&mutex);
printf("Waiter: I picked up a pizza\n");
shelf--;
sem_post(&mutex);
}
sleep(2);
}
}
int main()
{
pthread_t Tcook, Twaiter;
sem_init(&mutex, 0, 1);
printf("Cook: I have started cooking pizza.\n");
pthread_create(&Tcook, NULL, cook, NULL);
pthread_create(&Twaiter, NULL, waiter, NULL);
pthread_join(Tcook, NULL);
pthread_join(Twaiter, NULL);
return 0;
}
