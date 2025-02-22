#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "student.h"
#include <algorithm>

template <class T> class avl_tree;
template <class T>
class avl_tree_node: public T {
  friend class avl_tree<T>;
  private:
    avl_tree_node *left = nullptr;
    avl_tree_node *right = nullptr;
    int balance = 1;
  public:
    avl_tree_node() = default;
    avl_tree_node(const avl_tree_node& x) = delete;
    avl_tree_node(avl_tree_node &&x) : T ((T&&)x) {
      erase_links();
      x.erase_links();
    }
    ~avl_tree_node() {
      erase_links();
    }
    avl_tree_node& operator= (const avl_tree_node& x) = delete;
    avl_tree_node& operator= (avl_tree_node &&x) {
      if (this == &x) return *this;
      (T&&) *this = (T&&) x;
      erase_links();
      x.erase_links();
      return *this;
    }
  private:
    void erase_links() {
      left = nullptr;
      right = nullptr;
    }
};


template <class T>
class avl_tree {
  private:
    avl_tree_node<T> *root = nullptr;
  public:
    avl_tree() = default;
    ~avl_tree() {
      delete_subtree(root);
    }
    avl_tree(const avl_tree&) = delete;
    avl_tree(avl_tree&& x) = delete;
    avl_tree& operator= (const avl_tree& x) = delete;
    avl_tree& operator= (avl_tree&& x) = delete;
    void print (unsigned int r = 10, FILE *fp = stdout) const {
      print_subtree (root, 0, r, fp);
    }
    io_status read (FILE * fp = stdin, unsigned int max_read = -1) {
      avl_tree_node<T> x; unsigned int count = 0;
      while(x.read(fp) == io_status::success && count < max_read) {
        avl_tree_node<T> *curr = new avl_tree_node<T> ();
        *curr = (avl_tree_node<T>&&) x;
        if (curr == nullptr) {
          delete_subtree(root);
          return io_status::memory;
        }
        if (root == nullptr) {root = curr; curr->balance = 0;}
        else add_node_subtree(root, curr, nullptr);
        if (count == max_read) return io_status::success;
      }
      if (!feof(fp)) return io_status::eof;
      return io_status::success;
    }

  private:
    static void delete_subtree(avl_tree_node<T> *curr) {
      if (curr == nullptr) return;
      if (curr->left) delete_subtree(curr->left);
      if (curr->right) delete_subtree(curr->right);
      delete curr;
    }
    static void print_subtree (avl_tree_node<T> * curr, int level, int r, FILE *fp = stdout) {
      if (curr == nullptr || level > r) return;
      int spaces = level * 2;
      for (int i = 0; i < spaces; i++) fprintf (fp, " ");
      curr->print(fp);
      print_subtree (curr->left, level + 1, r, fp);
      print_subtree (curr->right, level + 1, r, fp);
    }
    static int get_balance(avl_tree_node<T> *curr) {
      if (curr == nullptr) return 0;
      else return curr->balance;
    }
    void add_node_subtree(avl_tree_node<T> *curr, avl_tree_node<T> *x, avl_tree_node<T> *prev) {
      if (*x < *curr) {
        if (curr->left == nullptr) {
          curr->left = x;
          curr->balance = 1 + std::max(get_balance(curr->left), get_balance(curr->right));
        }
        else {
          add_node_subtree(curr->left, x, curr);
          curr->balance = 1 + std::max(get_balance(curr->left), get_balance(curr->right));
          int bal = get_balance(curr->left) - get_balance(curr->right);
          if (bal == 2) right_balance(curr, prev);
        }
      }
      else {
        if (curr->right == nullptr) {
          curr->right = x;
          curr->balance = 1 + std::max(get_balance(curr->left), get_balance(curr->right));
        }
        else {
          add_node_subtree(curr->right, x, curr);
          curr->balance = 1 + std::max(get_balance(curr->left), get_balance(curr->right));
          int bal = get_balance(curr->left) - get_balance(curr->right);
          if (bal == -2) left_balance(curr, prev);
        }
      }
    }
    void left_balance(avl_tree_node<T> *curr, avl_tree_node<T> *prev) {
      avl_tree_node<T> *a = curr;
      avl_tree_node<T> *b = curr->right;
      if (b == nullptr) return;
      avl_tree_node<T> *c = b->left;
      int bal = get_balance(b->left) - get_balance(b->right);
      if (bal <= 0) {
        if (prev) {
          if (prev->right == a) prev->right = b;
          else prev->left = b;
        }
        else root = b;
        b->left = a; a->right = c;
        a->balance = 1 + std::max(get_balance(a->right), get_balance(a->left));
        b->balance = 1 + std::max(get_balance(b->left), get_balance(b->right));
      }
      else {
        if (c == nullptr) return;
        avl_tree_node<T> *m = c->left;
        avl_tree_node<T> *n = c->right;
        if (prev) {
          if (prev->right == a) prev->right = c;
          else prev->left = c;
        }
        else root = c;
        c->left = a; c->right = b;
        b->left = n; a->right = m;
        a->balance = 1 + std::max(get_balance(a->right), get_balance(a->left));
        b->balance = 1 + std::max(get_balance(b->left), get_balance(b->right));
        c->balance = 1 + std::max(get_balance(c->left), get_balance(c->right));
      }
    }
    void right_balance(avl_tree_node<T> *curr, avl_tree_node<T> *prev) {
      avl_tree_node<T> *a = curr;
      avl_tree_node<T> *b = curr->left;
      if (b == nullptr) return;
      avl_tree_node<T> *c = b->right;
      int bal = get_balance(b->left) - get_balance(b->right);
      if (bal >= 0) {
        if (prev) {
          if (prev->right == a) prev->right = b;
          else prev->left = b;
        }
        else root = b;
        b->right = a; a->left = c;
        a->balance = 1 + std::max(get_balance(a->right), get_balance(a->left));
        b->balance = 1 + std::max(get_balance(b->left), get_balance(b->right));
      }
      else {
        if (c == nullptr) return;
        avl_tree_node<T> *m = c->left;
        avl_tree_node<T> *n = c->right;
        if (prev) {
          if (prev->right == a) prev->right = c;
          else prev->left = c;
        }
        else root = c;
        c->left = b; c->right = a;
        b->right = m; a->left = n;
        a->balance = 1 + std::max(get_balance(a->right), get_balance(a->left));
        b->balance = 1 + std::max(get_balance(b->left), get_balance(b->right));
        c->balance = 1 + std::max(get_balance(c->left), get_balance(c->right));
      }
    }

  public:
    //==================
    //      Task 1
    //==================

    int solve1(const char * s) {
      int count = 0;
      solve1_recc(s, root, &count);
      return count;

    }
    void solve1_recc(const char *s, avl_tree_node<T> * curr, int* count) {
      if (curr == nullptr) return;
      if (curr->left) solve1_recc(s, curr->left, count);
      if (curr->right) solve1_recc(s, curr->right, count);
      if (curr->left == nullptr && curr->right == nullptr) {
        char *n = curr->get_name();
        if (check(n, s) == 0) *count += 1;
      }
    }
    int check(const char *s1, const char *s2) {
      size_t idx;
      unsigned char a_2[256] = {0};
      int flag = 0;
      for(idx = 0; (s2[idx]); idx++){
        a_2[(unsigned char) s2[idx]] = 1;
      }
      for(idx = 0; s1[idx]; idx++){
        if ((a_2[(unsigned char) s1[idx]]) == 0){
          flag = 1;
          break;
        }
      }
      return flag;
    }

    //==================
    //      Task 2
    //==================

    int solve2(const char *s) {
      return solve2_recc(s, root);
    }
    int solve2_recc(const char *s, avl_tree_node<T> *curr) {
      if (curr == nullptr) return 0;
      int count = std::max(solve2_recc(s, curr->left), solve2_recc(s, curr->right));
      char *n = curr->get_name();
      if (check(n, s) == 0) return count + 1;
      return count;
    }

    //==================
    //      Task 3
    //==================

    int solve3(const char * s) {
      int count = 0;
      (void) s;
      return count;
    }
    //==================
    //      Task 4
    //==================

    int solve4(const char *s) {
      int max = 0;
      for (int i = 0 ; i < root->balance; i++) {
        int count = 0;
        count_nodes_kth_level(root, i, 0, &count, s);
        max = std::max(max, count);
      }
      return max;
    }
    void count_nodes_kth_level(avl_tree_node<T> *curr, int goal, int level, int *count, const char *s) {
      if (curr == nullptr || level > goal) return;
      if (goal == level) {
        char * n = curr->get_name();
        if (check(n, s) == 1) {return;}
        (*count)++;
      }
      count_nodes_kth_level(curr->left, goal, level+1, count, s);
      count_nodes_kth_level(curr->right, goal, level+1, count, s);
    }

    //==================
    //      Task 5
    //==================

    int solve5(const char *s) {
      int max = 0;
      solve5_recc(root, &max, s);
      return max;
    }
    int solve5_recc(avl_tree_node<T> *curr, int *max, const char *s) {
      if (curr == nullptr) return 0;
      int left = solve5_recc(curr->left, max, s);
      int right = solve5_recc(curr->right, max, s);
      int count = left + right;
      char * n = curr->get_name();
      if (check(n, s) == 0) {count++;}
      int dif = left - right;
      if (std::abs(dif) > *max) *max = std::abs(dif);
      return count;
    }
};


#endif
