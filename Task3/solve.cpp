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

char* strtok_custom(char* str, const char* delim) {
  static char* buffer;
  if (str != nullptr) buffer = str;
  buffer += strspn(buffer, delim);
  if (*buffer == '\0') return nullptr;
  char* const tokenBegin = buffer;
  buffer += strcspn(buffer, delim);
  if (*buffer != '\0') *buffer++ = '\0';
  return tokenBegin;
}
