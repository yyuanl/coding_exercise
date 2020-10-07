##### 1.换零钱方式的统计

假设有零钱1、5、10、25、50，把100兑换成零钱，有多少种兑换方法？

递归的思想解决。

``````c++
#include <iostream>
using namespace std;
/*
假设零钱排好顺序：coins:[50,25....]
将a块钱兑换成n种（0~n-1）零钱方式数 = 
    a块钱兑换成n-1种（1~n-1）零钱方式数       
+   a - coins[0]兑换成n种（0~n-1）零钱方式数
*/
int coins[] = {50,25,10,5,1};
const int N = 5;
int countChange(int amount,int kinds){  // amount:钱总数  kinds:使用的零钱种类数目
    if(amount == 0){
        return 1;
    }else if(amount < 0 || kinds == 0){
        return 0;
    }
    return countChange(amount, kinds - 1) + countChange(amount - coins[N - kinds], kinds); 
}
int main(){
    cout<<countChange(100, N)<<endl;
    return 0;
}
``````

