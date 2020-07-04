#include <iostream>
#include "Splay.h"
#include "D:\coding_exercise\0002_DSA\shareClass\visit.h"
using namespace std;
int main(){
    Splay<int> splayTest;
    Visit<int> vst;
    // BinNodePosi(int) root = splayTest.insertAsRoot(16);
    // BinNodePosi(int) n1 = splayTest.insertAsLC(root,15);
    // BinNodePosi(int) n2 = splayTest.insertAsLC(n1,6);
    // BinNodePosi(int) n3 = splayTest.insertAsRC(n2,12);
    // BinNodePosi(int) n4 = splayTest.insertAsLC(n2,5);
    // BinNodePosi(int) n5 = splayTest.insertAsLC(n4, 2);
    // 构造极端情况：一撇。使用父类方法，使用自己方法会在插入过程就进行两层伸展。
    splayTest.BST<int>::insertAsRoot(7);
    splayTest.BST<int>::insert(6);
    splayTest.BST<int>::insert(5);
    splayTest.BST<int>::insert(4);
    splayTest.BST<int>::insert(3);
    splayTest.BST<int>::insert(2);
    splayTest.BST<int>::insert(1);

    splayTest.travIn(vst);
    splayTest.travLevel(vst);
    splayTest.search(1);
    splayTest.travIn(vst);
    splayTest.travLevel(vst);
    



    return 0;
}