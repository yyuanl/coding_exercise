#ifndef _QUEUE_
#define _QUEUE_
#include<stack>
class Queue{
    public:
        void push(const int &element); // 入队
        int pop(); // 出队
        int& fist_ele();  // 返回首元素
        int& end_ele();   //  返回末尾元素
        bool my_empty();     // 判断是否为空
        int size();   //大小
        void stack_to_stack(stack<int> form_stack, stack<int> to_stack);  // 一个栈倒入另一个栈
    private:
        stack <int> stack1;
        stack <int> stack2;
};
#endif