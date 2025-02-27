#include "querry.h" 
#include "solve.h"


io_status solve1(const char *a, const char *b, char *s, char *t, int m, int * r) {
  querry_1 quartz(m);
  io_status read = quartz.initialize(s, t);
  if (read != io_status::success) return read;
  FILE *fin = fopen(a, "r");
  if (fin == nullptr) return io_status::read;
  FILE *fout = fopen(b, "w");
  if (fout == nullptr) {fclose (fin); return io_status::read;}


  const int len = 1234;
  char buffer[len];
  char buffer2[len];
  while(fgets(buffer, sizeof(buffer), fin)) {
    for (int j = 0; j < len; j++) {const char c = buffer[j]; if (c != '\n') buffer2[j] = c; else {buffer[j] = '\0'; buffer2[j] = c;}}
    char *start = strtok(buffer, t);
    while (start) {
      if (quartz.search(start) == 1) {
        (*r)++;
        fputs(buffer2, fout);
        break;
      }
      start = strtok(nullptr, t);
    }
  }

  fclose(fin);
  fclose(fout);
  return io_status::success;
}

io_status solve2(const char *a, const char *b, char *s, char *t, int * r) {
  querry_2 quartz;
  io_status read = quartz.initialize(s, t);
  if (read != io_status::success) return read;
  FILE *fin = fopen(a, "r");
  if (fin == nullptr) return io_status::read;
  FILE *fout = fopen(b, "w");
  if (fout == nullptr) {fclose (fin); return io_status::read;}


  const int len = 1234;
  char buffer[len];
  char buffer2[len];
  int flag = -1;
  while(fgets(buffer, sizeof(buffer), fin)) {
    for (int j = 0; j < len; j++) {const char c = buffer[j]; if (c != '\n') buffer2[j] = c; else {buffer[j] = '\0'; buffer2[j] = c;}}
    char *start = strtok(buffer, t);
    while (start) {
      flag = 0;
      if (quartz.search(start) != 1) {
        flag = 1;
        break;
      }
      start = strtok(nullptr, t);
    }
    if (flag == 0) {
      (*r)++;
      fputs(buffer2, fout);
    }
  }

  fclose(fin);
  fclose(fout);
  return io_status::success;
}
