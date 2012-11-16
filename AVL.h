#ifndef __AVL_H__
#define __AVL_H__

#include "Node.h"
#include <string>

template <typename T>
class AVL {
 private:
  Node<T>* root;
  Node<T>* parentOf(T v, Node<T>* n);
  int getBalance(Node<T>* n);
  int height(Node<T>* n);
  void rr(Node<T>* n);
  void lr(Node<T>* n);
  void traversalPrint(Node<T>* root);

 public:
  AVL<T>();
  ~AVL<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
  void treePrint();
};


#endif
