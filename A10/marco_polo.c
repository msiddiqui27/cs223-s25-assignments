/**
 * Name: Maryam
 * Date: 04/04/2025
 * Assignment description: this programuses signals to coordinate between two processes, like so. When the user presses the 'm' key, the parents sends SIGALRM. When the child receives SIGALRM, the child prints "Marco" and sends SIGALRM to the parent. When the parent receives SIGALRM, the parent prints "Polo".
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> //was getting an error using pid_t wihtout inlcuding this header file

pid_t child_pid = -1; // global variables to hold child & parent process id
pid_t parent_pid = -1;

void parent_handler(int signum)
/**
 * function for the parent process when recieving sigalrm
 * prints "polo" and the parent's pid when called
 * @param signum: singla number recieved
 */
{
  printf("Polo [%d]\n", getpid()); // print polo and current process id
  fflush(stdout);                  // flush output so it appears fast
}

void child_handler(int signum)
/**
 * signal handler for child process when recibing sigalrm
 * prints marco and send sigalrm back to parent to compelte runnign
 * @param signum: signal number received
 */
{
  printf("Marco [%d]\n", getpid()); // print marco and current prcess id
  fflush(stdout);                   // flush output out immediately
  kill(parent_pid, SIGALRM);        // signal parent back with sigalrm
}

int main()
/**
 * main function running program
 * forks into parent and child
 * parents waits for m or q input
 * q terminates
 * return 0 when successfully exectued
 */
{
  parent_pid = getpid(); // store parent process id
  child_pid = fork();    // create child process

  if (child_pid < 0) // if fork failed print message
  {
    printf("Error: the fork failed\n");
    exit(1);
  }

  if (child_pid == 0) // runs in child process
  {
    signal(SIGALRM, child_handler);
    signal(SIGTERM, exit);//tried to just exit bu the whole program crashed, so need to use sigterm instead for the signal process to exit

    while (1) // this infininte loops wiats for a signal to happen
    {
      pause(); // also used in 13.4 of book from signals
    }
  }
  else
  {
    signal(SIGALRM, parent_handler); // run parent process
    printf("Parent is %d\n", parent_pid);
    fflush(stdout);

    char command; // user input
    while (1)
    {
      command = getchar(); // read the variable from the user, which can only be m or q
      if (command == '\n')
      {
        continue; // skip newlines
      }

      if (command == 'm')
      {
        kill(child_pid, SIGALRM); // send signal to child
      }

      else if (command == 'q')
      {
        kill(child_pid, SIGTERM); // terminate child
        break;                    // exit loop
      }
      else
      {
        printf("incorrect input, try again\n");
      }
    }
  }
}