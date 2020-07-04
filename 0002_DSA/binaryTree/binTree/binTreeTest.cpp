#include <iostream>
#include "BinTree.h"
#include "D:\coding_exercise\0002_DSA\shareClass\visit.h"

using namespace std;

int main(){
    BinTree<int> bintree;
    BinNodePosi(int) n0 = bintree.insertAsRoot(8);
    BinNodePosi(int) n1 = bintree.insertAsLC(n0,9);
    BinNodePosi(int) n2 = bintree.insertAsRC(n0,10);
    bintree.insertAsLC(n1,2);
    bintree.insertAsRC(n1,6);
    bintree.insertAsRC(n2,5);
    Visit<int>vst;
    bintree.travPre(vst);
    bintree.travIn(vst);
    bintree.travPost(vst);
    bintree.travLevel(vst);
    

    return 0;
}