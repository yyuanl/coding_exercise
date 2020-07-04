#include <iostream>
#include "AVL.h"
#include "D:\coding_exercise\0002_DSA\shareClass\visit.h"
using namespace std;
int main(){
    Visit<int> vst;
    AVL<int>avl;
    avl.insert(8);
    avl.insert(5);
    avl.insert(12);
    avl.insert(1);
    avl.insert(6);
    avl.insert(9);
    avl.insert(10);
    avl.insert(15);
    avl.travIn(vst);
    // avl.remove(9);
    // avl.travIn(vst);
    avl.remove(8);
    avl.travIn(vst);
    cout<<avl.root()->data<<endl;
    return 0;
}