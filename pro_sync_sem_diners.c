#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5

// Semaphore variables
sem_t entering_diners;
sem_t enter_done;
sem_t exiting_diners;
sem_t exit_done;
sem_t mutex_enter;
sem_t mutex_exit;
sem_t door_mutex;
sem_t food_served;
int count_enter = 0;
int count_exit = 0;
int front_door_open = 0;
int back_door_open = 0;
int front_door_closed = 0;

void openFrontDoor() {
  printf("We are opening the Front Doors :\n");
  printf("Only %d diners can come in\n", N);
  if (!front_door_open) {
    printf("Opening front door\n");
    front_door_open = 1;
  }
}

void closeFrontDoor() {
  if (front_door_open) {
    printf("Closing front door\n");
    front_door_open = 0;
    front_door_closed = 1;
  }
}

void serveFood() {
  printf("Serving food\n");
  for (int i = 0; i < N; i++) {
    sem_post(&food_served); // Signal that food is served
  }
}

void openBackDoor() {
  if (!back_door_open) {
    printf("Opening back door\n");
    back_door_open = 1;
  }
}

void closeBackDoor() {
  if (back_door_open) {
    printf("Closing back door\n");
    back_door_open = 0;
  }
}

void enterRestaurant() { printf("Diner entered the restaurant\n"); }

void exitRestaurant() { printf("Diner exited the restaurant\n"); }

void *dinerThread(void *arg) {
  int id = *(int *)arg;

  // Wait for the entering signal
  sem_wait(&entering_diners);

  // Wait for the front door to be opened
  while (1) {
    sem_wait(&door_mutex);
    if (front_door_open) {
      sem_post(&door_mutex);
      break;
    }
    sem_post(&door_mutex);
    sleep(1);
  }

  // Enter the restaurant
  sem_wait(&door_mutex);
  enterRestaurant();
  sem_post(&door_mutex);

  sem_wait(&mutex_enter);
  count_enter++;
  if (count_enter == N) {
    sem_post(&enter_done);
    count_enter = 0;
  }
  sem_post(&mutex_enter);

  // Wait for food to be served
  sem_wait(&food_served);

  // Eat
  printf("Diner %d is eating\n", id);
  sleep(2); // Simulating eating time

  // Wait for the exiting signal
  sem_wait(&exiting_diners);

  // Exit the restaurant
  sem_wait(&door_mutex);
  if (!back_door_open) {
    openBackDoor();
  }
  sem_post(&door_mutex);

  sem_wait(&mutex_exit);
  count_exit++;
  if (count_exit == N) {
    sem_post(&exit_done);
    count_exit = 0;
  }
  sem_post(&mutex_exit);

  sem_wait(&door_mutex);
  exitRestaurant();
  sem_post(&door_mutex);

  return NULL;
}

void *restaurantThread(void *arg) {
  // Open front door
  sem_wait(&door_mutex);
  openFrontDoor();
  sem_post(&door_mutex);

  // Signal entering diners
  for (int i = 0; i < N; i++) {
    sem_post(&entering_diners);
  }

  // Wait for all diners to enter
  sem_wait(&enter_done);

  // Close the door
  sem_wait(&door_mutex);
  closeFrontDoor();
  front_door_closed = 0;
  sem_post(&door_mutex);

  // Serve food
  serveFood();

  // Open back door
  sem_wait(&door_mutex);
  if (!back_door_open) {
    openBackDoor();
  }
  sem_post(&door_mutex);

  // Signal exiting diners
  for (int i = 0; i < N; i++) {
    sem_post(&exiting_diners);
  }

  // Wait for all diners to exit
  sem_wait(&exit_done);

  // Close back door
  sem_wait(&door_mutex);
  closeBackDoor();
  sem_post(&door_mutex);

  return NULL;
}

int main() {
  pthread_t dinerThreadID[N];
  pthread_t restaurantThreadID;
  int dinerIDs[N];

  // Initialize semaphores
  sem_init(&entering_diners, 0, 1);
  sem_init(&enter_done, 0, 0);
  sem_init(&exiting_diners, 0, 0);
  sem_init(&exit_done, 0, 0);
  sem_init(&mutex_enter, 0, 1);
  sem_init(&mutex_exit, 0, 1);
  sem_init(&door_mutex, 0, 1);
  sem_init(&food_served, 0, 0);

  // Create diner threads
  for (int i = 0; i < N; i++) {
    dinerIDs[i] = i + 1;
    pthread_create(&dinerThreadID[i], NULL, dinerThread, &dinerIDs[i]);
  }

  // Create restaurant thread
  pthread_create(&restaurantThreadID, NULL, restaurantThread, NULL);

  // Join diner threads
  for (int i = 0; i < N; i++) {
    pthread_join(dinerThreadID[i], NULL);
  }

  // Join restaurant thread
  pthread_join(restaurantThreadID, NULL);

  // Destroy semaphores
  sem_destroy(&entering_diners);
  sem_destroy(&enter_done);
  sem_destroy(&exiting_diners);
  sem_destroy(&exit_done);
  sem_destroy(&mutex_enter);
  sem_destroy(&mutex_exit);
  sem_destroy(&door_mutex);
  sem_destroy(&food_served);

  return 0;
}