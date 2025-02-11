#include "student.h"
#include "rb_tree.h"

int main(int argc, char* argv[]) {
  char *filename = 0;
  int r, k;
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
      return -3;
    case io_status::format:
      printf("Wrong format of data\n");
      delete birch;
      return -4;
    case io_status::memory:
      printf("Not enough memory\n");
      delete birch;
      return -5;
  }
  birch->print(r);


  delete birch;
  fclose(fp);
  return 0;
}
