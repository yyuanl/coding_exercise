#include<iostream>
#include "List.h"
#include <vector>
using namespace std;
int main(){
    vector<int>vec{1, 5, 6, 78, 26, 3, 26, 50};
    List mylist(vec);

    mylist.print();
    cout<<"\ninsert sorted ..."<<endl;
    mylist.insertSort();
    mylist.print();

    return 0;
}