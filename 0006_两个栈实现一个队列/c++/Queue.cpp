#include"Queue.h"
#include<iostream>

/*
stack1倒入stack2后，stack1变空，stack2的栈顶是队列的头，队列所有元素在stack2中存储；进行插入操作后，stack1不为空，其top是队尾元素；进行删除操作后，stack2元素减少，其top时当前队列头；
总之，stack1装了队列后半部分，stack2装了队列前半部分
*/

void Queue::push(const int &element){
    stack1.push(element);
    cout << "finish to push "<< element << " to queue !"<<endl;
}

int Queue::pop(){
    int temp;
    if(stack2.empty()){
        stack_to_stack(stack1, stack2);     
        temp = stack2.top();      
        stack2.pop();
        cout << "pop finish..." << endl;
        
    }else{
        temp =stack2.top();
        stack2.pop();
        cout << "pop finish..." << endl;
    }
    return temp;
}
int Queue::fist_ele(){
    if(my_empty()){
        cout << "sorry, the queue is empty" << endl;
        return -1;
    }       
    if(!stack2.empty()){
        return stack2.top();
    }else{
        stack_to_stack(stack1, stack2);
        return stack2.top();
    }
}
int Queue::end_ele(){
    if(my_empty())
        return -1;
    if(!stack1.empty()){
        return stack1.top();
    }else{
        stack_to_stack(stack2, stack1);
        return stack1.top();
    }
}
bool Queue::my_empty(){
    if(stack1.empty() && stack2.empty()){
        return true;
    }else{
        return false;
    }
}
int Queue::size(){
    return stack1.size() + stack2.size();

}
void Queue::stack_to_stack(stack<int> &from_stack, stack<int> &to_stack){
    if(!to_stack.empty())
        return ;
    while(!from_stack.empty()){
        to_stack.push(from_stack.top());
        from_stack.pop();
    }
}