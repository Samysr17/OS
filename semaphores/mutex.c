#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
int *a;
sem_t mutex;
int main()
{
sem_init(&mutex, 0, 1);
int shmid;
shmid = shmget(IPC_PRIVATE, 2 * sizeof(int), 0777 | IPC_CREAT);
a = (int *)shmat(shmid, NULL, 0);
*a = 0;
pid_t pid;
pid = fork();
if (pid == -1)
{
printf("Error !!\n");
}
else if (pid == 0)
{
// Child Process
printf("This is the Child Process.\n");
for (int i = 0; i < 10; i++)
{
sem_wait(&mutex);
printf("Child prints %d\n", (*a)++);
sem_post(&mutex);
}
}
else if (pid > 0)
{
// Parent Process
printf("This is the Parent Process.\n");
for (int i = 0; i < 10; i++)
{
sem_wait(&mutex);
printf("Parent prints %d\n", (*a)++);
sem_post(&mutex);
}
}
}