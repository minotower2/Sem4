#ifndef COMMAND
#define COMMAND

#include "record.h"

class command : public record {
  private:
    condition c_name = condition::none;
    condition c_phone = condition::none;
    condition c_group = condition::none;
  public:
    command() = default;
    ~command() = default;
    bool parse(const char * string) {
      char buffer[LEN];
      int flag = 0;
      strcpy(buffer, string);
      char *s = strtok(buffer, " ");
      if (s == nullptr) return false;
      if (strcmp(s, "phone") == 0) flag = 1;
      else if (strcmp(s, "group") == 0) flag = 2;
      else if (strcmp(s, "name") == 0) flag = 3;
      else return false;

      s = strtok(nullptr, " ");
      if (s == nullptr) return false;
      switch (flag) {
        case 1:
          if (strcmp(s, "=") == 0) c_phone = condition::eq;
          else if (strcmp(s, "<>") == 0) c_phone = condition::ne;
          else if (strcmp(s, "<") == 0) c_phone = condition::lt;
          else if (strcmp(s, ">") == 0) c_phone = condition::gt;
          else if (strcmp(s, "<=") == 0) c_phone = condition::le;
          else if (strcmp(s, ">=") == 0) c_phone = condition::ge;
          else if (strcmp(s, "like") == 0) c_phone = condition::like;
          else return false;
          break;
        case 2:
          if (strcmp(s, "=") == 0) c_group = condition::eq;
          else if (strcmp(s, "<>") == 0) c_group = condition::ne;
          else if (strcmp(s, "<") == 0) c_group = condition::lt;
          else if (strcmp(s, ">") == 0) c_group = condition::gt;
          else if (strcmp(s, "<=") == 0) c_group = condition::le;
          else if (strcmp(s, ">=") == 0) c_group = condition::ge;
          else if (strcmp(s, "like") == 0) c_group = condition::like;
          else return false;
          break;
        case 3:
          if (strcmp(s, "=") == 0) c_name = condition::eq;
          else if (strcmp(s, "<>") == 0) c_name = condition::ne;
          else if (strcmp(s, "<") == 0) c_name = condition::lt;
          else if (strcmp(s, ">") == 0) c_name = condition::gt;
          else if (strcmp(s, "<=") == 0) c_name = condition::le;
          else if (strcmp(s, ">=") == 0) c_name = condition::ge;
          else if (strcmp(s, "like") == 0) c_name = condition::like;
          else return false;
          break;
        default:
          return false;
      }


      s = strtok(nullptr, " ");
      if (s == nullptr) return false;
      int temp;
      switch(flag) {
        case 1:
          if (sscanf(s, "%d", &temp) != 1) return false;
          init(nullptr, temp, 0);
          break;
        case 2:
          if (sscanf(s, "%d", &temp) != 1) return false;
          init(nullptr, 0, temp);
          break;
        case 3:
          for (int j = 0 ; j < LEN; j++) if (s[j] == '\n') s[j] = '\0';
          init(s, 0 ,0);
          break;
        default:
          return false;
      }
      return true;
    }
    void print(FILE *fp = stdout) {
      char s1[5] = {0};
      switch(c_name) {
        case condition::eq:
          s1[0] = '=';
          break;
        case condition::ne:
          s1[0] = '<';
          s1[1] = '>';
          break;
        case condition::gt:
          s1[0] = '>';
          break;
        case condition::ge:
          s1[0] = '>';
          s1[1] = '=';
          break;
        case condition::lt:
          s1[0] = '<';
          break;
        case condition::le:
          s1[0] = '<';
          s1[1] = '=';
          break;
        case condition::none: {
          const char *none = "none";
          strcpy(s1, none);
          break;
        }
        case condition::like: {
          const char *like = "like";
          strcpy(s1, like);
          break;
        }
      }
      char s2[5] = {0};
      switch(c_group) {
        case condition::eq:
          s2[0] = '=';
          break;
        case condition::ne:
          s2[0] = '<';
          s2[1] = '>';
          break;
        case condition::gt:
          s2[0] = '>';
          break;
        case condition::ge:
          s2[0] = '>';
          s2[1] = '=';
          break;
        case condition::lt:
          s2[0] = '<';
          break;
        case condition::le:
          s2[0] = '<';
          s2[1] = '=';
          break;
        case condition::none: {
          const char *none = "none";
          strcpy(s2, none);
          break;
        }
        case condition::like: {
          const char *like = "like";
          strcpy(s2, like);
          break;
        }
      }
      char s3[5] = {0};
      switch(c_phone) {
        case condition::eq:
          s3[0] = '=';
          break;
        case condition::ne:
          s3[0] = '<';
          s3[1] = '>';
          break;
        case condition::gt:
          s3[0] = '>';
          break;
        case condition::ge:
          s3[0] = '>';
          s3[1] = '=';
          break;
        case condition::lt:
          s3[0] = '<';
          break;
        case condition::le:
          s3[0] = '<';
          s3[1] = '=';
          break;
        case condition::none: {
          const char *none = "none";
          strcpy(s3, none);
          break;
        }
        case condition::like: {
          const char *like = "like";
          strcpy(s3, like);
          break;
        }
      }
      fprintf(fp, "%s %d %d %s %s %s\n", get_name(), get_group(), get_phone(), s1, s2, s3);
    }
    bool apply (const record& x) {
      if (c_name != condition::none) return compare_name(c_name, x);
      if (c_phone != condition::none) return compare_phone(c_phone, x);
      if (c_group != condition::none) return compare_group(c_group, x);
      return false;
    }
};
#endif
