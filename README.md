# coding_exercise

#### 一、需要复习

1. 0008：使用冒泡排序的方法
2. 0011：利用递归倒序输出链表
3. 0014：合并链表
4. 0015：需要记住方法
5. 0020
6. **0022**：还不懂

#### 二、问题

1. 使用c++编码0015_复制复杂链表时，新建一个结点时要使用new这个关键字分配内存，new的具体用法?
2. 0015本地通过，牛客oj没通过。还未查出原因。
3. 0018本地测试同通过，牛客oj提示段错误。还未查出原因。

#### 三、复习

1.树的遍历



#### 三、遇到的一些c/c++用法

关于vector一些方法：

###### 1. 找到vector中某个元素的索引：

find找到某个元素的位置（迭代器），再使用distance。

``````c
vector<int>::iterator it = find(vin.begin(), vin.end(), root_val);
index_root = distance(vin.begin(), it);
``````

###### 2. 利用一个已有的vector,复制到另一个vector:

``````c
vector<int>new_vector;
new_vector.assign(it_left,it_right);//it_left和it_right是已知vector [,)
``````

###### 3. 去重：

``````c++
vector<string>res;
set<string>s(res.begin(), res.end());//利用set给res去重
res.assign(s.begin(), s.end());
``````

###### 4. vector的clear不影响capacity

###### 5. 删除/erase

`v.erase(v.begin()+ixdex);`

也可以删除范围内的元素。

###### 6. pair:

可以使用make_pair或者初始化列表来生成一对pair

``````c++
#include <pair>
#include <vector>
int main(){
	vector<pair<int, int>>test;
	test.push_back(make_pair(2,3));
}
``````

###### 7. unordered_map

```c++
#include <unordered_map>
#include <pair>
#include <vector>
int main(){
	unordered_map<int, vector<pair<int, int>> >test;
	test[1].push_back(make_pair(5,3));// []直接插入 有则直接接入向量
    cout<<test[1][0].first<<" "<<test[1][0].second<<endl;
    test[1].push_back(make_pair(4,3));
    cout<<test[1][0].first<<" "<<test[1][0].second<<endl;
    cout<<test[1][1].first<<" "<<test[1][1].second<<endl;
    test[23].push_back(make_pair(10,5));
    cout<<test[23][0].first<<" "<<test[23][0].second<<endl;
}
```

查看某个key是否存在：`unordered_map<int, char>my_map; my_map[1] = 'a'; my_map.count(1);//1或者0`

###### 8、类内部使用函数指针

``````c++
class Solution {
public:
    // 将下面两个函数声明为静态成员函数
    static bool f1(int currVal, int parentVal){
        return currVal > parentVal;
    }
    static bool f2(int currVal, int parentVal){
        return currVal < parentVal;
    }
    //函数指针作为参数
    void heapAddElem(int ele, bool (*judge_f)(int, int)){ 	
    	judeg_f(1, 2);
    }
    //在成员函数里调用heapAddElem
    void cll_heapAddElem(){
        heapAddElem(2, f1); //类内调用方法
        heapAddElem(3, f2);
    }
  }
//类外调用
Solution test;
test.heapAddElem(5,&Solution::f1);
test.heapAddElem(5,&Solution::f2);//取静态成员函数地址
``````

**在类内部，定义一个compare成员函数，供sort使用，compare必须是静态**：

``````c++
class C{
    public:
    	static bool compare(int a, int b){ return a>b;}
    	void f(vector<int>&v){
            sort(v.begin(), b.end(), compare);
        }
};
``````



###### 9、string转const char*

``````c++
const char* resuChar = str.c_str();
``````

###### 10、**int转string**

`to_string(2);`

###### 11、**string统计某个字符个数**

`count(v.begin(),v.end(), 'a');`

###### 12、**子串**：

``````c++
string st("adfadafdfdfdsfdfd");
string a = st.substr(1, 5); //从索引为1处复制5个[1,1+5)
``````

###### 13、数值型字符串转整形

* “123456”转123456：

  ``````c++
  #include <stdlib.h>
  #include <string>
  string s("123");
  int a = atoi(s.c_str()); //1.atoi 参数要const char*  2. 先要把字符串变为c风格字符串
  ``````

* ‘2’转2：`char a = '2'; int b = a - 0x30;`

* "12:23:34"分别得到“12”、“23”、“34”

  ``````c++
  #include <string>
  #include <sstream>
  string str = "12:34:56";
  for (int i=0; i<str.length(); i++)
  {
      if (str[i] == ':')
          str[i] = ' ';
  }
  vector<int> array;
  stringstream ss(str); // 先转为字符串流
  int temp;
  while (ss >> temp) // 读到空格算一个字符结束。读完返回结束符，-1.
      array.push_back(temp);
  ``````

  **注意，使用`cin>>str;`如果输入“123 456 45”, str只会读入123**，cin是以空格作为一个字符串结束的标志

* 字符串反转

  ``````c++
  string str
  string s(str.rbegin(), str.rend());
  ``````
  
* string转为c风格字符串char a []内

  ``````c++
  string str1;
  cin>>str1;
  char arr_cr[str1.size()];
  memset(arr_cr, 0, sizeof(arr_cr));
  strcpy(arr_cr, str1.c_str());
  ``````


1. c：

   * 比较参数s1 和s2 字符串，比较时会自动忽略大小写的差异相同返回0

     `int strcasecmp (const char *s1, const char *s2);`//忽略大小写

     区别：`int strcmp(const char *str1, const char *str2)`

   * sscanf()函数用于从字符串中读取指定格式的数据，其原型如下：

     `int sscanf (char *str, char * format [, argument, ...]);`

   * `scanf()`格式化输入：`scanf("%d,%d,%d",&a,&b,&c);`  键盘敲入必须带逗号

   * ``````c++
     char cbuf[]={'a', 'b', 'c', 'd', 'e', '\0'};
     char s[] = {'z', 'x', '\0'};
     puts(cbuf); 
     sprintf(cbuf, "%s", s);  
     puts(cbuf); // print "zx"
     ``````

   * ``````c
     inlcude<unistd.h>
     char **environ;  //别的文件使用execve执行程序调用全局环境变量
     ``````

   * ``````c
     //字符数组常用函数：
     strstr();//字串首次出现位置
     strchr();//字符首次出现位置
     strcat();//连接
     index(); // 返回首次出现字符的地址
     ``````

   * 

2. 二维向量：`vector<vector<int> >v(rows, vector<int>(cols));`

3. c++ 父类virtual方法，强制子类重写后调用，具体使用谁的方法，由**对象类型**决定。另外，此时子类对象想调用父类方法必须加上作用域。复杂情况如下：

   ```````c++
   calss BST<T>{
   public:
       virtual insert(){
           /*......*/
           BST<T>::search();
       }
       virtual search(){ // ...}
   };
   calss Splay<T>:public BST<T>{
   public:
       insert(){/*......*/}
       search(){ // ...}
   };
   int main(){
       Splay<int>splayTest;
       splayTest.insert();  //调用Splay的insert()
       splayTest.BST<int>::insert();// 如果BST中的insert里面对search()的调用没有使用作用域，实际将会调用Splay的search()方法，造成错误。本意是子类想调用父类的方法。
       return 0;
   }
   
   ```````



