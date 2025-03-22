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
    ordering order[3] = {ordering::none};
    command_type check = buff.check_type(buf);
    if (check == command_type::quit) {
      printf("\n");
      break;
    }
    switch(check) {
      case command_type::select:
        if (buff.parse(buf, order) == false) printf("incorrect format\n");
        res += birch.check(buff, order);
        printf("\n");
        break;
      case command_type::quit:
        break;
      case command_type::insert:
        birch.parse_insert(buf);
        break;
      case command_type::del:
        birch.delete_parse(buf);
        break;
      case command_type::incorrect:
        printf("incorrect command\n");
        break;

    }
  }
  t = (clock()-t)/CLOCKS_PER_SEC;

  printf ("%s : Result = %d Elapsed = %.2f\n", argv[0], res, t);

  fclose(fp);
  return 0;
}
