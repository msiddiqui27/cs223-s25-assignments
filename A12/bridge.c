/**
 * Name: maryam
 * date: 04/16/2025
 * program description: In the file, bridge.c, your will find a simulation of summer tourists. Each tourist is simulated with a thread. The bridge is modeled as a shared, global resource. If two cars simultaneously try to drive in opposite directions on the bridge, we have a terrible accident. The bridge explodes and any cars on the bridge plummet to the rapids below. Edit the file, bridge.c, to safely simulate N tourists spending the day in Mountainview Village.
 * prevent deadlocks where no one takes the bridge
 * prevent accidents where cars travel in both directions at once


 */

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

typedef enum
{
  OUTLOOK,
  TOWN
} location_t;
const char *location_string[2] = {"Outlook", "Town"};

struct bridge_t
{
  int num_on_bridge[2];
  location_t direction;
  pthread_mutex_t lock;
  pthread_cond_t free;
} bridge; // global variable for bridge

struct thread_data
{
  int id;
  int num_trips;
  location_t start_destination;
};

void *Move(void *args)
{
  struct thread_data *data = (struct thread_data *)args;
  int id = data->id;
  location_t destination = data->start_destination;

  for (int i = 0; i < data->num_trips; i++)
  {

    // cross bridge
    // i replaced the original code chunk that was here, starting from "bridge.destination=destination;...assert(...);"
    // i wraped the entire "entering the bridge" parts with a pthread_mutex_lock & whiel loop to wait until it was safe to enter the bridge
    pthread_mutex_lock(&bridge.lock);                       // lock before entering
    while (bridge.num_on_bridge[(destination + 1) % 2] > 0) // wait until its safe for cars to enter the bridge (bridge is empty or other tourists on bridge going same way as them)
    {
      pthread_cond_wait(&bridge.free, &bridge.lock);
    }

    if (bridge.num_on_bridge[destination] == 0) // if the bridfe is empty, the direction can be set
    {
      bridge.direction = destination;
    }
    bridge.num_on_bridge[destination]++; // stop onto birdge
    // Assert that no one is on the bridge, going the opposite way
    // now it should be safe to cross. i moved the printf to the bottom, but the results should be the same

    assert(bridge.num_on_bridge[(bridge.direction + 1) % 2] == 0);
    pthread_mutex_unlock(&bridge.lock);
    printf("Tourist %d takes their %d/%d trip towards %s\n",
           id, i, data->num_trips, location_string[destination]);

    sleep(rand() / RAND_MAX);

    pthread_mutex_lock(&bridge.lock); // lock again to exit safely
    // chunk i changed

    bridge.num_on_bridge[destination]--;
    // Assert that number on bridge never goes below zero
    // Assert that no one is on the bridge, going the opposite way
    assert(bridge.num_on_bridge[destination] >= 0);
    assert(bridge.num_on_bridge[(bridge.direction + 1) % 2] == 0);

    if (bridge.num_on_bridge[destination] == 0) // if bridge is empty, signall all waiting cars
    {
      pthread_cond_broadcast(&bridge.free); // wake everyone waiting
    }
    pthread_mutex_unlock(&bridge.lock); // dont crossing

    // spend time at the new location and then change destination
    sleep(rand() / RAND_MAX);
    location_t current = destination;
    destination = (destination + 1) % 2;
  }

  return NULL;
}

int main(int argc, char **argv)
{

  if (argc != 3)
  {
    printf("usage: %s <NumThreads> <NumTrips>\n", argv[0]);
    exit(0);
  }

  int N = strtol(argv[1], NULL, 10);
  int ntrips = strtol(argv[2], NULL, 10);

  bridge.direction = OUTLOOK;
  bridge.num_on_bridge[OUTLOOK] = 0;
  bridge.num_on_bridge[TOWN] = 0;
  pthread_mutex_init(&(bridge.lock), NULL);
  pthread_cond_init(&(bridge.free), NULL);

  pthread_t *threads = malloc(sizeof(pthread_t) * N);
  struct thread_data *data = malloc(sizeof(struct thread_data) * N);
  for (int i = 0; i < N; i++)
  {
    data[i].id = i;
    data[i].num_trips = ntrips;
    data[i].start_destination = i < (N + 1) / 2 ? OUTLOOK : TOWN;
    pthread_create(&threads[i], NULL, Move, &data[i]);
  }

  for (int i = 0; i < N; i++)
  {
    pthread_join(threads[i], NULL);
  }

  free(threads);
  free(data);
  pthread_mutex_destroy(&bridge.lock);
  pthread_cond_destroy(&bridge.free);
  return 0;
}
