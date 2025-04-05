#include "record.h"
#include "command.h"
#include "lists.h"
#include <libgen.h>
#include <string.h>
#include "config.h"
#include <memory>

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

  const char * config_name = "config.txt";
  std::unique_ptr<char []> exe_path = std::make_unique<char []> (strlen (argv[0]) + 1);
  strcpy (exe_path.get (), argv[0]); // make a copy, "dirname" modifies argument
  char *dir = dirname (exe_path.get ()); // get directory with executable
  printf ("Executable dir = %s\n", dir);
  size_t path_len = strlen (dir) + 1 + strlen (config_name) + 1;
  std::unique_ptr<char []> config_path = std::make_unique<char []> (path_len);
  snprintf (config_path.get (), path_len, "%s/%s", dir, config_name);
  printf ("Config path = %s\n", config_path.get ());

  FILE *fc = fopen(config_path.get(), "r");
  if (!fc) {
    printf("Can't open config file\n");
    return -3;
  }
  config con;
  if (con.parse(fc) == false) {
    printf("Couldn't read config file\n");
    return -4;
  }
  fclose (fc);

  list birch;
  birch.read_list(fp, con);

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
        res += birch.check(buff, order, con);
        printf("\n");
        break;
      case command_type::quit:
        break;
      case command_type::insert:
        birch.parse_insert(buf, con);
        break;
      case command_type::del:
        birch.delete_parse(buf, con);
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
