#include "AVL.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
  AVL<int>* avl = new AVL<int>();

  avl->insert(4);
  avl->insert(1);
  avl->insert(2);
  cout << "Inserted List: 4, 1, 2" << endl;
  avl->treePrint();

  avl->insert(3);
  avl->insert(15);
  avl->insert(18);
  avl->insert(12);
  cout << "Inserted List: 4, 1, 2, 3, 15, 18, 12" << endl;
  avl->treePrint();

  cout << endl;

  avl->remove(1);
  cout << "Removed 1" << endl;
  avl->treePrint();

  cout << endl;

  avl->remove(18);
  cout << "Removed 18" << endl;
  avl->treePrint();

  cout << endl;

  avl->remove(12);
  cout << "Removed 12" << endl;
  avl->treePrint(); 

  return 0;
}
