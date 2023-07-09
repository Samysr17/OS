#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_t tid[2];
void *doSomeThing(void *arg)
{
pthread_t id = pthread_self();
if (pthread_equal(id, tid[0]))
printf("\nFirst Thread Processing \n");
else
printf("\nSecond Thread Processing \n");
}
int main(void)
{
int i = 0;
int err;
while (i < 2)
{
err = pthread_create(&tid[i], NULL, &doSomeThing, NULL);
if (err != 0)
printf("\nCan't create Thread : [%s]", strerror(err));
else
printf("\nThread created successfully\n");
i++;
}
sleep(5);
return 0;
}
