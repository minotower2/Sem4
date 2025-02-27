#include "solve.h"

int main(int argc, char **argv) {
  char *filenamein = 0, *filenameout = 0, *s = 0, *t = 0, *x = 0;
  int res = 0, task = 5;
  double time;
  io_status read;

  if (!((argc == 6)))
  {
    printf("Usage %s\n", argv[0]);
    return -1;
  }
  filenamein = argv[1];
  filenameout = argv[2];
  s = argv[3];
  t = argv[4];
  x = argv[5];

  read = solve5(filenamein, filenameout, s, t, x, &res);
  time = clock();
  switch(read) {
    case io_status::success: break;
    case io_status::read:
      printf("Couldn't open file\n");
      return 1;
    case io_status::memory:
      printf("Memory error\n");
      return 2;
    case io_status::create:
      printf("Error!\n");
      return 3;
    case io_status::format:
      printf("Wrong format\n");
      return 4;
  }
  time = (clock()-time)/CLOCKS_PER_SEC;

  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, time);
  return 0;
}
