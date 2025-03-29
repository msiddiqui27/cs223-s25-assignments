/**
 * Author: Maryam
 * Date: 03/28/2025
 * Program description: grep.c implements a program that uses N processes to search for a keyword in a set of files
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct Task
{
  int start_idx; // start index of file list this program will search
  int end_idx;   // end index
  char *keyword; // keyword being searched
  int process_n; // process number for tracking
  char **files;  // list of file names
} Task;

void fileSearch(Task k)
/**
 * performs the file search and exits w/ match count
 */
{
  int match = 0;
  printf("Process [%d] searching %d files ( %d to %d)\n", getpid(), k.end_idx - k.start_idx, k.start_idx, k.end_idx - 1);
  // log which files are being searched by this process
  fflush(stdout);

  for (int i = k.start_idx; i < k.end_idx; i++) // loop through assigned file range
  {
    FILE *fp = fopen(k.files[i], "r"); // open file
    if (!fp)
    {
      fprintf(stderr, "Process [%d] Erorr, cant open file %s\n", getpid(), k.files[i]);
      fflush(stderr);
      exit(0); // return/exit with 0 matches if file can't be opened
    }
    char line[1000]; // buffer to hold each line
    while (fgets(line, sizeof(line), fp))
    {
      if (strstr(line, k.keyword))
      {
        printf(ANSI_COLOR_MAGENTA "%d] %s:%s" ANSI_COLOR_RESET, getpid(), k.files[i], line); // print match with color. was playing around with different colors and liked the magenta one the best.
        fflush(stdout);
        match++;
      }
    }
    fclose(fp); // cloe file after reading
  }

  printf("Process [%d] found %d lines containing keyword: %s\n", getpid(), match, k.keyword);
  fflush(stdout); // flush output before exiting

  // return match count as exit code (maximum allowed is 255)
  if (match > 255)
  {
    match = 225; // exit code limited from 0 to 255
  }

  exit(match); // send match count back by exiting code
}

void time_elapsed(struct timeval start, struct timeval end) 
/**
 * this function tracks the time elapsed
 */
{
  double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;//most of this was taken from chapter 11.5.1, which also taught me how to use the gettimeofday function. in the book they used 1.e6 and i just used 1000000 instead
  printf("Elapsed time is %.6f\n", elapsed);
}

int main(int argc, char *argv[])
/**
 * main function for grep program
 * implements grep command using multiple child processes. it divides a set of files aong n child processes to search for a given keyword and collects the total number of matches lines across all files
 * @param argc: number of command line arguments
 * @param argv: array of strings representing the command line arguments
 * argv[1]: number of child processes to create
 * argv[2]: keyword to search for
 * argc[3]: list of file paths to search
 * @return return 0 on successful exection, 1 for memory errors
 */
{
  if (argc < 4)
  {
    fprintf(stderr, "usage: ./grep <NumProcesses> <Keyword> <Files>\n");//just copied the format from the assignment example
    return 1;
  }

  int num_processes = atoi(argv[1]); // how many child processes to create
  char *keyword = argv[2];           // keyword to search
  char **files = &argv[3];           // file listes begins at argv[3]
  int num_files = argc - 3;          // how many total files

  printf("Searching %d files for keyword: %s\n", num_files, keyword);

  struct timeval start, end;
  gettimeofday(&start, NULL);            // record start time

  int base = num_files / num_processes;  // base files for each process
  int extra = num_files % num_processes; // files left over
  int total_matches = 0;
  int file_idx = 0;

  pid_t *pids = malloc(sizeof(pid_t) * num_processes);
  if (pids == NULL)
  {
    fprintf(stderr, "Error: malloc failed\n");
    return 1;
  }

  for (int i = 0; i < num_processes; i++)
  {
    int count = base; // handle remainder
    if (i < extra)
    {
      count += 1;
    }

    Task k;
    k.start_idx = file_idx;//set starting index in files array for this process
    k.end_idx = file_idx + count; //set ending index based on how many files this proess shuodl handle
    k.keyword = keyword;//set keyword process will search
    k.files = files;//assign shared array of file names to this task
    k.process_n = i;//store this process's number so i knew where to debug if needed

    pid_t pid = fork(); // fork child
    if (pid == 0)
    {
      fileSearch(k); // child runs the search and exits with match count
    }

    pids[i] = pid;     // parent saves child’s pid
    file_idx += count; // move to next file chunk
  }

  for (int i = 0; i < num_processes; i++)
  {
    int status;
    waitpid(pids[i], &status, 0); // wait for specific child

    
    int matches = (status >> 8) & 0xFF;//extract child's exit code from the waitpid status, shifting tight by 8 bits to move the high byte int o the low positions since the actual exit code is in the hight byte. 
                                      //& 0xFF masks it to keep just the lowest 8 bits. had to review this from chapter 4

    total_matches = total_matches + matches; // add this child's match count to the running total
  }

  gettimeofday(&end, NULL); // record end time
  printf("Total occurrences: %d\n", total_matches);
  time_elapsed(start, end); // show total time
  free(pids);               // clean up memory
  return 0;
}