#ifndef __NODE_H__
#define __NODE_H__

template <typename T>
class Node {
 private:
  T value;
  int bal;
  Node<T>* leftChild;
  Node<T>* rightChild;

 public:
  Node<T>(T v);
  T getValue();
  Node<T>* getLeftChild();
  void setLeftChild(Node<T>* n);
  Node<T>* getRightChild();
  void setRightChild(Node<T>* n);
  void setBalance(int b);
  int checkBalance();
};
#endif
