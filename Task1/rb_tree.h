#ifndef RB_TREE_H
#define RB_TREE_H

#include "student.h"

  enum colors {
    invalid,
    red,
    black,
  };

template <class T> class rb_tree;
template <class T>
class rb_tree_node: public T {
  friend class rb_tree<T>;
  private:
    rb_tree_node *left = nullptr;
    rb_tree_node *right = nullptr;
    rb_tree_node *parent = nullptr;
    colors color = invalid;
  public:
    rb_tree_node() = default;
    rb_tree_node(const rb_tree_node& x) = delete;
    rb_tree_node(rb_tree_node &&x) : T ((T&&)x) {
      erase_links();
      x.erase_links();
    }
    ~rb_tree_node() {
      erase_links();
    }
    rb_tree_node& operator= (const rb_tree_node& x) = delete;
    rb_tree_node& operator= (rb_tree_node &&x) {
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
      parent = nullptr;
    }
};


template <class T>
class rb_tree {
  private:
    rb_tree_node<T> *root = nullptr;
  public:
    rb_tree() = default;
    ~rb_tree() {
      delete_subtree(root);
    }
    rb_tree(const rb_tree&) = delete;
    rb_tree(rb_tree&& x) = delete;
    rb_tree& operator= (const rb_tree& x) = delete;
    rb_tree& operator= (rb_tree&& x) = delete;
    void print (unsigned int r = 10, FILE *fp = stdout) const {
      print_subtree (root, 0, r, fp);
    }
    io_status read (FILE * fp = stdin, unsigned int max_read = -1) {
      rb_tree_node<T> x; unsigned int count = 0;
      while(x.read(fp) == io_status::success && count < max_read) {
        rb_tree_node<T> *curr = new rb_tree_node<T> ();
        *curr = (rb_tree_node<T>&&) x;
        if (curr == nullptr) {
          delete_subtree(root);
          return io_status::memory;
        }
        if (root == nullptr) {root = curr; root->color = colors::black;}
        else add_node_subtree(root, curr);
        if (count == max_read) return io_status::success;
      }
      if (!feof(fp)) return io_status::eof;
      return io_status::success;
    }

  private:
    static void delete_subtree(rb_tree_node<T> *curr) {
      if (curr == nullptr) return;
      if (curr->left) delete_subtree(curr->left);
      if (curr->right) delete_subtree(curr->right);
      delete curr;
    }
    static void print_subtree (rb_tree_node<T> * curr, int level, int r, FILE *fp = stdout) {
      if (curr == nullptr || level > r) return;
      int spaces = level * 2;
      for (int i = 0; i < spaces; i++) fprintf (fp, " ");
      curr->print(fp);
      print_subtree (curr->left, level + 1, r, fp);
      print_subtree (curr->right, level + 1, r, fp);
  }
    void add_node_subtree(rb_tree_node<T> *curr, rb_tree_node<T> *x) {
      if (*x < *curr) {
        if (curr->left == nullptr) {
          curr->left = x;
          (curr->left)->color = colors::red;
          (curr->left)->parent = curr;
          balance_subtree(curr->left);
        }
        else add_node_subtree(curr->left, x);
      }
      else {
        if (curr->right == nullptr) {
          curr->right = x;
          (curr->right)->color = colors::red;
          (curr->right)->parent = curr;
          balance_subtree(curr->right);
        }
        else add_node_subtree(curr->right, x);
      }
    }
    void balance_subtree(rb_tree_node<T> *curr) {
      if (curr == nullptr || (curr && curr->color == colors::black)) return;
      if (curr == root) {
        root->color = colors::black;
        return;
      }
      if (curr->parent == nullptr) return;
      rb_tree_node<T> *father = curr->parent;
      if (father->parent == nullptr) return;
      rb_tree_node<T> *grfather = father->parent;
      rb_tree_node<T> *uncle;
      if (grfather->left == father) {
        uncle = grfather->right;
      }
      else {
        uncle = grfather->left;
      }

      // красный дядя
      if (grfather->color == colors::black && father->color == colors::red && uncle && uncle->color == colors::red) {
        father->color = colors::black;
        uncle->color = colors::black;
        grfather->color = colors::red;
        balance_subtree(grfather);
      }

      // черный дядя
      if ((uncle == nullptr || (uncle && uncle->color == colors::black)) && father->color == colors::red && grfather->color == colors::black) {
        int flag = 0;
        if (grfather-> left == father && father->right == curr) {
          rb_tree_node<T> *temp2 = curr->left;
          grfather->left = curr; curr->parent = grfather;
          curr->left = father; father->parent = curr;
          father->right = temp2; if (temp2) temp2->parent = father;
          flag = 1;
        }
        if (grfather->right == father && father->left == curr) {
          rb_tree_node<T> *temp2 = curr->right;
          grfather->right = curr; curr->parent = grfather;
          curr->right = father; father->parent = curr;
          father->left = temp2; if (temp2) temp2->parent = father;
          flag = 1;
        }
        rb_tree_node<T> *p;
        if (flag == 0) {
          p = father;
        }
        else {
          p = curr;
        }
        if (grfather->right == uncle) {
          rb_tree_node<T> *c = p->right;
          rb_tree_node<T> *grr= grfather->parent;
          if (grr && grr->left == grfather) flag = 3;
          if (grr && grr->right == grfather) flag = 4;
          grfather->left = c; if (c) c->parent = grfather;
          grfather->right = uncle; if (uncle) uncle->parent = grfather;
          p->parent = grr;
          p->right = grfather; grfather->parent = p;
          p->color = colors::black;
          grfather->color = colors::red;
          if (grfather == root) root = p;
          if (flag == 3) grr->left = p;
          if (flag == 4) grr->right = p;
          
        }
        else {
          rb_tree_node<T> *c = p->left;
          rb_tree_node<T> *grr= grfather->parent;
          if (grr && grr->left == grfather) flag = 3;
          if (grr && grr->right == grfather) flag = 4;
          grfather->right = c; if (c) c->parent = grfather;
          grfather->left = uncle; if (uncle) uncle->parent = grfather;
          p->parent = grr;
          p->left = grfather; grfather->parent = p;
          p->color = colors::black;
          grfather->color = colors::red;
          if (grfather == root) root = p;
          if (flag == 3) grr->left = p;
          if (flag == 4) grr->right = p;
        }
      }
    }

  public:
    //=========================
    //         Task1
    //=========================

    int solve1(int k) {
      int count = 0;
      solve1_recc(root, k, &count);
      return count;
    }

    int solve1_recc(rb_tree_node<T> *curr, int k, int *count) {
      if (curr == nullptr) return 0;
      int c = solve1_recc(curr->left, k, count) + solve1_recc(curr->right, k, count) + 1;
      if (c <= k) {*count += c;}
      return c;
    }

    //=========================
    //         Task2
    //=========================

    int solve2(int k) {
      int count = 0;
      solve2_recc(root, k, &count);
      return count;
    }

    int count_levels(rb_tree_node<T> *curr, int level, int *num) {
      if (curr == nullptr) return 0;
      if (level > *num) *num = level;
      int count = 1;
      count += count_levels(curr->left, level+1, num);
      count += count_levels(curr->right, level+1, num);
      return count;
    }
    void solve2_recc(rb_tree_node<T> *curr, int k, int *count) {
      if (curr == nullptr) return;
      int c = 0;
      int num = count_levels(curr, 1, &c);
      if (c <= k) {*count += num;}
      solve2_recc(curr->left, k, count);
      solve2_recc(curr->right, k, count);
    }

    //=========================
    //         Task3
    //=========================

    int count_subtree(rb_tree_node<T> *curr) {
      if (curr == nullptr) return 0;
      int count = 1;
      count += count_subtree(curr->left);
      count += count_subtree(curr->right);
      return count;
    }
    void count_nodes_kth_level(rb_tree_node<T> *curr, int goal, int level, int *count) {
      if (curr == nullptr || level > goal) return;
      if (goal == level) (*count)++;
      count_nodes_kth_level(curr->left, goal, level+1, count);
      count_nodes_kth_level(curr->right, goal, level+1, count);
    }
    int solve3(int k) {
      int count = 0;
      solve3_recc(root, k, &count);
      return count;
    }
    int get_height(rb_tree_node<T>*curr) {
      if (curr == nullptr) return 0;
      int count = 1, height, max_height = 0;
      height = get_height(curr->left);
      if (height > max_height) max_height = height;
      height = get_height(curr->right);
      if (height > max_height) max_height = height;
      return count + max_height;
  }
    int check_subtree(rb_tree_node<T> *curr, int k) {
      int height = get_height(curr);
      int count;
      for (int i = 0; i < height; i++) {
        count = 0;
        count_nodes_kth_level(curr, i, 0, &count);
        if (count > k) {
          return -1;
        }
      }
      return 1;
    }
    void solve3_recc(rb_tree_node<T> *curr, int k, int *count) {
      if (curr == nullptr) return;
      int num = 0, c;
      num = check_subtree(curr, k);
      if (num == 1) {
        c = count_subtree(curr);
        (*count) += c;
      }
      solve3_recc(curr->left, k, count);
      solve3_recc(curr->right, k, count);
    }

    //=========================
    //         Task4
    //=========================

    int solve4(int k) {
      int count = 0;
      count_nodes_kth_level(root, k, 0, &count);
      return count;
    }


    //=========================
    //         Task5
    //=========================
    
    int solve5(int k) {
      int count = 0;
      lists_on_kth_level(root, k, 1, &count);
      return count * k;
    }

    void lists_on_kth_level(rb_tree_node<T> *curr, int goal, int level, int *count) {
      if (curr == nullptr || level > goal) return;
      if (goal == level && (curr->left == nullptr) && (curr->right == nullptr)) (*count)++;
      lists_on_kth_level(curr->left, goal, level+1, count);
      lists_on_kth_level(curr->right, goal, level+1, count);
    }

};


#endif
