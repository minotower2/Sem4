#include "querry.h" 
#include "solve.h"
#include <vector>


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

io_status solve4(const char *a, const char *b, char *s, char *t, char *x, int *r) {
  FILE *fin = fopen(a, "r");
  if (fin == nullptr) return io_status::read;
  FILE *fout = fopen(b, "w");
  if (fout == nullptr) {fclose (fin); return io_status::read;}

  std::vector<char*> words;
  std::vector<char*> conditions;

  char *start = strtok(s, t);
  while (start){
    words.push_back(start);
    start = strtok(nullptr, t);
  }
  start = strtok(x, t);
  while (start){
    conditions.push_back(start);
    start = strtok(nullptr, t);
  }
  long unsigned int len = words.size();
  if (len != conditions.size()) {fclose(fin); fclose(fout); return io_status::format;}

  const int length = 1234;
  char buffer[length];
  char buffer2[length];
  int flag = 0;
  while(fgets(buffer, sizeof(buffer), fin)) {
    for (int j = 0; j < length; j++) {const char c = buffer[j]; if (c != '\n') buffer2[j] = c; else {buffer[j] = '\0'; buffer2[j] = c;}}
    start = strtok(buffer, t);
    while (start) {
      flag = 0;
      for (long unsigned int j = 0; j < len; j++) {
        if (strcmp(conditions[j], "<") == 0) {
          if (strcmp(start, words[j]) < 0) {
            (*r)++;
            fputs(buffer2, fout);
            flag = 1;
            break;
          }
        }
        else if (strcmp(conditions[j], ">") == 0) {
          if (strcmp(start, words[j]) > 0) {
            (*r)++;
            fputs(buffer2, fout);
            flag = 1;
            break;
          }
        }
        else if (strcmp(conditions[j], "<=") == 0) {
          if (strcmp(start, words[j]) <= 0) {
            (*r)++;
            fputs(buffer2, fout);
            flag = 1;
            break;
          }
        }
        else if (strcmp(conditions[j], ">=") == 0) {
          if (strcmp(start, words[j]) >= 0) {
            (*r)++;
            fputs(buffer2, fout);
            flag = 1;
            break;
          }
        }
        else if (strcmp(conditions[j], "=") == 0) {
          if (strcmp(start, words[j]) == 0) {
            (*r)++;
            fputs(buffer2, fout);
            flag = 1;
            break;
          }
        }
        else if (strcmp(conditions[j], "<>") == 0) {
          if (strcmp(start, words[j]) != 0) {
            (*r)++;
            fputs(buffer2, fout);
            flag = 1;
            break;
          }
        }
        else {
          fclose (fin);
          fclose (fout);
          return io_status::format;
        }
      }
      if (flag == 1) break;
      start = strtok(nullptr, t);
    }
  }

  fclose(fin);
  fclose(fout);
  return io_status::success;
}

io_status solve5(const char *a, const char *b, char *s, char *t, char *x, int *r) {
  FILE *fin = fopen(a, "r");
  if (fin == nullptr) return io_status::read;
  FILE *fout = fopen(b, "w");
  if (fout == nullptr) {fclose (fin); return io_status::read;}

  std::vector<char*> words;
  std::vector<char*> conditions;

  char *start = strtok(s, t);
  while (start){
    words.push_back(start);
    start = strtok(nullptr, t);
  }
  start = strtok(x, t);
  while (start){
    conditions.push_back(start);
    start = strtok(nullptr, t);
  }
  long unsigned int len = words.size();
  if (len != conditions.size()) {fclose(fin); fclose(fout); return io_status::format;}

  const int length = 1234;
  char buffer[length];
  char buffer2[length];
  int flag = 0;
  while(fgets(buffer, sizeof(buffer), fin)) {
    for (int j = 0; j < length; j++) {const char c = buffer[j]; if (c != '\n') buffer2[j] = c; else {buffer[j] = '\0'; buffer2[j] = c;}}
    start = strtok(buffer, t);
    flag = 1;
    while (start) {
      for (long unsigned int j = 0; j < len; j++) {
        if (strcmp(conditions[j], "<") == 0) {
          if (strcmp(start, words[j]) < 0) {
            flag *= 1;
          }
          else {
            flag *= 0;
          }
        }
        else if (strcmp(conditions[j], ">") == 0) {
          if (strcmp(start, words[j]) > 0) {
            flag *= 1;
          }
          else {
            flag *= 0;
          }
        }
        else if (strcmp(conditions[j], "<=") == 0) {
          if (strcmp(start, words[j]) <= 0) {
            flag *= 1;
          }
          else {
            flag *= 0;
          }
        }
        else if (strcmp(conditions[j], ">=") == 0) {
          if (strcmp(start, words[j]) >= 0) {
            flag *= 1;
          }
          else {
            flag *= 0;
          }
        }
        else if (strcmp(conditions[j], "=") == 0) {
          if (strcmp(start, words[j]) == 0) {
            flag *= 1;
          }
          else {
            flag *= 0;
          }
        }
        else if (strcmp(conditions[j], "<>") == 0) {
          if (strcmp(start, words[j]) != 0) {
            flag *= 1;
          }
          else {
            flag *= 0;
          }
        }
        else {
          fclose (fin);
          fclose (fout);
          return io_status::format;
        }
      }
      start = strtok(nullptr, t);
    }
    if (flag == 1) {
      (*r)++;
      fputs(buffer2, fout);
      break;
    }
  }

  fclose(fin);
  fclose(fout);
  return io_status::success;
}


io_status solve6(const char *a, const char *b, char *s, char *t, int *r) {
  const int length = 1234;
  if (s[0] == '\0') return io_status::success;
  FILE *fin = fopen(a, "r");
  if (fin == nullptr) return io_status::read;
  FILE *fout = fopen(b, "w");
  if (fout == nullptr) {fclose (fin); return io_status::read;}

  char buffer[length];
  char keys[length];
  int j = 0, k = 0;
  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    if (s[i] == '\\' && s[i+1] == '\\') {
      buffer[j++] = '\\';
      keys[k++] = '0';
      i++;
    }
    else if (s[i] == '\\' && s[i+1] == '_') {
      buffer[j++] = '_';
      keys[k++] = '0';
      i++;
    }
    else if (s[i] == '\\' && s[i+1] == '\0') {
      fclose(fin);
      fclose(fout);
      return io_status::format;
    }
    else if (s[i] == '\\') {
      buffer[j++] = s[i+1];
      keys[k++] = '0';
      i++;
    }
    else if (s[i] == '_'){
      buffer[j++] = s[i];
      keys[k++] = '1';
    }
    else {
      int hay = 0;
      for (int j = 0; t[j]; j++) {
        if (t[j] == s[i]) {
          hay = 1;
          break;
        }
      }
      if (hay == 0) {
        buffer[j++] = s[i];
        keys[k++] = '0';
      }
      else {
        buffer[j++] = s[i];
        keys[k++] = '2';
      }
    }
  }
  buffer[j] = '\0';
  keys[k] = '\0';

  char buffer2[length];
  char buffer3[length];
  int flag = -1;
  while(fgets(buffer2, sizeof(buffer2), fin)) {
    for (int j = 0; j < length; j++) {const char c = buffer2[j]; if (c != '\n') buffer3[j] = c; else {buffer2[j] = '\0'; buffer3[j] = c;}}
    char *start = strtok(buffer2, t);
    while(start) {
      int j = 0;
      while(keys[j]) {
        flag = 0;
        for (; keys[j] == '2'; j++);
        for(int k = 0; (keys[j] == '0' || keys[j] == '1'); j++, k++) {
          if (start[k] == '\0') {
            flag = 1;
          }
          if (keys[j] == '0') {
            if (buffer[j] != start[k]) {
              flag = 1;
            }
          }
          if ((keys[j+1] == '\0' || (keys[j+1] && keys[j+1] == '2')) && (start[k+1] != '\0')) {
            flag = 1;
          }
        }
        if (flag == 0) break;
      }

      if (flag == 0) {
        (*r)++;
        fputs(buffer3, fout);
        break;
      }
      start = strtok(nullptr, t);
    }

  }
  fclose(fin);
  fclose(fout);
  return io_status::success;
}


io_status solve8(const char *a, const char *b, char *s, char *t, int *r) {
  const int length = 1234;
  if (s[0] == '\0') return io_status::success;
  FILE *fin = fopen(a, "r");
  if (fin == nullptr) return io_status::read;
  FILE *fout = fopen(b, "w");
  if (fout == nullptr) {fclose (fin); return io_status::read;}

  char buffer[length];
  char buffercopy[length];
  char keys[length];
  int j = 0, k = 0, l = 0;
  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    if (s[i] == '\\' && s[i+1] == '\\') {
      buffer[j++] = '\\';
      buffercopy[l++] = '\\';
      keys[k++] = '0';
      i++;
    }
    else if (s[i] == '\\' && s[i+1] == '[') {
      buffer[j++] = '[';
      buffercopy[l++] = '[';
      keys[k++] = '0';
      i++;
    }
    else if (s[i] == '\\' && s[i+1] == ']') {
      buffer[j++] = ']';
      buffercopy[l++] = ']';
      keys[k++] = '0';
      i++;
    }
    else if ((s[i] == '\\' && s[i+1] == '\0') || (s[i] == '[' && s[i+1] == '\0') || (s[i] == '[' && s[i+2] != '-') || (s[i] == '[' && s[i+3] == '\0') || (s[i] == '[' && s[i+4] != ']')) {
      fclose(fin);
      fclose(fout);
      return io_status::format;
    }
    else if (s[i] == '\\') {
      buffer[j++] = s[i+1];
      buffercopy[l++] = s[i+1];
      keys[k++] = '0';
      i++;
    }
    else if (s[i] == '['){
      buffer[j++] = s[i+1];
      buffercopy[l++] = s[i+3];
      keys[k++] = '1';
      i+=4;
    }
    else {
      int hay = 0;
      for (int j = 0; t[j]; j++) {
        if (t[j] == s[i]) {
          hay = 1;
          break;
        }
      }
      if (hay == 0) {
        buffer[j++] = s[i];
        buffercopy[l++] = s[i];
        keys[k++] = '0';
      }
      else {
        buffer[j++] = s[i];
        buffercopy[l++] = s[i];
        keys[k++] = '2';
      }
    }
  }
  buffer[j] = '\0';
  keys[k] = '\0';
  buffercopy[l] = '\0';


  char buffer2[length];
  char buffer3[length];
  int flag = -1;
  while(fgets(buffer2, sizeof(buffer2), fin)) {
    for (int j = 0; j < length; j++) {const char c = buffer2[j]; if (c != '\n') buffer3[j] = c; else {buffer2[j] = '\0'; buffer3[j] = c;}}
    char *start = strtok(buffer2, t);
    while(start) {
      int j = 0;
      while(keys[j]) {
        flag = 0;
        for (; keys[j] == '2'; j++);
        for(int k = 0; (keys[j] == '0' || keys[j] == '1'); j++, k++) {
          if (start[k] == '\0') {
            flag = 1;
          }
          if (keys[j] == '0') {
            if (buffer[j] != start[k]) {
              flag = 1;
            }
          }
          if ((keys[j+1] == '\0' || (keys[j+1] && keys[j+1] == '2')) && (start[k+1] != '\0')) {
            flag = 1;
          }
          if (keys[j] == 1) {
            if (start[k] > buffercopy[j] || start[k] < buffer[j]) {
              flag = 1;
            }
          }
        }
        if (flag == 0) break;
      }

      if (flag == 0) {
        (*r)++;
        fputs(buffer3, fout);
        break;
      }
      start = strtok(nullptr, t);
    }

  }
  fclose(fin);
  fclose(fout);
  return io_status::success;
}

