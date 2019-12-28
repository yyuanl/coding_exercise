#include<iostream>
#include<vector>
using namespace std;
int first_big_max(vector<int> &vec_ugly, int multiplier){
    vector<int>::iterator it = vec_ugly.begin();
    while(it != vec_ugly.end()){

        if((*it) * multiplier > vec_ugly.back()){
            break;
        }else{
            it++;
        }
    }
    
}

int GetUglyNumber_Solution(int index) {
    vector<int>order_ugly_number;
    order_ugly_number.push_back(1);
    int next_ugly_number;
    // int current_max = order_ugly_number[order_ugly_number.size() - 1];
    while(order_ugly_number.size() < index){


    }
    
}
int main(){
    return 0;
}