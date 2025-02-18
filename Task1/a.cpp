#include "student.h"
#include "rb_tree.h"
#include <ctime>

int main(int argc, char* argv[]) {
  char *filename = 0;
  int r, k, task, res;
  double t;
  FILE *fp;
  io_status read;

  if (!((argc == 4) &&
    (sscanf(argv[1], "%d", &r) == 1) &&
    (sscanf(argv[2], "%d", &k) == 1)))
  {
    printf("Usage %s\n", argv[0]);
    return -1;
  }
  filename = argv[3];

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Can't open file %s\n", filename);
    return -2;
  }

  rb_tree<student> *birch = new rb_tree<student>;
  read = birch->read(fp);
  switch(read) {
    case io_status::success:
      break;
    case io_status::eof:
      printf("Reached end of file\n");
      delete birch;
      fclose(fp);
      return -3;
    case io_status::format:
      printf("Wrong format of data\n");
      delete birch;
      fclose(fp);
      return -4;
    case io_status::memory:
      printf("Not enough memory\n");
      delete birch;
      fclose(fp);
      return -5;
  }
  birch->print(r);

  task = 1;
  t = clock();
  res = birch->solve1(k);
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 2;
  t = clock();
  res = birch->solve2(k);
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 3;
  t = clock();
  res = birch->solve3(k);
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 4;
  t = clock();
  res = birch->solve4(k);
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 5;
  t = clock();
  res = birch->solve5(k);
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  delete birch;
  fclose(fp);
  return 0;
}
