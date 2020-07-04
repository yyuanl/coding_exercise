#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


void printVector(vector<int>& v){
    cout<<"----------"<<endl;
    int s = v.size();
    cout<<"[";
    for(int i = 0;i < s;i++)
        cout<<v[i]<<" ";
    cout<<"]\n"<<endl;
}


class Solution {
public:
int NumberOf1Between1AndN_Solution(int n){
    vector<int>bit_n;
    int left = 0,right = 0;
    int temp = n;
    int right_bit_num = 1;
    int res = 0;
    int sum = 0;
    int size;
    while(n){
        bit_n.push_back(n % 10);
        n = n / 10;
    }
    size = bit_n.size();
   
    reverse(bit_n.begin(), bit_n.end());
    
    for(int i = 0;i<size;i++){
        
        res = 0,left = 0, right = 0,right_bit_num=1;
        for(int j = 0;j < i;j++){
            left = left*10 + bit_n[j];
        }
        for(int j = i + 1;j < size;j++){
            right = right * 10 + bit_n[j];
            right_bit_num = right_bit_num * 10;
        }
        res += left*right_bit_num;
        if(bit_n[i] == 1){
            res += right+1;
            
        }else if(bit_n[i] > 1){
            res += right_bit_num;
        }
        sum += res;

    }


    cout<<"res is "<<sum<<endl;
    return sum;
    
}
};
int main(){
    Solution s;
    s.NumberOf1Between1AndN_Solution(10);
    return 0;
}