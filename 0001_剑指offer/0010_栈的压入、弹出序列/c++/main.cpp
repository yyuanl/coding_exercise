#include<iostream>
#include<stack>
#include<vector>
using namespace std;
bool IsPopOrder(vector<int> pushV,vector<int> popV) {
    /*
    模拟入栈出栈的过程，安装出栈序列，看能执行到哪
    */
    bool is_pop_order = true;
    stack<int>stack_temp;
    vector<int>::iterator it_pushV = pushV.begin();
    vector<int>::iterator it_popV = popV.begin();
    while((it_pushV <= pushV.end()) && (it_popV < popV.end())){
        if((stack_temp.empty() == false)&&(stack_temp.top() == *it_popV)){ //如果某个序列不是出栈序列，该if语句不执行，最终辅助序列有剩余，以此作为判断。
            cout<<"the top value of stack is "<<stack_temp.top()<<",and you want to poped value is "<<*it_popV<<". you can pop it"<<"\n"<<endl;
            stack_temp.pop();
            it_popV++;
        }else{ //首次入栈；不符合出栈要求，就入栈。入栈序列所有序列总会都入栈。
            cout<<"the value that will be pushed is "<<*it_pushV<<"\n"<<endl;
            stack_temp.push(*it_pushV);
            it_pushV++;
            
        }
    }
    if(stack_temp.empty() == false)
        is_pop_order = false;
    return is_pop_order;
  
}



int main(){
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {4, 5, 3, 2, 1};
    int c[] = {4, 3, 5, 1, 2};
    int d[] = {4, 5, 9, 2, 1};
    vector<int>pushV(a, a + 5);
    vector<int>popV1(b, b + 5);
    vector<int>popV2(c, c + 5);
    vector<int>popV3(d, d + 5);

    cout<<"is pop oder? "<<IsPopOrder(pushV, popV1)<<endl;
    cout<<"is pop oder? "<<IsPopOrder(pushV, popV2)<<endl;
    cout<<"is pop oder? "<<IsPopOrder(pushV, popV3)<<endl;


    return 0;
}