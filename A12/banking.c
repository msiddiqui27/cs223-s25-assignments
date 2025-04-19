/**
 * Name: maryam
 * date: 04/16/2025
 * program description: Edit the file, banking.c, so it correctly handles a series of transfers between two accounts. 
 * Specifically, you should ensure the program does not subtract funds if there aren’t sufficient funds in the account. 
 * The program does not hang due to deadlock. 
 */

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

struct account
{
  float balance;
  pthread_mutex_t lock;
  pthread_cond_t withdraw; // a condition varibale to check if the user can withdraw
};

struct thread_data
{
  struct account *fromAccount;
  struct account *toAccount;
  float amount;
};

void lock_both_acc(struct account *a1, struct account *a2)
/**
 * void helper function to consistently lock both accounts in memory address to prevent deadlock
 */
{
  if (a1 < a2)
  {
    pthread_mutex_lock(&(a1->lock));
    pthread_mutex_lock(&(a2->lock));
  }
  else
  {
    pthread_mutex_lock(&(a2->lock));
    pthread_mutex_lock(&(a1->lock));
  }
}

void unlock_both_acc(struct account *a1, struct account *a2)
/**
 * void helper function unlock to go with lock_both)acc
 */
{
  pthread_mutex_unlock(&(a1->lock));
  pthread_mutex_unlock(&(a2->lock));
}

void *Transfer(void *args)
{
  struct thread_data *data = (struct thread_data *)args;
  struct account *fromAcct = data->fromAccount;
  struct account *toAcct = data->toAccount;
  float amt = data->amount;

  for (int i = 0; i < 1000; i++)
  {
    pthread_mutex_lock(&(fromAcct->lock)); // lock fromAcct individuall to check balance safely
    while (fromAcct->balance < amt)        // if there aren't enough funds, wait
    {
      pthread_cond_wait(&(fromAcct->withdraw), &(fromAcct->lock)); // releases lock and waits for funds
    }
    pthread_mutex_unlock(&(fromAcct->lock)); // unlock after wait check

    lock_both_acc(fromAcct, toAcct); // lock both accounts

    if (fromAcct->balance >= amt) // double check balance under full lock
    {
      fromAcct->balance -= amt;
      assert(fromAcct->balance >= 0); // assert was required, i just moved it around a bit
      toAcct->balance += amt;

      pthread_cond_signal(&toAcct->withdraw); // signal that toAcct now has more money if someone is waiting. i have tried to run the program without this line, but it literally does not work.
    }
    unlock_both_acc(fromAcct, toAcct);
  }

  return NULL;
}

int main()
{
  struct account A, B;
  A.balance = 5000;
  B.balance = 5000;
  pthread_mutex_init(&(A.lock), NULL);
  pthread_mutex_init(&(B.lock), NULL);
  pthread_cond_init(&(A.withdraw), NULL); // contion variable init
  pthread_cond_init(&(B.withdraw), NULL);

  printf("Starting balance A: %.2f\n", A.balance);
  printf("Starting balance B: %.2f\n", B.balance);

  struct thread_data dataA;
  dataA.fromAccount = &B;
  dataA.toAccount = &A;
  dataA.amount = 1000;

  struct thread_data dataB;
  dataB.fromAccount = &A;
  dataB.toAccount = &B;
  dataB.amount = 1000;

  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, Transfer, &dataA);
  pthread_create(&thread2, NULL, Transfer, &dataB);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // Should be the same because we transfer the same amount between both
  printf("Ending balance A: %.2f\n", A.balance);
  printf("Ending balance B: %.2f\n", B.balance);

  pthread_mutex_destroy(&A.lock);
  pthread_mutex_destroy(&B.lock);
  pthread_cond_destroy(&A.withdraw); // condition variable cleaned
  pthread_cond_destroy(&B.withdraw);

  return 0;
}
