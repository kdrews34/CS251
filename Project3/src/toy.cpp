#include <iostream>
#include "bst.h"


int main(){
    int x;
    int h;

    bst<int> *t = new bst<int>();

    while( (std::cin >> x)){
        t->insert(x);
    }

    int min = 5;
    int max = 15;

    std::vector<int>* vec = t->extract_range(min, max);

    for (int i = 0; i < vec->size(); i++)
        printf("%d, ", vec[i]);
    printf("\n");

    if(t->size() <= 20) {
      t->inorder();
      t->preorder();
    }

    h = t->height();
    std::cout << "\n#### Reported height of tree:   " << h << "\n";

    delete t;
    
    return 0;
}
