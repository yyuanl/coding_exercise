#include<iostream>
#include<vector>
using namespace std;
int find_mask(int &num){
    int temp = num;
    if(num == 0)
        return 0;
    int mask = 1;
    
    //如何判断某位是否位1
    while(mask < INT_MAX){
        // cout<<"---------"<<mask<<endl;
        // cout<<"temp & mask is "<<(temp & mask)<<" ,mask is "<<mask<<endl;
        if((temp & mask) == mask){
            break;
        }
        mask <<= 1;
    }
    if(mask > INT_MAX )
        return 0;
    return mask;
}
void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
    if(data.size() < 2)
        return ;
    int xor_result = data[0];
    vector<int>::iterator it = data.begin();
    it ++; 
    // 所有数字异或结果
    while(it != data.end()){
        xor_result = xor_result ^ (*it);
        it++;
    }
    int mask = find_mask(xor_result);  
    cout<<"mask is "<<mask<<endl;
    int first_num = 0;
    int second_num = 0;
    vector<int>::iterator it_temp = data.begin();
    while(it_temp != data.end()){
       
        if(((*it_temp) & mask) == mask){
            first_num = first_num ^ (*it_temp);      
        }else{
            second_num = second_num ^ (*it_temp);
        }
        it_temp++;
    }
    *num1 = first_num;
    *num2 = second_num;
}
int main(){
    int test_array[10] = {2, 4, 5, 2, 3, 5, 6, 7, 4, 6};
    vector<int>test_vector(test_array, test_array + 10);
    int num1;
    int num2;
    FindNumsAppearOnce(test_vector, &num1, &num2);
    cout<<"first number is "<<num1<<" ,sencond number is "<<num2<<endl;
    return 0;
}