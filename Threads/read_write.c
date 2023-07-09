#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define readers 5
#define writers 2
int sharedResource = 0;
pthread_mutex_t resourceLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t readerCountLock = PTHREAD_MUTEX_INITIALIZER;
int readerCount = 0;
void *reader(void *arg)
{
int readerId = *(int *)arg;
pthread_mutex_lock(&readerCountLock);
readerCount++;
if (readerCount == 1)
{
pthread_mutex_lock(&resourceLock);
}
pthread_mutex_unlock(&readerCountLock);
printf("Reader %d reads shared resource: %d\n", readerId, sharedResource);
pthread_mutex_lock(&readerCountLock);
readerCount--;
if (readerCount == 0)
{
pthread_mutex_unlock(&resourceLock);
}
pthread_mutex_unlock(&readerCountLock);
pthread_exit(NULL);
}
void *writer(void *arg)
{
int writerId = *(int *)arg;
pthread_mutex_lock(&resourceLock);
sharedResource = writerId;
printf("Writer %d writes shared resource: %d\n", writerId,
sharedResource);
pthread_mutex_unlock(&resourceLock);
pthread_exit(NULL);
}
int main()
{
pthread_t readerThreads[readers];
pthread_t writerThreads[writers];
int readerIds[readers];
int writerIds[writers];
for (int i = 0; i < writers; i++)
{
writerIds[i] = i + 1;
pthread_create(&writerThreads[i], NULL, writer, &writerIds[i]);
}
for (int i = 0; i < readers; i++)
{
readerIds[i] = i + 1;
pthread_create(&readerThreads[i], NULL, reader, &readerIds[i]);
}
for (int i = 0; i < readers; i++)
{
pthread_join(readerThreads[i], NULL);
}
for (int i = 0; i < writers; i++)
{
pthread_join(writerThreads[i], NULL);
}
return 0;}