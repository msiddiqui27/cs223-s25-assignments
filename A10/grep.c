

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct // struct holding arguments passed to each thread
{
  int thread_id;   // thread id
  int start_index; // startinf idx of file range
  int end_index;
  char **files;
  char *keyword;
  int match_count; // number of matches thread found
} ThreadArguments;

void *search_files(void *arg)
/**
 * function to check if each thread runs
 * searchws subset of files for keyword
 * opens files to read, these files are assigned to a threat
 * searches each line for the keywrod with strstr
 * if there is a match, prints the line and thread/file info
 * @param arg: pointer to threadArguments struct containign the arguments of the thread
 * @return null
 *
 */
{
  ThreadArguments *args = (ThreadArguments *)arg;
  args->match_count = 0; // initilaize match count for thread

  for (int i = args->start_index; i < args->end_index; i++)
  { // loop through file
    FILE *fp = fopen(args->files[i], "r");
    if (!fp) // open file and handle error case
    {
      fprintf(stderr, "thread can't open");
    }
    char line[1000];                      // holds each line
    while (fgets(line, sizeof(line), fp)) // read each line from file
    {
      if (strstr(line, args->keyword)) // if line contains keywrod using strstr
      {
        printf("[thread %d] %s: %s", args->thread_id, args->files[i], line); // print match with file name and line
        args->match_count++;                                                 // increment match counter
      }
    }
    fclose(fp); // close file
  }
  return NULL;
}
int main(int argc, char *argv[])
/**
 * main function to run multithread grep
 * parses command line arguments and splits the work among threads
 */
{
  if (argc < 4)//check minimum number of arguments
  {
    fprintf(stderr, "./grep <NumThreards> <Keyword> <Files>\n");//print usage instructions like the example showed
    exit(1);//exit
  }

  int num_threads = atoi(argv[1]);//convert argument 1 to number of threads
  if (num_threads < 1)
  {
    fprintf(stderr, "Error: number of threads must be at least 1. try again.\n");//is number of threads positive?
    exit(1);
  }
  char *keyword = argv[2];//keyword being searched
  int num_files = argc - 3;//total number of files that are given to us
  char **files = &argv[3];//point to first filename in argv

  pthread_t *threads = malloc(num_threads * sizeof(pthread_t));//i tried another way but it didn't work so this way I am dynamically allocating arrays for threads and their arguemetns

  ThreadArguments *thread_arguments = malloc(num_threads * sizeof(ThreadArguments));

  if (threads == NULL || thread_arguments == NULL) //if memory allocation failed, print error message
  {
    fprintf(stderr, "error: memory allocation failed.\n");
    exit(1);
  }
  int files_thread = num_files / num_threads;//calculate even diviison of files per thread
  int remainder = num_files % num_threads;//leftover files

  int current = 0;//next file to assign's index
  for (int i = 0; i < num_threads; i++)
  {
    thread_arguments[i].thread_id = i;//assign thread id
    thread_arguments[i].keyword = keyword;//keyword
    thread_arguments[i].files = files;//pass file list
    thread_arguments[i].start_index = current;//file range starting index
  

    current = thread_arguments[i].end_index;
    pthread_create(&threads[i], NULL, search_files, &thread_arguments[i]);
  }
  int total_matches = 0;
  for (int i = 0; i < num_threads; i++)
  {
    pthread_join(threads[i], NULL);
    total_matches += thread_arguments[i].match_count;
  }

  printf("All threads done. Total matches: %d\n", total_matches);
  free(threads);
  free(thread_arguments);
  return 0;
}
