#ifndef RB_TREE_H
#define RB_TREE_H

#include "student.h"

  enum color {
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
    color color = invalid;
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
      delte_subtree(root);
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
        if (root == nullptr) {root = curr; root->color = color::black;}
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
      if (curr->color == color::red) {
        printf("\033[0;31m");
        curr->print (fp);
        printf("\033[0m");
      }
      else {
        printf("\033[0;30m");
        curr->print (fp);
        printf("\033[0m");
      }
      print_subtree (curr->left, level + 1, r, fp);
      print_subtree (curr->right, level + 1, r, fp);
  }
    void add_node_subtree(rb_tree_node<T> *curr, rb_tree_node<T> *x) {
      if (*x < *curr) {
        if (curr->left == nullptr) {
          curr->left = x;
          (curr->left)->color = color::red;
          (curr->left)->parent = curr;
          balance_subtree(curr->left);
        }
        else add_node_subtree(curr->left, x);
      }
      else {
        if (curr->right == nullptr) {
          curr->right = x;
          (curr->right)->color = color::red;
          (curr->right)->parent = curr;
          balance_subtree(curr->right);
        }
        else add_node_subtree(curr->right, x);
      }
    }
    void balance_subtree(rb_tree_node<T> *curr) {
      if (curr == nullptr || (curr && curr->color == color::black)) return;
      if (curr == root) {
        root->color = color::black;
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
      if (grfather->color == color::black && father->color == color::red && uncle && uncle->color == color::red) {
        father->color = color::black;
        uncle->color = color::black;
        grfather->color = color::red;
        balance_subtree(grfather);
      }

      // черный дядя
      if ((uncle == nullptr || (uncle && uncle->color == color::black)) && father->color == color::red && grfather->color == color::black) {
        int flag = 0;
        if (grfather-> left == father && father->right == curr) {
          rb_tree_node<T> *temp2 = curr->left;
          grfather->left = curr; curr->parent = grfather;
          curr->left = father; father->parent = curr;
          father->right = temp2; temp2->parent = father;
          flag = 1;
        }
        if (grfather->right == father && father->left == curr) {
          rb_tree_node<T> *temp2 = curr->right;
          grfather->right = curr; curr->parent = grfather;
          curr->right = father; father->parent = curr;
          father->left = temp2; temp2->parent = father;
          flag = 1;
        }
        rb_tree_node<T> *x;
        rb_tree_node<T> *p;
        if (flag == 0) {
          x = curr;
          p = father;
        }
        else {
          x = father;
          p = curr;
        }
        if (grfather->right == uncle) {
          rb_tree_node<T> *c = p->right;
          rb_tree_node<T> *grr= grfather->parent;
          grfather->left = c; c->parent = grfather;
          grfather->right = uncle; uncle->parent = grfather;
          p->parent = grr;
          p->right = grfather; grfather->parent = p;
          p->color = color::black;
          grfather->color = color::red;
        }
        else {
          rb_tree_node<T> *c = p->left;
          rb_tree_node<T> *grr= grfather->parent;
          grfather->right = c; c->parent = grfather;
          grfather->left = uncle; uncle->parent = grfather;
          p->parent = grr;
          p->left = grfather; grfather->parent = p;
          p->color = color::black;
          grfather->color = color::red;
        }
      }
    }

};


#endif
