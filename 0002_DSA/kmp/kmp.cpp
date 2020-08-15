#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
void buildNext(vector<int> &next, char *P){
    next[0] = -1;
    int j = 0, t = -1;  // t是prefix长度，t = next[j-1]，想从[0, j-1)获得已有的自匹配获得next[j]  j认为是文本串的指针
    while(j < next.size()){
        if(t < 0 || P[j] == P[t]){
            //next[++j] = ++t;
            //优化  如果下一次提供的位置的字符和上次位置的字符相同，则属于多次以卵击石的情况
            j++;t++; next[j] = (P[j] != P[t])?t:next[t];  
        }else{
            t = next[t];
        }
    }
}
int kmp(char *T, char *P){
    int m = strlen(T);
    int n = strlen(P);
    int i = 0, j = 0;
    vector<int>nt(n-1);
    buildNext(nt, P);
    while(i < m && j < n){
        if(j < 0 || T[i] == P[j]){
            i++;j++;
        }else{
            j = nt[j];
        }
    }
    return i-j;
}
int main(){
    char t[] = {'a', 'd', 'a', 'f' , 'g' ,'a', 'i', 'f', 'g', 'a', 'd', 's', 'd', 'f', 'd', 's', 'a','\0'};
    char p[] = {'f', 'g' ,'a', 'i', 'f', 'g', 'a', 'd', 's','\0'};
    int up = strlen(t) - strlen(p);
    cout<<"ret is "<<kmp(t,p)<<endl;
    return 0;
}