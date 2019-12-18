#include<iostream>
#include<vector>
using namespace std; 
/*
利用冒泡排序
*/
void reOrderArray(vector<int> &array){
    bool is_sorted = false;
    int correct_num = 0;  // 每趟安排好一个偶数至合适的位置
    while(!is_sorted){
        is_sorted = true;
        for(int ix = 0;ix < array.size() - correct_num - 1; ix++){
            if(array[ix] % 2 == 0 && array[ix + 1] % 2 != 0){
                swap(array[ix], array[ix + 1]);
                is_sorted = false;
            }
                
        }
        if(is_sorted == true)
            break;
        correct_num++;
    }
    
}
void print_vector(const vector<int> &vec){
    for(int i =0; i < vec.size(); i++)
        cout<<vec[i]<<" ";
    cout<<"\n";
}
int main(){
    int arr[11] = {1, 4, 3, 4, 8, 10, 13, 11, 0, 6, 17};
    vector<int>vec(arr, arr + 11);
    print_vector(vec);
    reOrderArray(vec);
    print_vector(vec);
    return 0;   
}