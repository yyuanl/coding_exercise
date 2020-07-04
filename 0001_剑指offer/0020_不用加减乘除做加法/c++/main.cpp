#include<iostream>
using namespace std;
int Add(int num1, int num2){
    int temp;
    int carray;

    while(true){
        temp = num1 ^ num2; //不带进位加法
        carray = (num1 & num2) << 1;  // 进位
        if(carray == 0)  // 进位为0推出
            break;
        num1 = temp;
        num2 = carray;

    }
    return temp;
}
int main(){
    cout<<"12 + 56 = "<<Add(12, 56)<<endl;
    return 0;
}