#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;

void *mythread(void *arg) {
  int i; // stack (private per thread)
  int *counter = (int *)arg;
  for (i = 0; i < max; i++) {
	(*counter)++; // shared: only one
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
	fprintf(stderr, "usage: main-first <loopcount>\n");
	exit(1);
  }
  max = atoi(argv[1]);

  int c1, c2, counter;
  c1 = 0;
  c2 = 0;

  pthread_t p1, p2;
  pthread_create(&p1, NULL, mythread, &c1);
  pthread_create(&p2, NULL, mythread, &c2);
  // join waits for the threads to finish
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  counter = c1+c2;
  printf("main: done\n [counter: %d]\n [should: %d]\n",
	  counter, max*2);
  return 0;
}