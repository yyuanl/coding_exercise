#include <iostream>
#include "BST.h"
#include "D:\coding_exercise\0002_DSA\shareClass\visit.h"
using namespace std;
int main(){
    /*
    BST<int> bstTest;
    Visit<int>vst;
    bstTest.insertAsRoot(8);
    bstTest.insert(5);
    bstTest.insert(12);
    bstTest.insert(1);
    bstTest.insert(6);
    bstTest.insert(9);
    bstTest.insert(15);
    bstTest.insert(10);
    bstTest.travIn(vst);
    cout<<"remove 9"<<endl;
    bstTest.remove(9);
    bstTest.travIn(vst);
    bstTest.insert(9);
    cout<<"after add 9, remove 8"<<endl;
    bstTest.remove(8);
    bstTest.travIn(vst);
    */
   /*一撇型，极端退化为向量*/
    BST<int> bstTest;
    Visit<int>vst;
    bstTest.insertAsRoot(10);
    bstTest.insert(9);
    bstTest.insert(8);
    bstTest.insert(7);
    bstTest.insert(6);
    bstTest.insert(5);
    bstTest.insert(4);
    bstTest.insert(3);
    bstTest.insert(2);
    bstTest.insert(1);
    bstTest.travLevel(vst);
    
    
    
    return 0;
}