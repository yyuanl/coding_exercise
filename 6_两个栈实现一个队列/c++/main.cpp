#include<iostream>
#include"Queue.h"
using namespace std;
int main(){
    Queue my_queue = Queue;
    for(int i=0; i < 10; i++){
        my_queue.push(i + 1);
    }
    my_queue.pop();
    my_queue.pop();
    cout<< "the first element is :" << my_queue.fist_ele() << endl;
    return 0;
}