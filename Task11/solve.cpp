#include "solve.h"
#include <stdio.h>
#include <vector>
#include <list>
#include <string>
#include <cstring>
#include <utility>
#include <algorithm>
#define LEN 1234

io_status solve1(const char *a, const char *b, int & r) {
  FILE * fr = fopen(a, "r");
  if (fr == nullptr) return io_status::open;
  FILE *fw = fopen(b, "w");
  if (fw == nullptr) {fclose(fr); return io_status::open;}
  std::vector < std::pair < std::string, int > > birch;
  std::string str;

  char buf[LEN];
  int j = 0;
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    str = buf;
    std::pair pr = std::make_pair(str, j);
    birch.push_back(pr);
    j++;
  }
  std::sort(birch.begin(), birch.end(), 
      [](const std::pair < std::string, int> & a, const std::pair < std::string, int> & b) {
        return a.first < b.first;
      });
  auto it = unique(birch.begin(), birch.end(), 
      [](const std::pair < std::string, int> & a, const std::pair < std::string, int> & b) {
        return a.first == b.first;
        }
      );
  birch.erase(it, birch.end());
  std::sort(birch.begin(), birch.end(), 
      [](const std::pair < std::string, int> & a, const std::pair < std::string, int> & b) {
        return a.second < b.second;
      });
  for (auto i: birch)  {
    fprintf(fw, "%s\n", (i.first).c_str());
    r++;
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
  std::list < std::pair < std::string, int > > birch;
  std::string str;

  char buf[LEN];
  int j = 0;
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    str = buf;
    std::pair pr = std::make_pair(str, j);
    birch.push_back(pr);
    j++;
  }
  birch.sort(
      [](const std::pair < std::string, int> & a, const std::pair < std::string, int> & b) {
        return a.first < b.first;
        }
      );
  birch.unique(
      [](const std::pair < std::string, int> & a, const std::pair < std::string, int> & b) {
        return a.first == b.first;
        }
      );
  birch.sort(
      [](const std::pair < std::string, int> & a, const std::pair < std::string, int> & b) {
        return a.second < b.second;
        }
      );
  for (auto i: birch)  {
    fprintf(fw, "%s\n", (i.first).c_str());
    r++;
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
  std::vector < std::pair < std::string, std::pair < int, int > > > birch;
  std::string str;

  char buf[LEN];
  int j = 1;
  int flag = 0;
  while (fgets(buf, LEN, fr) != nullptr) {
    flag = 1;
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    str = buf;
    std::pair pr = std::make_pair(j, 1);
    birch.push_back(std::make_pair(str, pr));
    j++;
  }
  if (flag == 1) r = 1;
  else {fclose (fw); fclose(fr); return io_status::success;}
  std::sort(birch.begin(), birch.end(), 
      [](const std::pair < std::string, std::pair < int, int > > & a, const std::pair < std::string, std::pair < int, int > > & b) {
        return a.first < b.first;
      });
  auto prev = begin(birch);
  for (auto it = begin(birch)+1; it != end (birch); ++it) {
    if (prev->first == it->first) ((prev->second).second)++;
    else prev = it;
  }
  auto start = begin(birch);
  for (auto it = begin(birch); it != end(birch); ++it) {
    if (it->first == start->first) (it->second).second = (start->second).second;
    else {start = it; r++;}
  }
  std::sort(birch.begin(), birch.end(), 
       [](const std::pair < std::string, std::pair < int, int > > & a, const std::pair < std::string, std::pair < int, int > > & b) {
        return (a.second).first < (b.second).first;
      });
  for (auto i: birch)  {
    fprintf(fw, "%d %d %s\n", (i.second).first, (i.second).second, (i.first).c_str());
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
  std::list < std::pair < std::string, std::pair < int, int > > > birch;
  std::string str;

  char buf[LEN];
  int j = 1;
  int flag = 0;
  while (fgets(buf, LEN, fr) != nullptr) {
    flag = 1;
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    str = buf;
    std::pair pr = std::make_pair(j, 1);
    birch.push_back(std::make_pair(str, pr));
    j++;
  }
  if (flag == 1) r = 1;
  else {fclose (fw); fclose(fr); return io_status::success;}
  birch.sort(
      [](const std::pair < std::string, std::pair < int, int > > & a, const std::pair < std::string, std::pair < int, int > > & b) {
        return a.first < b.first;
      });
  auto prev = begin(birch);
  for (auto it = ++begin(birch); it != end (birch); ++it) {
    if (prev->first == it->first) ((prev->second).second)++;
    else prev = it;
  }
  auto start = begin(birch);
  for (auto it = ++begin(birch); it != end(birch); ++it) {
    if (it->first == start->first) (it->second).second = (start->second).second;
    else {start = it; r++;}
  }
  birch.sort(
       [](const std::pair < std::string, std::pair < int, int > > & a, const std::pair < std::string, std::pair < int, int > > & b) {
        return (a.second).first < (b.second).first;
      });
  for (auto i: birch)  {
    fprintf(fw, "%d %d %s\n", (i.second).first, (i.second).second, (i.first).c_str());
  }
  fclose (fw);
  fclose (fr);
  return io_status::success;
}

io_status solve5(const char *a, const char *b, const char *c, std::string& t, int & r) {
  FILE * fr = fopen(a, "r");
  if (fr == nullptr) return io_status::open;
  std::vector <std::string> birch;
  char buf[LEN];
  char *s;
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    s = strtok(buf, t.c_str());
    while (s != nullptr) {
      birch.push_back(s);
      s = strtok(nullptr, t.c_str());
    }
  }
  std::sort(birch.begin(), birch.end());
  auto it = std::unique(birch.begin(), birch.end());
  birch.erase(it, birch.end());
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
      if (std::binary_search(birch.begin(), birch.end(), s)) {
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
  std::list <std::string> birch;
  char buf[LEN];
  char *s;
  while (fgets(buf, LEN, fr) != nullptr) {
    for (int i = 0; buf[i]; ++i) {
      if (buf[i] == '\n') buf[i] = '\0';
    }
    s = strtok(buf, t.c_str());
    while (s != nullptr) {
      birch.push_back(s);
      s = strtok(nullptr, t.c_str());
    }
  }
  birch.sort();
  birch.unique();
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
      if (std::find(birch.begin(), birch.end(), s) != birch.end()) {
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
