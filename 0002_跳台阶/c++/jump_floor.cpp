#include<iostream>
using namespace std;
int jump_floor(const int &num){
    int a0 = 0;
    int a1 = 1;
    
    if(num < 1) return 0;
    for(int i = 0; i < num ;i++){
        a1 = a0 + a1;
        a0 = a1 - a0;
    }
    return a1;
}
int main(){
    int num = 5;
    cout<<"jump:"<<jump_floor(num)<<endl;
    return 0;
}