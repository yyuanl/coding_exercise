#ifndef _MINSTACK_
#define _MINSTACK_
#include<stack>
using namespace std;
class MinStack {
    public:
            MinStack();
            void push(const int &value);
            void pop();
            int top();
            int min();
    private:
            stack<int>data_stack;
            stack<int>min_stack;
};
#endif