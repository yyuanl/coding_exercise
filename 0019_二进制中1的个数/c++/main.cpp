#include<iostream>
using namespace std;
int  NumberOf1(int n){
    int count = 0;
    unsigned long flag = 1;
    while(flag <= INT_MAX){ //INT_MAX = 2^31 -1  循环执行31次，只判断到第31位
        if((n&flag) != 0){
            count++;
        }
        flag <<=1;  // 算数左移 1 -> 2 -> 4 -> 8, 二进制：1 -> 10 -> 100 -> 1000
    }  //循环结束flag = 2^31

    if((n&flag)==1){  //判断到32位
        count++;
    }
    return count;

}
int main(){

    return 0;
}