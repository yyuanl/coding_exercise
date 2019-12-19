#include"min_stack.h"
#include<iostream>

MinStack::MinStack(){
    cout<<"instance MinStack.."<<endl;
}
void MinStack::push(const int &value){
    data_stack.push(value);
    if(min_stack.empty()){
        min_stack.push(data_stack.top());
    }else{
        if(value <= min_stack.top()){
            min_stack.push(value);
        }else{
            min_stack.push(min_stack.top());
        }           
    }
}
void MinStack::pop(){
    if(data_stack.empty())
        return ;
    data_stack.pop();
    min_stack.pop();   
}
int MinStack::top(){
    if(data_stack.empty())
        return -1;
    return data_stack.top();
}
int MinStack::min(){
    if(min_stack.empty())
        return -1;
    return min_stack.top();
}