// Gabby and Maryam

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100
#define NUM_THREADS 4

int M[SIZE * SIZE];
int u[SIZE];
int result[SIZE];
int result_threads[SIZE];

typedef struct
{
  int start_row;
  int end_row;
} ThreadData;

void *compute_product(void *arg)
{
  ThreadData *data = (ThreadData *)arg;

  for (int i = data->start_row; i < data->end_row; i++)
  {
    result_threads[i] = 0;
    for (int j = 0; j < SIZE; j++)
    {
      result_threads[i] += M[i * SIZE + j] * u[j];
    }
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  srand(time(0));

  for (int i = 0; i < SIZE; i++)
  {
    u[i] = rand() % 10 - 5;
    result[i] = 0;
    result_threads[i] = 0;
  }

  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      int value = rand() % 10 - 5;
      M[i * SIZE + j] = value;
      result[i] += value * u[j];
    }
  }

  printf("Test with 4 threads\n");

  pthread_t threads[NUM_THREADS];
  ThreadData thread_data[NUM_THREADS];

  int rows_per_thread = SIZE / NUM_THREADS;

  for (int i = 0; i < NUM_THREADS; i++)
  {
    thread_data[i].start_row = i * rows_per_thread;
    thread_data[i].end_row = (i == NUM_THREADS - 1) ? SIZE : (i + 1) * rows_per_thread;

    pthread_create(&threads[i], NULL, compute_product, (void *)&thread_data[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(threads[i], NULL);
  }

  int error = 0;
  for (int i = 0; i < SIZE; i++)
  {
    error += abs(result[i] - result_threads[i]);
  }
  printf("Error between ground truth and multithreaded version: %d\n", error);

  return 0;
}
