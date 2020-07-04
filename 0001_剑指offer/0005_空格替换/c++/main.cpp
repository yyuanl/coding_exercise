#include<iostream>
#include<string>
using namespace std;
void replaceSpace(char *p_char, int length){
    if(p_char == NULL)  // 边界检查
        return ;
    // 统计原字符串长度 统计空格个数
    int orig_str_len = 0;
    int space_number = 0;
    while(*p_char != '\0'){
        orig_str_len++;
        if( *p_char == ' ')
            space_number ++;
        p_char++;
    }
    cout << "original string length is : " << orig_str_len << endl;
    cout << "the number of space is : " << space_number << endl;
    int new_str_len = orig_str_len + 2 * space_number; // 替换之后字符串的长度
    // 检查数组是否越界
    if(new_str_len + 1 > orig_str_len)
        return ;
    // 维护两个指针
    char * p_orig_str = p_char + orig_str_len;
    char * p_new_str = p_char + new_str_len;
    while(p_orig_str != p_new_str){ //从后遍历原字符串，构造“新”字符串
        if(* p_orig_str != ' '){
            * p_new_str -- = * p_orig_str;
        }else{
            * p_new_str -- = '0';
            * p_new_str -- = '2';
            * p_new_str -- = '%';
        }
        p_orig_str -- ;       
    }
}
int main(){
    int length = 50;
    char str[] = "we are happy";  // 1. 定义字符串变量，以便修改；char * str = "we are happy" 无法利用指针对其修改，字符串是const, 常量无法修改  2. 字符串默认用字符数组存储 2. 字符数组，打印变量名，输出内容。其他类型数组，输出地址
    cout << "original string is " << str << endl;
    replaceSpace(str, length);
    cout << "replaced string is " << str << endl;
    return 0;
}