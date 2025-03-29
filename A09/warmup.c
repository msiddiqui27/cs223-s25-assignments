/**
 * Author: Maryam
 * Program description: warmup.c implemetns a program that spans processes according to the diagram on assignment 9.
 * date: 03/27/2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
/**
 * main program following the sequence: A0-> B0-> C0-> Bye  (main)
 *                                                |C1-> Bye (C0's child)
 *                                           |B1-> Bye (B0's child)
 * each process prints the messahe with its process id, using getpid()
 * fflush(stdout) used to ensure immediate output before fork creates children, used form chapter 13
 * waitpit() used from chapter 13 allowing parents to block while waitinf or the termination of a specific child process
 */

{
  printf("%d] A0\n", getpid());
  fflush(stdout);

  printf("%d] B0\n", getpid());
  fflush(stdout);

  pid_t pid_b1 = fork(); // fork b1
  if (pid_b1 == 0)       // child process: b1
  {
    printf("%d] B1\n", getpid());
    fflush(stdout);
    printf("%d] Bye\n", getpid());
    fflush(stdout);
    return 0;
  }
  waitpid(pid_b1, NULL, 0); // parent process continues as B0. waitpid() waits for B1 to finish

  pid_t pid_c0 = fork(); // fork c0
  if (pid_c0 == 0)       // child process: c0
  {
    printf("%d] C0\n", getpid());
    fflush(stdout);
    printf("%d] Bye\n", getpid()); // C0 says bye before C1
    fflush(stdout);

    pid_t pid_c1 = fork(); // fork c1
    if (pid_c1 == 0)       // child process: c1
    {
      printf("%d] C1\n", getpid());
      fflush(stdout);
      printf("%d] Bye\n", getpid());
      fflush(stdout);
      return 0;
    }

    waitpid(pid_c1, NULL, 0); // C0 waits for C1
    return 0;
  }
  waitpid(pid_c0, NULL, 0);
  return 0;
}