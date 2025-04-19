/**
 * Name: maryam
 * date: 04/16/2025
 * program description: implement the producer/consumer demo from class.  producer function should generate an integer between 0 and 9.  
 * consumer function should print the value. 
 * The size of  circular queue should be 10 elements.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 10

int buffer[N]; // buffer to hold items
int in = 0;    // index where producer inserts
int out = 0;   // index where consumer removes
int count = 0; // current # of items in buffer

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;  // mutex to protect shared data
pthread_cond_t n_full = PTHREAD_COND_INITIALIZER;  // condition to wait when buffer is full
pthread_cond_t n_empty = PTHREAD_COND_INITIALIZER; // conition to wait when buffer is empty

int produce_item()
{
  return rand() % 10;
}

void consume_item(int item)
{
  printf("Received item: %d\n", item);
}

void *producer(void *arg)
/**
 * helper producer function
 */
{
  while (1) // infinitne loop so keeps on producing
  {
    int item = produce_item(); // create new item
    sleep(1);                  // slow down producer output for readability
    pthread_mutex_lock(&lock); // lock before accessing shared buffer
    while (count == N)         // wait if buffer is full
    {
      pthread_cond_wait(&n_full, &lock); // wait until slot is free
    }
    buffer[in] = item; // place item into buffer
    in = (in + 1) % N; // move to next slot
    count++;

    pthread_cond_signal(&n_empty); // wake up a consumer if there is one waiting
    pthread_mutex_unlock(&lock);   // unlock buffer
  }
  return NULL;
}

void *consumer(void *arg)
/**
 * helper function
 */
{
  while (1) // keeeps on consuming
  {
    pthread_mutex_lock(&lock); // lock before accessing shared buffer
    while (count == 0)         // wait if buffer is empty
    {
      pthread_cond_wait(&n_empty, &lock); // wait until item is available
    }
    int item = buffer[out]; // get item from buffer
    out = (out + 1) % N;    // move to next slot
    count--;

    pthread_cond_signal(&n_full); // wake up waiting producer
    pthread_mutex_unlock(&lock);  // unlock buffer
    consume_item(item);           // print consumed item
    sleep(1);                     // slow down consumer for easier output tracking
  }
  return NULL;
}

int main()
{
  srand(time(NULL));//seed random generator for producer
  pthread_t producer_thread, consumer_thread;//threads from producer and consumer

  pthread_create(&producer_thread, NULL, producer, NULL);//start producer thread
  pthread_create(&consumer_thread, NULL, consumer, NULL);//start consumer thread
  pthread_join(producer_thread, NULL);//wait for for producer
  pthread_join(consumer_thread, NULL);//wait for consumer
  return 0;
}
