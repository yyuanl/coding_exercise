#include<iostream>
#include"Queue.h"
//using namespace std;
int main(){
    Queue my_queue;
    for(int i=0; i < 10; i++){
        my_queue.push(i + 1);
    }
    my_queue.pop();
    my_queue.push(101);
    while(!my_queue.my_empty()){
        cout<< "the first element is :" << my_queue.fist_ele() << endl;
        cout<< "the end element is :" << my_queue.end_ele()<< endl;
        cout<< "the size of queue is :" << my_queue.size() << "\n" << endl;
        my_queue.pop();
    }  
    return 0;
}