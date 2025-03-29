#ifndef COMMAND
#define COMMAND

#include "record.h"
#include "command_type.h"
enum class operation {
  none,
  land,
  lor,
};

class command : public record {
  private:
    condition c_name = condition::none;
    condition c_phone = condition::none;
    condition c_group = condition::none;
    operation op = operation::none;
    ordering order_by[3] = {ordering::none};
  public:
    ordering * get_ordering() {return order_by;}
    command() = default;
    ~command() = default;
    command_type check_type(const char *buf) {
      char buffer[LEN] = {0};
      strcpy(buffer, buf);
      char *s;
      s = strtok(buffer, " \t\n();");
      if (s == nullptr) return command_type::incorrect;
      if (strcmp(s, "select")==0) return command_type::select;
      if (strcmp(s, "insert")==0) return command_type::insert;
      if (strcmp(s, "delete")==0) return command_type::del;
      if (strcmp(s, "quit")==0) return command_type::quit;
      return command_type::incorrect;
    }
    int is_good() {
      if (c_name == condition::eq && c_phone == condition::none && c_group == condition::none) return 1;
      return 0;
    }

    bool parse(const char * string, ordering *order) {
      char buffer[LEN] = {0};
      strcpy(buffer, string);
      char *s;
      s = strtok(buffer, " ,\t\n;");
      if(s == nullptr) return false;
      s = strtok(nullptr, " ,\t\n;");
      if(s == nullptr) return false;
      if (strcmp(s, "*") == 0) {
        order[0] = ordering::name;
        order[1] = ordering::phone;
        order[2] = ordering::group;
        s = strtok(nullptr, " \t\n;");
        if(s == nullptr) {
          set_name("%");
          c_name = condition::like;
          return true;
        }
        if (strcmp(s, "order") == 0) {
          set_name("%");
          c_name = condition::like;
          goto orderby;
        }
        if (strcmp(s, "where") != 0) return false;
      }
      else {
        if (strcmp(s, "group")==0) {
          order[0] = ordering::group;
        }
        if (strcmp(s, "phone")==0) {
          order[0] = ordering::phone;
        }
        if (strcmp(s, "name")== 0) {
          order[0] = ordering::name;
        }
        s = strtok(nullptr, " ,\t\n;");
        if (s == nullptr) {
          set_name("%");
          c_name = condition::like;
          return true;
        }
        if (strcmp(s, "order") == 0) {
          set_name("%");
          c_name = condition::like;
          goto orderby;
        }
        if (strcmp(s, "where") != 0) {
          if (strcmp(s, "group")==0) {
            order[1] = ordering::group;
          }
          if (strcmp(s, "phone")==0) {
            order[1] = ordering::phone;
          }
          if (strcmp(s, "name")== 0) {
            order[1] = ordering::name;
          }
          s = strtok(nullptr, " ,\t\n;");
          if (s == nullptr) {
            set_name("%");
            c_name = condition::like;
            return true;
          }
          if (strcmp(s, "order") == 0) {
            set_name("%");
            c_name = condition::like;
            goto orderby;
          }
          if (strcmp(s, "where") != 0) {
            if (strcmp(s, "group")==0) {
              order[2] = ordering::group;
            }
            if (strcmp(s, "phone")==0) {
              order[2] = ordering::phone;
            }
            if (strcmp(s, "name")== 0) {
              order[2] = ordering::name;
            }
            s = strtok(nullptr, " \t\n;");
            if (s == nullptr) {
              set_name("%");
              c_name = condition::like;
              return true;
            }
            if (strcmp(s, "order") == 0) {
              set_name("%");
              c_name = condition::like;
              goto orderby;
            }
            if (strcmp(s, "where") != 0) return false;
          }
        }
      }

      if (where_parse(s) == false) return false;
      if (s == nullptr) return true;
orderby:
      s = strtok(nullptr, " \t\n;");
      if (s == nullptr) return true;
      else if (strcmp(s, "order") == 0) {
        s = strtok(nullptr, " \t\n");
        if (s == nullptr) return false;
        if (strcmp(s, "by") != 0) return false;
      }
      else if (strcmp(s, "by") != 0) return false;

      s = strtok(nullptr, " ,\t\n;");
      if(s == nullptr) return false;
      if (strcmp(s, "*") == 0) {
        order_by[0] = ordering::name;
        order_by[1] = ordering::phone;
        order_by[2] = ordering::group;
        return true;
      }
      else {
        if (strcmp(s, "group")==0) {
          order_by[0] = ordering::group;
        }
        if (strcmp(s, "phone")==0) {
          order_by[0] = ordering::phone;
        }
        if (strcmp(s, "name")== 0) {
          order_by[0] = ordering::name;
        }
        s = strtok(nullptr, " ,\t\n;");
        if (s == nullptr) {
          return true;
        }
        else {
          if (strcmp(s, "group")==0) {
            order_by[1] = ordering::group;
          }
          if (strcmp(s, "phone")==0) {
            order_by[1] = ordering::phone;
          }
          if (strcmp(s, "name")== 0) {
            order_by[1] = ordering::name;
          }
          s = strtok(nullptr, " ,\t\n;");
          if (s == nullptr) {
            return true;
          }
          else {
            if (strcmp(s, "group")==0) {
              order_by[2] = ordering::group;
            }
            if (strcmp(s, "phone")==0) {
              order_by[2] = ordering::phone;
            }
            if (strcmp(s, "name")== 0) {
              order_by[2] = ordering::name;
            }
            s = strtok(nullptr, " \t\n;");
            if (s == nullptr) {
              return true;
            }
          }
        }
      }

      return true;
    }

    bool where_parse(char * s){
      int flag = 0;
      s = strtok(nullptr, " \t\n");
      if (s == nullptr) return false;
      if (strcmp(s, "phone") == 0) flag = 1;
      else if (strcmp(s, "group") == 0) flag = 2;
      else if (strcmp(s, "name") == 0) flag = 3;
      else return false;
      s = strtok(nullptr, " \t\n");
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
          else if (strcmp(s, "not") == 0) {
            s = strtok(nullptr, " \t\n");
            if (s == nullptr) return false;
            if (strcmp(s, "like") == 0) c_phone = condition::nlike;
            else return false;
          }
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
          else if (strcmp(s, "not") == 0) {
            s = strtok(nullptr, " \t\n");
            if (s == nullptr) return false;
            if (strcmp(s, "like") == 0) c_group = condition::nlike;
            else return false;
          }
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
          else if (strcmp(s, "not") == 0) {
            s = strtok(nullptr, " \t\n");
            if (s == nullptr) return false;
            if (strcmp(s, "like") == 0) c_name = condition::nlike;
            else return false;
          }
          else return false;
          break;
        default:
          return false;
      }

      s = strtok(nullptr, " \t\n;");
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
          init(s, 0 ,0);
          break;
        default:
          return false;
      }

      s = strtok(nullptr, " \t\n;");
      if (s == nullptr) return true;
      if (strcmp(s, "or") == 0) op = operation::lor;
      else if (strcmp(s, "and") == 0) op = operation::land;
      else if (strcmp(s, "order") == 0) return true;
      else return false;

      flag = 0;
      s = strtok(nullptr, " \t\n");
      if (s == nullptr) return false;
      if (strcmp(s, "phone") == 0) flag = 1;
      else if (strcmp(s, "group") == 0) flag = 2;
      else if (strcmp(s, "name") == 0) flag = 3;
      else return false;
      s = strtok(nullptr, " \t\n");
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
          else if (strcmp(s, "not") == 0) {
            s = strtok(nullptr, " ");
            if (s == nullptr) return false;
            if (strcmp(s, "like") == 0) c_phone = condition::nlike;
            else return false;
          }
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
          else if (strcmp(s, "not") == 0) {
            s = strtok(nullptr, " \t\n");
            if (s == nullptr) return false;
            if (strcmp(s, "like") == 0) c_group = condition::nlike;
            else return false;
          }
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
          else if (strcmp(s, "not") == 0) {
            s = strtok(nullptr, " \t\n");
            if (s == nullptr) return false;
            if (strcmp(s, "like") == 0) c_name = condition::nlike;
            else return false;
          }
          else return false;
          break;
        default:
          return false;
      }

      s = strtok(nullptr, " \t\n;");
      if (s == nullptr) return false;
      switch(flag) {
        case 1:
          if (sscanf(s, "%d", &temp) != 1) return false;
          set_phone(temp);
          break;
        case 2:
          if (sscanf(s, "%d", &temp) != 1) return false;
          set_group(temp);
          break;
        case 3:
          set_name(s);
          break;
        default:
          return false;
      }

      s = strtok(nullptr, " \t\n;");
      if (s == nullptr) return true;
      if (strcmp(s, "or") == 0) op = operation::lor;
      else if (strcmp(s, "and") == 0) op = operation::land;
      else if (strcmp(s, "order") == 0) return true;
      else return false;

      flag = 0;
      s = strtok(nullptr, " \t\n");
      if (s == nullptr) return false;
      if (strcmp(s, "phone") == 0) flag = 1;
      else if (strcmp(s, "group") == 0) flag = 2;
      else if (strcmp(s, "name") == 0) flag = 3;
      else return false;
      s = strtok(nullptr, " \t\n");
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
          else if (strcmp(s, "not") == 0) {
            s = strtok(nullptr, " \t\n");
            if (s == nullptr) return false;
            if (strcmp(s, "like") == 0) c_phone = condition::nlike;
            else return false;
          }
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
          else if (strcmp(s, "not") == 0) {
            s = strtok(nullptr, " \t\n");
            if (s == nullptr) return false;
            if (strcmp(s, "like") == 0) c_group = condition::nlike;
            else return false;
          }
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
          else if (strcmp(s, "not") == 0) {
            s = strtok(nullptr, " \t\n");
            if (s == nullptr) return false;
            if (strcmp(s, "like") == 0) c_name = condition::nlike;
            else return false;
          }
          else return false;
          break;
        default:
          return false;
      }

      s = strtok(nullptr, " \t\n;");
      if (s == nullptr) return false;
      switch(flag) {
        case 1:
          if (sscanf(s, "%d", &temp) != 1) return false;
          set_phone(temp);
          break;
        case 2:
          if (sscanf(s, "%d", &temp) != 1) return false;
          set_group(temp);
          break;
        case 3:
          set_name(s);
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
        case condition::nlike: {
          const char *nike = "nike";
          strcpy(s1, nike);
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
        case condition::nlike: {
          const char *nike = "nike";
          strcpy(s2, nike);
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
        case condition::nlike: {
          const char *nike = "nike";
          strcpy(s3, nike);
          break;
        }
      }
      char s4[5] = {0};
      switch(op) {
        case operation::none: {
          const char *none = "none";
          strcpy(s4, none);
          break;}
        case operation::lor:{
          const char *lor = "lor";
          strcpy(s4, lor);
          break;}
        case operation::land:{
          const char *land = "land";
          strcpy(s4, land);
          break;}
      }
      fprintf(fp, "%s %d %d %s %s %s %s\n", get_name(), get_group(), get_phone(), s1, s2, s3, s4);
    }
    bool apply (const record& x) {
      switch (op) {
        case operation::none:
          {
            if (c_name != condition::none) return compare_name(c_name, x);
            if (c_phone != condition::none) return compare_phone(c_phone, x);
            if (c_group != condition::none) return compare_group(c_group, x);
            return false;
          }
        case operation::lor:
          {
            if ((c_name != condition::none && compare_name(c_name, x)) ||
              (c_phone != condition::none && compare_phone(c_phone, x)) ||
              (c_group != condition::none && compare_group(c_group, x))) return true;
            return false;
          }
        case operation::land:
          {
            if ((compare_name(c_name, x)) &&
              (compare_phone(c_phone, x)) &&
              (compare_group(c_group, x))) return true;
            return false;
          }
      }
      return false;
    }
};
#endif
