#include "AVL.h"
#include <iostream>
#include <list>
#include <vector>
#include <iomanip>
#include <math.h>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

template <typename T>
AVL<T>::AVL() {
  root = 0;
}

template <typename T>
AVL<T>::~AVL() {
  
}

template <typename T>
bool AVL<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void AVL<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>* curr = root;
  Node<T>* prev = root;
  Node<T> * cn = root;
  vector<Node<T>* > order;

  if(curr == 0) {
    root = temp;
    return;
  }
  else {
    while(curr != 0) {
      order.push_back(curr);
      if(prev != 0 && (prev->checkBalance() == 1 || prev->checkBalance() == -1)) {
	cn = prev;
      }
      if(v < curr->getValue()) {
	prev = curr;
	curr = curr->getLeftChild();
      }
      else if(v > curr->getValue()) {
	prev = curr;
	curr = curr->getRightChild();
      }
    }
    if(prev->getValue() > v) {
      prev->setLeftChild(temp);
    }
    else {
      prev->setRightChild(temp);
    }
    for(unsigned int i=0; i<order.size(); i++) {
      order[i]->setBalance(getBalance(order[i]));
    }
    if(cn->checkBalance() == 2) {
      if (cn->getRightChild()->checkBalance() < 0) {
	rr(cn->getRightChild());
      }
      lr(cn);
    }
    else if (cn->checkBalance() == -2) {
      if(cn->getLeftChild()->checkBalance() > 0) {
	lr(cn->getLeftChild());
      }
      rr(cn);
    }
  }
}

template <typename T>
void AVL<T>::remove(T v) {
  Node<T>* curr = root;
  Node<T>* curr2 = root;
  Node<T>* iop = root;
  Node<T>* parent = root;
  vector<Node<T>* > path;

  if(curr->getValue() == v) {
    if(curr->getLeftChild() == 0 && curr->getRightChild() == 0) {
      root = 0;
    }
    else if(curr->getLeftChild() != 0 && curr->getRightChild() == 0) {
      root = curr->getLeftChild();
    }
    else {
      root = curr->getRightChild();
    }
    if(curr->getLeftChild() != 0 && curr->getRightChild() != 0) {
      iop = curr->getLeftChild();
      path.push_back(iop);
      while(iop->getRightChild() != 0) {
	iop = iop->getRightChild();
	path.push_back(iop);
      }
      curr2 = iop;
      while(curr2->getLeftChild() != 0) {
	curr2 = curr2->getLeftChild();
      }
      iop->setRightChild(curr->getRightChild());
      if(curr->getLeftChild() != iop) {
	curr2->setLeftChild(curr->getLeftChild());
	curr->getLeftChild()->setRightChild(0);
      }
      root = iop;
    }
    delete curr;
  }
  else {
    while (curr->getValue() != v && curr != 0) {
      path.push_back(curr);
      if(curr->getValue() < v) {
	curr = curr->getRightChild();
      }
      else {
	curr = curr->getLeftChild();
      }
    }
    if (curr == 0) {
      cout << "not found" << endl;
    }
    parent = parentOf(v, root);
    if(curr->getLeftChild() == 0 && curr->getRightChild() == 0) {
      if(parent->getRightChild() == curr) {
	parent->setRightChild(0);
      }
      else {
	parent->setLeftChild(0);
      }
    }
    else if (curr->getLeftChild() != 0 && curr->getRightChild() == 0) {
      if(parent->getRightChild() == curr) {
	parent->setRightChild(curr->getLeftChild());
      }
      else {
	parent->setLeftChild(curr->getLeftChild());
      }
    }
    else if (curr->getLeftChild() == 0 && curr->getRightChild() != 0){
      if(parent->getRightChild() == curr) {
	parent->setRightChild(curr->getRightChild());
      }
      else {
	parent->setLeftChild(curr->getRightChild());
      }
    }
    else {
      iop = curr->getLeftChild();
      path.push_back(iop);
      while(iop->getRightChild() != 0) {
	iop = iop->getRightChild();
	path.push_back(iop);
      }
      iop->setRightChild(curr->getRightChild());
      curr2 = iop;
      while(curr2->getLeftChild() != 0) {
	curr2 = curr2->getLeftChild();
      }
      if(curr->getLeftChild() != iop) {
	curr2->setLeftChild(curr->getLeftChild());
	curr->getLeftChild()->setRightChild(0);
      }
      else if(parent->getLeftChild() == curr) {
	parent->setLeftChild(iop);
      }
      else {
	parent->setRightChild(iop);
      }
    }
    delete curr;
  }
  for(int i=path.size()-1; i>=0; i--) {
    path.back()->setBalance(getBalance(path.back()));
    int bal = path.back()->checkBalance();
    if(bal == 2) {
      if(path.back()->getRightChild()->checkBalance() < 0) {
	rr(path.back()->getRightChild());
      }
      lr(path.back());
    }
    else if(bal == -2) {
      if(path.back()->getLeftChild()->checkBalance() > 0) {
	lr(path.back()->getLeftChild());
      }
      rr(path.back());
    }
    path.pop_back();
  }
}

template <typename T>
int AVL<T>::height(Node<T>* n) {
  if(n == 0) {
    return 0;
  }
  else {
    return std::max(height(n->getLeftChild()), height(n->getRightChild()))+1;
  }
}

template <typename T>
int AVL<T>::getBalance(Node<T>* n) {
  int right = height(n->getRightChild());
  int left = height(n->getLeftChild());
  return right-left;
}

template <typename T>
Node<T>* AVL<T>::parentOf(T v, Node<T>* n) {
  Node<T>* curr = n;
  while(curr != 0) {
    if((curr->getRightChild() != 0 && curr->getRightChild()->getValue() == v) || (curr->getLeftChild() != 0 && curr->getLeftChild()->getValue() == v)) {
      return curr;
    }
    if(v < curr->getValue()) {
      curr = curr->getLeftChild();
    }
    else {
      curr = curr->getRightChild();
    }
  }
  return curr;
}

template <typename T>
void AVL<T>::rr(Node<T>* n) {
  Node<T>* parent = root;
  Node<T>* lc = n->getLeftChild();
  Node<T>* rc = lc->getRightChild();
  lc->setRightChild(n);
  if(root == n) {
    root = lc;
  }
  else {
    parent = parentOf(n->getValue(), root);
    if(parent->getValue() > n->getValue()) {
      parent->setLeftChild(lc);
    }
    else {
      parent->setRightChild(lc);
    }
  }
  n->setLeftChild(rc);
  n->setBalance(getBalance(n));
  lc->setBalance(getBalance(lc));
  if(lc->getLeftChild() != 0) {
    lc->getLeftChild()->setBalance(getBalance(lc->getLeftChild()));
  }
}

template <typename T>
void AVL<T>::lr(Node<T>* n) {
  Node<T>* parent = root;
  Node<T>* rc = n->getRightChild();
  Node<T>* lc = rc->getLeftChild();
  rc->setLeftChild(n);
  if(root == n) {
    root = rc;
  }
  else {
    parent = parentOf(n->getValue(), root);
    if(parent->getValue() < n->getValue()) {
      parent->setRightChild(rc);
    }
    else {
      parent->setLeftChild(rc);
    }
  }
  n->setRightChild(lc);
  n->setBalance(getBalance(n));
  rc->setBalance(getBalance(rc));
    if(rc->getRightChild() != 0) {
      rc->getRightChild()->setBalance(getBalance(rc->getRightChild()));
    }
}

template <typename T>
void AVL<T>::print() {
  traversalPrint(root);
}

template <typename T>
void AVL<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template <typename T>
void AVL<T>::treePrint(){
  std::list<Node<T>* > s;
  vector<vector<bool> > isPresent;
  vector<vector<T> > levels;
  vector<T> someRows;
  vector<bool> someOtherRow;
  levels.push_back(someRows);
  isPresent.push_back(someOtherRow);

  levels[0].push_back(root->getValue());
  isPresent[0].push_back(true);

  s.push_front(root);

  int currentLevel = 1;
  int nextLevel = 0;
  int depth = 1;

  while(!s.empty()){
    Node<T>* val = s.front();
    s.pop_front();

    currentLevel--;

    vector<T> row;
    vector<bool> otherRow;
    levels.push_back(row);
    isPresent.push_back(otherRow);

    if(val->getLeftChild() != 0){
      s.push_back(val->getLeftChild());
      levels[depth].push_back(val->getLeftChild()->getValue());
      isPresent[depth].push_back(true);
      nextLevel++;
    }
    else{
      isPresent[depth].push_back(false);
    }

    if(val->getRightChild() != 0){
      s.push_back(val->getRightChild());
      levels[depth].push_back(val->getRightChild()->getValue());
      isPresent[depth].push_back(true);
      nextLevel++;
    }
    else{
      isPresent[depth].push_back(false);
    }
    if(currentLevel == 0){
      depth++;
      currentLevel = nextLevel;
      nextLevel = 0;
    }
  }
  int width;

  for(int i=0; i<depth; i++){
    width = pow(1.625, depth-i-1);
    if(isPresent[i][0]){
      cout << std::setw(width) << levels[i][0];
    }
    else{
      cout << std::setw(width) << " ";
    }
    for(int j=1; j < (int)levels[i].size(); j++){
      if(isPresent[i][j]){
	cout << std::setw(pow(1.75, depth-i-1)) << std::setfill(' ') << levels[i][j];
      }
      else{
	cout << std::setw(pow(1.75, depth-i-1)) << std::setfill(' ') << " ";
      }
    }
    cout << endl;
  }
}

template class AVL<int>;
template class AVL<double>;
template class AVL<std::string>;
