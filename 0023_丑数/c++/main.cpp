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
    return (*it) * multiplier;
}

int min_three(const int &num1, const int &num2, const int &num3){
    int min_of_two = num1 < num2 ? num1 : num2;
    if(min_of_two < num3){
        return min_of_two;
    }else{
        return num3;
    }
}
void print_vector(vector<int>&vec){
    vector<int>::iterator it = vec.begin();
    while(it != vec.end()){
        cout<<*it<<endl;
        it++;
    }
}

int GetUglyNumber_Solution(int index) {
    if(index == 0)
        return 0;
    vector<int>order_ugly_number;
    order_ugly_number.push_back(1);
    int next_ugly_number;
    int multiply_two;
    int multiply_third;
    int multiply_five;
    // int current_max = order_ugly_number[order_ugly_number.size() - 1];
    while(order_ugly_number.size() < index){
        multiply_two = first_big_max(order_ugly_number, 2);
        multiply_third = first_big_max(order_ugly_number, 3);
        multiply_five = first_big_max(order_ugly_number, 5);
        next_ugly_number = min_three(multiply_two, multiply_third, multiply_five);
        order_ugly_number.push_back(next_ugly_number);
    }
    print_vector(order_ugly_number);
    return order_ugly_number.back();  
}
int main(){
    int n = 120;
    cout<<"the "<<n<<"th ugly number is "<<GetUglyNumber_Solution(n)<<endl;
    return 0;
}