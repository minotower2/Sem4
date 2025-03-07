#include "record.h"
#include "command.h"
#include "lists.h"

int main(int argc, char* argv[]) {
  char *filename = 0;
  FILE *fp;
  double t;
  int res = 0;

  if (!((argc == 2)))
  {
    printf("Usage filename %s\n", argv[0]);
    return -1;
  }
  filename = argv[1];

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Can't open file %s\n", filename);
    return -2;
  }

  list birch;
  birch.read_list(fp);

  char buf[LEN];
  t = clock();
  while (fgets(buf, LEN, stdin)) {
    command buff;
    buff.parse(buf);
    res += birch.check(buff);
  }
  t = (clock()-t)/CLOCKS_PER_SEC;

  printf ("%s : Result = %d Elapsed = %.2f\n", argv[0], res, t);

  fclose(fp);
  return 0;
}
