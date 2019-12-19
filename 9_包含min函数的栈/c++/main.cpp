#include<iostream>
#include"min_stack.h"
using namespace std;
int main(){
    MinStack my_stack; // 调用无参构造函数
    for(int i=5;i<10;i++)
        my_stack.push(i);
    cout<<"the min of stack is "<<my_stack.min()<<endl;
    my_stack.pop();
    my_stack.push(2);
    my_stack.push(4);
    cout<<"the min of stack is "<<my_stack.min()<<endl;

    return 0;
}