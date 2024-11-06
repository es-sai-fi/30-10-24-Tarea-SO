#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;
int numThreads;

void *mythread(void *arg) {
  int i; // stack (private per thread)
  int *counter = (int *)arg;
  for (i = 0; i < max; i++) {
	(*counter)++; // shared: only one
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
	fprintf(stderr, "usage: main-first <loopcount>\n");
	exit(1);
  }
  max = atoi(argv[1]);
  numThreads = atoi(argv[2]);
  
  int *counters = malloc(numThreads * sizeof(int));
  for (int i = 0; i < numThreads; i++) {
    counters[i] = 0;
  }
  int finalCounter = 0;
  pthread_t *threads = malloc(numThreads * sizeof(pthread_t));

  for (int i = 0; i < numThreads; i++) {
    pthread_create(&threads[i], NULL, mythread, &counters[i]);
  }
  for (int i = 0; i < numThreads; i++) {
    pthread_join(threads[i], NULL);
  }
  
    for (int i = 0; i < numThreads; i++) {
    finalCounter += counters[i];
  }

  printf("main: done\n [counter: %d]\n [should: %d]\n",
	  finalCounter, max*numThreads);
  return 0;
}
