#include<iostream>
using namespace std;
int jump_floor_bt(const int &num){
    //维护两个变量，一个记录当前n跳台阶方法，另一个记录之前n-1个跳台阶方法数总和
    int f_n = 0;
    int s_n = 0;
    for(int i = 0;i < num; i++){
        // int f_n_ = f_n;
        // int s_n_ = s_n;
        f_n = s_n + 1;
        s_n = s_n + f_n;
        // cout<<f_n<<"="<<s_n_<<"+"<<1<<endl;
        // cout<<s_n<<"="<<s_n_<<"+"<<f_n<<endl;
    }
    return f_n;
}
int main(){
    int num = 5;
    cout<<"jump:"<<jump_floor_bt(num)<<endl;
    return 0;
}