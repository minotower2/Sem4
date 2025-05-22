#include "solve.h"
#include <stdio.h>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <utility>
#define LEN 1234

io_status solve1(const char *a, const char *b, int & r) {
  FILE * fr = fopen(a, "r");
  if (fr == nullptr) return io_status::open;
  FILE *fw = fopen(b, "w");
  if (fw == nullptr) {fclose(fr); return io_status::open;}
  std::set < std::string > birch;
  std::string str;

  char buf[LEN];
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    str = buf;
    if (birch.find(str) == birch.end()) {
      birch.insert(str);
      fprintf(fw, "%s\n", buf);
      r++;
    }
  }
  fclose (fw);
  fclose (fr);
  return io_status::success;
}

io_status solve2(const char *a, const char *b, int & r) {
  FILE * fr = fopen(a, "r");
  if (fr == nullptr) return io_status::open;
  FILE *fw = fopen(b, "w");
  if (fw == nullptr) {fclose(fr); return io_status::open;}
  std::map <std::string, int> birch;
  std::string str;

  char buf[LEN];
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    str = buf;
    if (birch.find(str) == birch.end()) {
      birch.insert(std::make_pair(str, 0));
      fprintf(fw, "%s\n", buf);
      r++;
    }
  }
  fclose (fw);
  fclose (fr);
  return io_status::success;
}

io_status solve3(const char *a, const char *b, int & r) {
  FILE * fr = fopen(a, "r");
  if (fr == nullptr) return io_status::open;
  FILE *fw = fopen(b, "w");
  if (fw == nullptr) {fclose(fr); return io_status::open;}
  std::multiset < std::string > birch;
  std::string str;

  char buf[LEN];
  int rep = 0;
  int j = 1;
  while (fgets(buf, LEN, fr) != nullptr) {
    rep = 0;
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    str = buf;
    if(birch.count(str) == 0) r++;
    birch.insert(str);
    auto rep_range = birch.equal_range(str);
    for (auto it = rep_range.first; it != rep_range.second; it++) rep++;
    fprintf(fw, "%d %d %s\n", j, rep, buf);
    j++;
  }
  fclose (fw);
  fclose (fr);
  return io_status::success;
}

io_status solve4(const char *a, const char *b, int & r) {
  FILE * fr = fopen(a, "r");
  if (fr == nullptr) return io_status::open;
  FILE *fw = fopen(b, "w");
  if (fw == nullptr) {fclose(fr); return io_status::open;}
  std::map < std::string, int > birch;
  std::string str;

  char buf[LEN];
  int j = 1;
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    str = buf;
    int count = 1;
    auto it = birch.find(str);
    if(it == birch.end()) {
      r++;
      birch.insert(std::make_pair(str, 1));
    }
    else {
      (it->second)++;
      count = it->second;
    }
    fprintf(fw, "%d %d %s\n", j, count, buf);
    j++;
  }
  fclose (fw);
  fclose (fr);
  return io_status::success;
}

io_status solve5(const char *a, const char *b, const char *c, std::string& t, int & r) {
  FILE * fr = fopen(a, "r");
  if (fr == nullptr) return io_status::open;
  std::set <std::string> birch;
  char buf[LEN];
  char *s;
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    s = strtok(buf, t.c_str());
    while (s != nullptr) {
      birch.insert(s);
      s = strtok(nullptr, t.c_str());
    }
  }
  fclose(fr);
  fr = fopen(b, "r");
  if (fr == nullptr) return io_status::open;
  FILE * fw = fopen(c, "w");
  if (fw == nullptr) return io_status::open;
  char bufcp[LEN];
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
      bufcp[i] = buf[i];
    }
    s = strtok(buf, t.c_str());
    int count = 0;
    while (s != nullptr) {
      if (birch.find(s) != birch.end()) {
        count++;
      }
      s = strtok(nullptr, t.c_str());
    }
    r += count;
    fprintf(fw, "%d %s\n", count, bufcp);
  }
  fclose(fw);
  fclose(fr);
  return io_status::success;
}


io_status solve6(const char *a, const char *b, const char *c, std::string& t, int & r) {
  FILE * fr = fopen(a, "r");
  if (fr == nullptr) return io_status::open;
  std::map <std::string, int> birch;
  char buf[LEN];
  char *s;
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    s = strtok(buf, t.c_str());
    while (s != nullptr) {
      if (birch.count(s) == 0) birch.insert(std::make_pair(s, 0));
      s = strtok(nullptr, t.c_str());
    }
  }
  fclose(fr);
  fr = fopen(b, "r");
  if (fr == nullptr) return io_status::open;
  FILE * fw = fopen(c, "w");
  if (fw == nullptr) return io_status::open;
  char bufcp[LEN];
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
      bufcp[i] = buf[i];
    }
    s = strtok(buf, t.c_str());
    int count = 0;
    while (s != nullptr) {
      if (birch.find(s) != birch.end()) {
        count++;
      }
      s = strtok(nullptr, t.c_str());
    }
    r += count;
    fprintf(fw, "%d %s\n", count, bufcp);
  }
  fclose(fw);
  fclose(fr);
  return io_status::success;
}
