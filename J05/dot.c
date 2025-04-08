// Gabby and Maryam
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000
#define thread_num 4
int partial_sums[thread_num];
int v[SIZE];
int u[SIZE];

typedef struct ThreadArguments
{
  int start_idx;
  int end_idx;
  int thread_id;
} ThreadArguments;

// your code here
void *chunk_dotproduct(void *args)
{

  ThreadArguments *threadargs = (ThreadArguments *)args;
  int sum = 0;
  for (int i = threadargs->start_idx; i < threadargs->end_idx; i++)
  {
    sum += u[i] * v[i];
  }
  partial_sums[threadargs->thread_id] = sum;

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  srand(time(0));
  int dotproduct = 0;

  for (int i = 0; i < SIZE; i++)
  {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    dotproduct += u[i] * v[i];
  }
  printf("Ground truth dot product: %d\n", dotproduct);

  pthread_t threads[thread_num];
  ThreadArguments threadargs[thread_num];

  int chunk_size = SIZE / thread_num;
  // chunk 1
  threadargs[0].thread_id = 0;
  threadargs[0].start_idx = 0;
  threadargs[0].end_idx = chunk_size;
  // chunk 2
  threadargs[1].thread_id = 1;
  threadargs[1].start_idx = chunk_size;
  threadargs[1].end_idx = chunk_size * 2;
  // chunk 3
  threadargs[2].thread_id = 2;
  threadargs[2].start_idx = chunk_size * 2;
  threadargs[2].end_idx = chunk_size * 3;
  // chunk 4
  threadargs[3].thread_id = 3;
  threadargs[3].start_idx = chunk_size * 3;
  threadargs[3].end_idx = SIZE;

  pthread_create(&threads[0], NULL, chunk_dotproduct, &threadargs[0]);
  pthread_create(&threads[1], NULL, chunk_dotproduct, &threadargs[1]);
  pthread_create(&threads[2], NULL, chunk_dotproduct, &threadargs[2]);
  pthread_create(&threads[3], NULL, chunk_dotproduct, &threadargs[3]);

  // Wait for all 4 threads to finish
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);
  pthread_join(threads[3], NULL);

  // Sum up the partial results
  int thread_dotproduct = 0;
  thread_dotproduct += partial_sums[0];
  thread_dotproduct += partial_sums[1];
  thread_dotproduct += partial_sums[2];
  thread_dotproduct += partial_sums[3];

  // TODO: Implement your thread solution here

  printf("Test with 4 threads\n");

  printf("Answer with threads: %d\n", thread_dotproduct);

  return 0;
}
