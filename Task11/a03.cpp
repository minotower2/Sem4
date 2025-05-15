#include "solve.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv) {
  if (!(argc == 3)) {
    printf("Usage %s filenamein filenameout\n", argv[0]);
    return -1;
  }
  const char * filenamein = argv[1];
  const char * filenameout = argv[2];
  int res = 0;
  int task = 3;

  double t = clock();
  switch(solve3(filenamein, filenameout, res)) {
    case io_status::open:
      printf("Couldn't open file\n");
      return -1;
    default:
      break;
  }
  t = (clock() - t) / CLOCKS_PER_SEC;

  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
  return 0;
}
