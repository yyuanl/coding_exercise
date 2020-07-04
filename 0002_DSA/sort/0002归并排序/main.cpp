#include<iostream>
#include<vector>
using namespace std;
void merge(vector<int> &vec, int lo, int mi, int hi){//假设向量左右两边是有序的，现在要把它按顺序重新排列
    // 注意：都是针对大vectotr操作， 后面三个参数是在不同的区间上操作
    int left_size = mi - lo;
    int right_size = hi - mi;
	int whole_size = hi - lo;
    vector<int> left_vector(left_size); // 不必再新建一个容器装右边的元素。当开始排序右边时，总是选两个序列首部最小的赋值到右边
    for(int i = 0; i < left_size; i++)
        left_vector[i] = vec[lo + i];
    //选小的放入原vec容器
    int j = lo, left_vec_ind = 0, right_vec_ind = mi;
    for(; (left_vec_ind < left_size)&&(right_vec_ind < hi); j++){                    
        if(left_vector[left_vec_ind] < vec[right_vec_ind]){
            vec[j] = left_vector[left_vec_ind];
            left_vec_ind++; 
            cout<<"left:"<<left_vec_ind<<endl;
        }else{
            vec[j] = vec[right_vec_ind];
            right_vec_ind++;
            cout<<"right:"<<right_vec_ind<<endl;
        }          
    }
    // 总有一个先遍历完    
    if(right_vec_ind == hi){
        // cout<<"mi: "<<mi<<"\n"<<"left_vec_ind: "<<left_vec_ind<<"\n"<<"hi: "<<hi<<"\n"<<"j: "<<j<<"\n"<<endl;
        // cout<<"left_size: "<<left_size<<endl;
        // cout<<"right_size: "<<right_size<<endl;
        // cout<<"mi - left_vec_ind======="<<mi - left_vec_ind<<endl;
        // cout<<"hi - j======="<<hi - j<<endl;
		
        while(left_vec_ind < left_size){ // 左边索引应该小于左边向量的长度  总结：索引从0开始的向量，其长度为末尾索引大小，遍历其条件是指示索引j小于长度
			cout<<"--------------"<<j<<endl;
            vec[j++] = left_vector[left_vec_ind++];
			
        }
    }   
}
void mergesort(vector<int> &vec, int lo, int hi){ // 这个函数功能是使得向量有序
   
    if(hi - lo < 2){ // 递归基
        return;
    }else{
        int mi = (lo + hi) / 2;  
        mergesort(vec, lo, mi);  // 使得左边有序
        mergesort(vec, mi, hi);  // 使得右边有序
        merge(vec, lo, mi, hi);  // 把有序的子序列合并起来
    }
    
}

int main(){
    int arr[9] = {0, 100, 12, 6, 0, 98, 17, 130, 20};
    vector<int> test_vector(arr, arr + 9);
    mergesort(test_vector, 0, 9);
    for(int i = 0;i < test_vector.size(); i++)
        cout<<i<<"--"<<test_vector[i]<<endl;
}

