#include "student.h"
#include "avl_tree.h"
#include <ctime>

int main(int argc, char* argv[]) {
  char *filename = 0;
  int r, task, res, res_all;
  double t, t_all;
  FILE *fp;
  const char *s;
  io_status read;

  if (!((argc == 4) &&
    (sscanf(argv[1], "%d", &r) == 1)))
  {
    printf("Usage %s\n", argv[0]);
    return -1;
  }
  s = argv[2];
  filename = argv[3];

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Can't open file %s\n", filename);
    return -2;
  }

  avl_tree<student> *birch = new avl_tree<student>;
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

  const char * s_all = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  task = 1;
  t = clock();
  res = birch->solve1(s);
  t = (clock()-t)/CLOCKS_PER_SEC;
  t_all = clock();
  res_all = birch->solve1(s_all);
  t_all = (clock()-t_all)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s_all, res_all, t_all);
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s, res, t);

  task = 2;
  t = clock();
  res = birch->solve2(s);
  t = (clock()-t)/CLOCKS_PER_SEC;
  t_all = clock();
  res_all = birch->solve2(s_all);
  t_all = (clock()-t_all)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s_all, res_all, t_all);
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s, res, t);

  task = 3;
  t = clock();
  res = birch->solve3(s);
  t = (clock()-t)/CLOCKS_PER_SEC;
  t_all = clock();
  res_all = birch->solve3(s_all);
  t_all = (clock()-t_all)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s_all, res_all, t_all);
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s, res, t);

  task = 4;
  t = clock();
  res = birch->solve4(s);
  t = (clock()-t)/CLOCKS_PER_SEC;
  t_all = clock();
  res_all = birch->solve4(s_all);
  t_all = (clock()-t_all)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s_all, res_all, t_all);
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s, res, t);

  task = 5;
  t = clock();
  res = birch->solve5(s);
  t = (clock()-t)/CLOCKS_PER_SEC;
  t_all = clock();
  res_all = birch->solve5(s_all);
  t_all = (clock()-t_all)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s_all, res_all, t_all);
  printf ("%s : Task = %d S = %s Result = %d Elapsed = %.2f\n", argv[0], task, s, res, t);

  delete birch;
  fclose(fp);
  return 0;
}
