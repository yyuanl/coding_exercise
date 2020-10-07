##### 题目举例（leetcode）：

339、零钱兑换；62、不同路径；55、跳跃游戏；152、乘积最大子 数组

##### 一、动态规划步骤：

1. 确定状态，具体根据题意设函数`f(x)`是什么含义。

2. 确定状态转移方程，`f(x)`变为数组`f[x]`。
3. 初始条件，确定边界条件。
4. 计算顺序。

##### 二、动态规划类型：

1. 计数型
2. 最值
3. 存在性

**leetcode 339 零钱兑换**:

	* 如何求最小值：`dp`初始化为“无穷”，一个不可能的大值即可。然后再不断刷新最小值变量。

``````c++
#define MAX amount + 1
vector<int>dp(amount+1, MAX);//初始化为“无穷大”
dp[i] = min(dp[i],dp[i -coins[j]] + 1);
``````

##### 三、坐标型动态规划：

`dp[i]`对应`a[i]`;	

###### 1.最长上升子序列（力扣300）：

* 意思是找出数组a子序列中长度最长的那个，返回其长度。需要区分**字串**和**子序列**。

* 定义状态：`dp[i]`表示以`a[i]`为结尾的子序列的长度。

  所以，初始化为 `dp[i]=1, 0<=i<size`。转移方程为  `dp[i] = max(dp[j]+1), 0<=j<i,nums[j]<nums[i]` 

  ``````c++
  int lengthOfLIS(vector<int>& nums) {
          if(nums.empty())return 0;
          int res = 1;
          vector<int>maxLen(nums.size(), 1);
          for(int i=0 ;i < nums.size();i++){
              for(int j = 0; j < i;j++){
                  if(nums[j] < nums[i]){
                      maxLen[i] = max(maxLen[i], maxLen[j] + 1);
                  }
              }
              res = max(res, maxLen[i]);
          }
          return res;
  }
  ``````

  时间复杂度过大。

* 进阶，重新定义状态：`dp[i]`表示**长度为`i+1`的所有子序列的最后一个元素中最小的那个元素**。将子序列按照长度划分为等价类，只记录等价类中最可能使得子序列再增长的那种情况，即贪心原则。针对当前的元素`nums[i]`，利用二分查找在`dp`中找到第一个>=`nums[i]`的地方，将此处替换为`nums[i]`，这实质上是在一个递增向量中进行查找。

  <img src="./assets/1.png" style="zoom:80%;" />

代码如下：

``````c++
class Solution {
public:
    int binarySearch(vector<int> &v, int lo, int hi, int target){
        int mi;
        while(lo < hi){mi = (lo + hi) >> 1; (target <= v[mi]) ? hi = mi:lo = mi+1; }
        return lo;
    }
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty())return 0;
        vector<int>minSameLen; int ix;
        minSameLen.push_back(nums[0]);
        for(int i = 0; i < nums.size(); i++){
            ix = binarySearch(minSameLen,0,minSameLen.size(), nums[i]);
            if(ix == minSameLen.size()){
                minSameLen.push_back(nums[i]);
            }else{
                minSameLen[ix]=nums[i];
            }
        }
        return minSameLen.size();
    }
};
``````

* **二分查找**：对于一个非递减向量，使用[, )来表示查找范围。最右端是哨兵，可以认为是无穷大值。最左端索引-1，可以认为是无穷小值。

  * 如果要返回不大于target最大值的位置，代码如下：

    ``````c++
    int binSearch(vector<int> &v, int lo, int hi, int target){
    	int mi;
    	while(lo < hi){
    		mi = (lo + hi) >> 1;
    		(target < v[mi]) ? hi = mi : lo = mi+1;
    	}
    	return --lo;
    }
    /*
    查找最后一步，查找区间必然是:[a,b)形态，记a、b的索引分别为i,j，mi = i;
    1. 若target < v[mi],hi压缩到lo, lo = hi = i,返回值为i-1;
       此时，若i-1合法，那么就说明target在i-1索引处。
       		若i-1不合法，当且仅当i-1 = -1,返回无穷的索引-1，说明target < v[0]。返回结果符合语义。
    2. 若target == v[mi],lo压缩到hi，lo = hi = j,返回值为j-1即i,正确。
    3. 若target > v[mi], lo压缩到hi, lo = hi = j,返回i,符合语义。
    
    总之，如果v中有和target相等的值会准确返回，如果位于v中紧邻两个值构成的区间，则返回左区间值，即小于target的最大值。特别的，如果target属于(-infinity, v[0])，此时返回-1，如果target属于[v.back(), +infinity)，此时返回v.size()-1。
    */
    ``````

  * 同样的，如果要返回不小于最小值的位置，代码如下：

    ``````c++
    int binSearch(vector<int> &v, int lo, int hi, int target){
    	int mi;
    	while(lo < hi){
    		mi = (lo + hi) >> 1;
    		(target <= v[mi]) ? hi = mi : lo = mi+1;
    	}
    	return lo;
    }
    /*
    如果target == v[i],返回i; 在程序运行过程中有段时间对[v[i],v[hi])压缩hi.
    如果target属于(-infinty, v[0])返回0；
    如果target属于[v[i], v[j])返回j;
    如果target属于[v.back(),+infinity)返回v.size();
    */
    ``````

  * **经过对向量两边进行处理，target总在一个连续元素组成的区间内，最终都有lo==hi**。依此选择合适的方法。

###### 2.最小路径和（力扣64）

给一个网格，左上角走到右下角，路径和最小。

利用滚动数组优化空间：

``````c++
int minPathSum(vector<vector<int>>& grid) {
        if(grid.empty())return 0;
        int rows = grid.size(); int cols = grid[0].size(); 
        vector<vector<int> >dp(2, vector<int>(cols));
        int curr = 1; int prev = 0; int mmin;
        for(int i = 0;i < rows; i++){
            for(int j = 0; j < cols; j++){
                mmin = INT_MAX;
                if(i == 0 && j == 0){
                    dp[curr][j] = grid[i][j];
                    continue;
                }
                if(i > 0){
                    mmin = min(dp[prev][j], mmin);
                }
                if(j > 0){
                    mmin = min(mmin, dp[curr][j-1]);
                }
                dp[curr][j] = mmin + grid[i][j];
            }
            curr = 1 - curr;   prev = 1 - prev;
        }
	  return dp[1-curr][cols-1];
    }
``````

###### 3. bomb enemy ( lintcode 553)

**关键是分四个方向炸，用四次动态规化。当前情况在`if`中彻底完成，不要忘记`continue`**

------

##### 四、序列型动态规划

`dp[i]`对应`a[0]`到`a[i-1]`，所以开的数组一般为`size+1`，常常最后一步和前一步有关，常常按照最后一步的性质进行分类。组合数学中计数问题。

###### 1. paint house (lintcode 515) 

每个房子可以染成三种颜色，每个房子染每种颜色对应有成本，要求相邻两间房不能同色，求最低成本。

**染房子，必然会去染最后一个房子，最优染房策略中最后一个房子必然被染成某种颜色，但是我们不知道具体染成什么颜色，就此分类。同时染i个房子且第i-1个房子被染成红色的最小花费和染i-1个房子且第i-2个房子被染成绿色或者蓝色有关**

可以使用滚动数组优化

###### 2. paint house （lintcode 516）

paint house 1的一般化处理

* 求数组最小的两个一种做法：

  ``````c++
  void findtwomin(vector<int> &v, int &min, int &semin){
          int minv = INT_MAX, seminv=INT_MAX;
          int len = v.size();
          min = 0;semin = 0; //index
          for(int i = 0; i < len;i++){  // if len==1; comply 
              if(v[i] < minv){
                  seminv = minv;
                  semin = min;
                  minv = v[i];
                  min = i;
              }else if(v[i] < seminv){
                  seminv = v[i];
                  semin = i;
              }
          }
          
      }
  ``````

###### 3. house robber (lintcode 392 )

**结束，最后一间房要么被偷，要么不被偷**，递推公式类似斐波那契额形式， 空间可以优化。

###### 4. Russian Doll Envelopes （lintcode 602）

如何优化时间复杂度？

###### 5. best time to buy and sell stock 1(lintcode 149)

只允许买卖一次

**最后肯定是某一天卖出，枚举每一天， 维护一个当前最小值，得到当天卖出的最大利润**

###### 6. best time to buy and sell stock 2(lintcode 150)

可以买卖任意次数，但是手中最多只能有一张股票。

**把差价为正的累计起来。利用序列型动态规划。**

###### **7. best time to buy and sell stock 3(lintcode 151)**

最多交易两笔，购买股票之前必须卖掉手中已有的股票。

两次交易将问题划分为五个阶段：

<img src="./assets/2.png" style="zoom:60%;" />

递推公式如下：

<img src="./assets/3.png" style="zoom:60%;" />

注意初始化。

###### **8. best time to buy and sell stock 4(lintcode  393)**

上题的推广，进行k次买卖。



##### 五、划分型动态规划：

给定序列，要求划分为若干段。最后一步是划出一段，产生子问题。

###### 1. perfect squares （leetcode 279）

最少多少个平方数和为给定某数。

leetcode 通过，lintcode超时

###### 2. Palindrome Partitioning II(lintcode 108):

分割成回文字串最小次数。

如何控制时间复杂度，事先计算出每个字串是否为回文串记录下来

###### 3. copy books(lintcode 437)

给k个人，几本书，每个人超连续的书，抄每页花费一分钟，同时开始抄，问最少花费多少时间抄完。

* 构造递推公式思路：首先，定义$f$为最小花费时间。从数组最后某段划分给最后那个人，此时就产生子问题，因为需要知道前面一大段最小抄书时间，同时，前面一大段对应的人数也减1，人数不同对应的$f$也不同。所以变量有两个：人数$people$和书本数$book$。

  ​	同时，对于固定的人数和书本数，不同的划分，将带来不同时间花费，我们取这些花费最小的。

  ​	再有，对于固定的人数和书本数，固定的划分，前大段和后段花费时间的最大值将作为此时的花费时间。

  由上述思考，可以写出递推公式：

  ​	$f(people,book) = min [ max[f(people-1, j), T(j) ] ].$

  ​	其中，

  ​	$T(j) = \sum_{l=j}^{book-1}{pages(l)}, 0=<j<=book-1;$

  ​	$T(j)=0,j=book$

* 为了降低复杂度，$T(j)$可从后往前计算：

  ``````c++
  int sumtime = 0; //sumtime:后段花费时间和
  for(int kk = 1; kk < k+1; kk++){ // kk:人数
  // set leasttime[kk][i]
      for(int i = 0; i < len+1; i++){ // i:对于前i本书
          if(i == 0){
              leasttime[kk][i]=0;
              continue;
          }
          leasttime[kk][i] = INT_MAX;
          sumtime=0;
          for(int j = i; j >= 0;j--){  //使用j来划分
              if(j != i)   // 特殊情况，j == book, T(j)=0，划分0本给最后一人
                  sumtime += pages[j];
              leasttime[kk][i] = min(leasttime[kk][i],max(leasttime[kk-1][j], sumtime));
          }
  
      }
  }
  ``````

##### 六、博弈型动态规划：

###### 1. coins in a line(lintcode 394)

定义必胜态，面对i个硬币必胜，只要让对手面对i-1个硬币必败或者面对i-2个硬币必败。

##### 七、背包问题

###### 1. back pack(lintcode 92):

n个物品，背包承重为m。最多装多重?

* 递推思路：假设n个物品最多装w重。对于`A[n-1]`，不知道是否入包。

  * 假设入包，前n-1个物品能装w-`A[n-1]`
  * 假设不入包，则前n-1个物品能装w.

  * w是1到m的正整数，定义$f(i,m)=true$表示**前i个**物品**能装m个重量(不是最多能)**

###### 2. back pack 5（lintcode 563）

​	给出 n 个物品, 以及一个数组, `nums[i]` 代表第i个物品的大小, 保证大小均为正数, 正整数 `target` 表示背包的大小, 找到能填满背包的方案数。每一个物品只能使用一次。

和上题思路一致

空间可以优化至o(target):只用到了前一行

<img src="./assets/4.png" style="zoom:60%;" />

###### 3. Combination Sum (lintcode 564)  back pack 6

给出一个都是正整数的数组 `nums`，其中没有重复的数。从中找出所有的和为 `target` 的组合个数。

一个数可以在组合中出现多次，顺序不同视为不同的组合。

* 递推分析：**不能**定义**前**多少个物品这样的函数。显然，能拼出target的组合，最后一个物品要么是`nums[0]`,要么是`nums[1]`...`nums[N-1]`。$f(target)$表示能组合出target的方法数。

  $f(target) = \sum_{i=0}^{N-1}{f(target- nums[i])},i\in[0,N-1)$

  从而产生子问题。重新定义递推公式：

  $f(j) = \sum_{i=0}^{N-1}{f(j- nums[i])},i\in[0,N-1), j\in[0,target],j>=nums[i]$
  
  ​															

###### 4. Back Pack 2(lintcode 125)

​	有 `n` 个物品和一个大小为 `m` 的背包. 给定数组 `A` 表示每个物品的大小和数组 `V` 表示每个物品的价值.

问最多能装入背包的总价值是多大?每个物品只能取一次。

* 分析：假设我们有最优的结果，可以设为前n个物品凑出M重量的物品进入背包获得最大价值$MAXV(n,M)$.其中，$MAXV$要求量，M位于[0,m]。设为函数，令$f(n, w)$表示前n个物品凑出w重量入包，获得的价值，-1表示无法凑出。

  显然，$MAXV = max{f(n, m)}, m\in[0,m]$.

  考虑最有策略的**最后一步**，即**最后一个物品**是否入包，易得：

  $f(n,m) = max(f(n-1,m), f(n-1,m-A[n-1]) + v[n-1]),n\geq1,m\geq(A[n-1])$

  产生子问题，写出递推公式：

  $f(i,w) = max(f(i-1,w), f(i-1,w-A[i-1]) + v[i-1]),n\geq 1,m\geq(A[i-1])$

  $f(i,w)$表示前i个物品凑出w重量的最大价值，凑不出为-1.

  初始化后，从低向高计算，最后获得$MAXV$

* 空间可优化，和 back pack 5 一样的思路。



###### 5. Back Pack 3（未找到题目）

​	和背包2相似，只不过每个物品有无限个。

 * 分析：因为每个物品有无穷多个，不妨按照重量把所有的物品划分成等价类。分析最优策略，也就是未知数目的物品凑出了w重量入包，物品可以有重复，最大价值是$MAXV$。由于每类物品有无穷多个，最后一步无法从最后一个物品是否进包入手。但是物品的类别是有限的，物品有n类。于是最优策略可以描述为：**前n类物品**凑出了w重量入包，获得最大价值$f(n,w), w\in[0,m]$。考虑最后一类入包的物品个数，设为k(k>=0)，有：

   $f(n, w) = max(f(n-1, w - k*A[n-1]) + k*V[n-1]), k\geq0$

   显然产生了子问题，种类数减少了。写出递推公式如下：

   $f(i, w) = max(f(i-1, w - k*A[i-1]) + k*V[i-1]), k\geq0,w - k*A[i-1]\geq0,i\in[0,n],w\in[0,m]$

   $f(i,w)$：**前i类**物品凑成w重量的最大价值，定义-1表示不能凑出重量来。

   初始化后，从$f(0,w)$计算到$f(n,w)$，最后$MAXV = max(f(n,w)),w\in[0,m]$。

   **时间复杂度优化：**因为要枚举i、w、k。有上述递推公式易得：
   $$
   \begin{split}
   f(i, w+A[i-1]) &= max(f(i-1, w - (k-1)*A[i-1]) + k*V[i-1])\\
   &=max[f(i-1, w + A[i-1]) ,max(f(i-1,w-k*A[i-1])+(k+1)*V[i-1])]\\
   &=max[f(i-1, w + A[i-1]) ,max( f(i-1,w-k*A[i-1])+k*v[i-1] )+V[i-1]] \\
   &=max[f(i-1, w+A[i-1]), f(i,w)+V[i-1]]
   \end{split}
   $$
   即得$f(i,w) = max[f(i-1,w), f(i,w-A[i-1])+V[i-1]]$

* 空间可以优化，但是计算顺序要从左向右。

​														**背包问题总结**：



<img src="./assets/5.png" style="zoom:100%;" />

##### 八、区间型动态规划

* **f[i,j]表示某个区间的最有性质**
* **以长度作为计算顺序的 衡量标准**

###### 1. Longest Palindromic Subsequence(lintcode 667)

给一字符串 s, 找出在 s 中的最长回文子序列的长度. 

* 分析：不妨设最优解为$f$,此时有三种情况：

  * 首尾字符相等，记去掉首尾后的字符串最优解为$f1$;
  * 首尾字符不等，记去掉首字符后的字符串最优解为$f2$;
  * 记去掉尾字符后的字符串的最优解为$f3$.

  易知，$f = max(f1+2,f2,f3)$。

  产生子问题，不妨定义$f(i,j)$表示[i,j]区间内的最优解，递推公式如下：

  $f(i,j) = max(f(i+1,j), f(i, j-1), f(i+1,j-1)+2)$


###### 2. coins in a line(lintcode 395)

未找到原题

###### 3. scramble string(lint code 430)

给定两个相同长度的字符串 `s1` 和 `s2`，判断 `s2` 是否为 `s1` 的攀爬字符串.

令$f(s1,s2)$表示s1和s2是否能够相互变换,$left1$表示$s1$左边部分，对于$s2$同理。

$f(s1,s2) = [f(left1, left2) \bigwedge f(right1,right2)]\bigvee[f(left1,right2)\bigwedge f(right2,left2)]$

从而产生子问题，因为字符串长度变小。

重新定义:

$f(i,j,l)$表示字符串$s1[i]...s1[i+l-1]$和字符串$s2[j]...s2[j+l-1]$是否可以互变

可以写出以下递推公式：

$f(i,j,l)=[f(i,j,ll)\bigwedge f(i+ll,j+ll,l-ll)] \bigvee[f(i,j+l-ll,l-ll)\bigwedge f(i+ll, j, l-ll)],ll\in[1,l]$

###### 4.	Burst Balloons(lint code 168)

​		有n个气球，编号为`0`到`n-1`，每个气球都有一个分数，存在`nums`数组中。每次吹气球i可以得到的分数为 `nums[left] * nums[i] * nums[right]`，left和right分别表示`i`气球相邻的两个气球。当i气球被吹爆后，其左右两气球即为相邻。要求吹爆所有气球，得到最多的分数。可以假设`nums[-1] = nums[n] = 1`。-1和n位置上的气球不真实存在，因此不能吹爆它们。

* 分析：不妨在数组左右两边添加1，记新数组为v方便计算，`v[0] = v.back()=1`。显然，**最优策略最后一步必然是最后吹破某个气球**。设最优策略最后分数为$f$,最后一个吹的气球为k ，记对于k的左边气球的最优策略为$f(left)$, 右边同理记为$f(right)$ 

  于是有$f = max(f(left) + f(right) + v[0]*v[k]*v.back()),k\in[1, len-2]$

  从而产生子问题，需要求左边和右边的最优策略。

  进行正式定义，$f(i,j)$表示$[i+1,j-1]$的最优策略（就是此区间的最多得分），递推公式如下：

  $f(i,j) = max(f(i,k)+f(k,j) + A[i]*A[k]*A[j],k\in[i+1,j-1]$

  **以长度递增顺序进行计算，保证区间合法性**，先初始化长度为2的区间。

##### 九、双序列型动态规划

**两个字符串，考虑最后一个字符确定最后一步，分类讨论，写出递推公式**。

###### 1.最长公共子序列（lintcode 77）：

给出两个字符串，找到最长公共子序列(LCS)，返回LCS的长度。子序列不一定在序列中连续。

* 分析：设A、B的长度分别为n、m，LCS的长度记为$f(n,m)$。

  考虑**最后一个字符**，如果`A[n-1] = B[m-1]`,显然$f(n,m)=f(n-1,m-1)+1$

  否则，我们不知道`A[n-1]`和`B[m-1]`是否属于LCS。此时，$f(n,m)=max(f(n-1,m),f(n,m-1))$

  以上产生子问题，递推顺利写出：

  $f(i,j)=max(f(i-1,j),f(i, j-1),f(i-1,j-1)+1|A[i-1]==B[j-1])$

  $f(i,j)$表示A的**前**i个字符和B的**前**j个字符的LCS的长度。

  从底向高递推计算，返回$f(n,m)$即可。

###### 2.交叉字符串

给出三个字符串:*s1*、*s2*、*s3*，判断*s3*是否由*s1*和*s2*交叉构成。

* 分析：首先，满足交叉构成，s1长度与s2长度之和应该等于s3长度。记三个字符串长度分别为len1,len2,len3,并且满足和的关系，$f(len1,len2)$表示是否交叉构成，具体来说整个s1和整个s2是否和整个s3交叉构成。考虑最后一步，s3的**最后一个字符**s3[len3-1]，该字符来自s1或者s2，显然:

  如果`s3[len1+len2-1] == s1[len1-1]`,有$f(len1，len2) = f(len1-1,len2)$

  同理`s3[len1+len2-1]==s2[len2-1]`，有$f(len1,len2) = f(len1,len2-1)$

  显然产生子问题，定义$f(i,j)$表示s1的前i个字符和s2的前j个字符是否构成s3的前i+j的字符，可写出递推公式：

  $f(i,j) = (f(i-1,j)|s3[i+j-1])==s1[i-1]) \bigvee (f(i,j-1)|s3[i+j-1]==s2[j-1])$

  初始化，注意边界条件，循环递推计算出$f(len1,len2)$即可。

###### 3.编辑距离

一个字符串变化为另一个字符串最小操作数目，仅限于增删该。

* 分析：s1变为s2，长度分别为n、m，记$f(n,m)$代表问题的最优策略。

  考虑最后一步，必然是s2最后一个字符被实现，分类讨论：

  - 如果是在s1的末尾添加一个`s2[m-1]`，我们只需要关注s1的前n个字符和s2的前m-1个字符的最优策略，即$f(n,m)=f(n,m-1)+1$
  - 同理，如果修改`s1[n-1]`为`s2[m-1]`,有$f(n,m) = f(n-1,m-1)+1$.
  - 再有，简单的删除`s[n-1]`,认为`s2[m-1]`从s1的前n-1个字符产生，有$f(n,m)=f(n-1,m)+1$
  - 还有，如果幸运的是`s1[n-1]==s2[m-1]`，那么$f(n,m) = f(n-1,m-1)$。

  显然产生子问题,重新定义$f(i,j)$代表s1的前i个字符和s2的前j个字符的最小编辑距离，初始化，从底向上递推计算，求出$f(n,m)$即可。

###### 4.不同的子序列

​	给定字符串 `S` 和 `T`, 计算 `S` 的所有子序列中有多少个 `T`.

​	子序列字符串是原始字符串删除一些(或零个)字符之后得到的字符串, 并且要求剩下的字符的相对位置不能改变. (比如 `"ACE"` 是 `ABCDE` 的一个子序列, 而 `"AEC"` 不是)

* 分析：记S的长度为n,T的长度为m，$f$代表问题的解。当T作为S的某个子序列时，T的**最后一个元素**必然和S的某个元素成对，如果`T[m-1]==S[n-1]`，则`T[m-1]`**可以**和`S[n-1]`成对，无论`T[m-1]`和`S[n-1]`是否相等，`T[m-1]`都可以和S的前n-1个字符中某个字符来成对。于是,考虑字符长度，记$f(n,m)$为问题的解，有：

  $f(n,m) = f(n-1,m)+[f(n-1,m-1)|S[n-1]==T[m-1]]$

  显然产生子问题，重新定义即可得到递推公式：$f(i,j)$代表S的前i个字符的子序列中有T的前j个字符的数目。

  $f(i,j) = f(i-1,j)+[f(i-1,j-1)|S[i-1]==T[j-1]]$

  **初始化需要注意**，容易得出$f(0,j)=0,j!=0$.考虑S={”a"},T={"a"},$f(1,1)=f(0,0)+f(0,1)=f(0,0)$,因此需要强制定义$f(0,0)=1$。因此$f(0,0)=f(1,0)=f(2,0)=...f(n,0)=1$.

###### 5.正则表达式匹配

输入s,p(带 '.' 和'*')，点认为是癞子，可以为任意字符，星前的元素个为自然数个。问是否能匹配。

* 分析：**主要分类讨论清楚，代码注意初始化和边界**。记s和p的长度分别为n和m，分析p的最后一个字符：
  * 如果，`p[m-1]==s[n-1]`或者p[m-1]=='.'  则s的最后一个字符成功匹配，整个是否匹配取决于前n-1和前m-1。
  * 如果，p[m-1]=='*' ：
    * 若p[m-2] == s[n-1] 或者p[m-2] == '.' 则s的最后一个字符成功匹配，整个匹配取决于n-1和**m**
    * 另外，则说明p的后两个字符无法匹配s的最后一个字符，整个匹配取决于n和**m-2**

###### 6.通配符匹配

判断两个可能包含通配符“？”和“*”的字符串是否匹配。匹配规则如下：

1. '?' 可以匹配任何单个字符。

2. '*' 可以匹配任意字符串（包括空字符串）。

两个串完全匹配才算匹配成功。

* 分析：难处理的是*可以匹配任意字符。

  和上题同样，如果p[m-1]==s[m-1]或者p[m-1]=="?",显然整个匹配取决于n-1和m-1。

  如果p[m-1]=='*'，可以匹配多个串，**我不知道你要不要匹配，也不知道你要匹配几个字符**，但是如果你不想匹配，则整个是否匹配取决于n,m-1，如果你想匹配，那就先匹配一个吧，则整个是否匹配取决于n-1,**m**。

###### 7. 零和一

在计算机世界中, 由于资源限制, 我们一直想要追求的是产生最大的利益.
现在，假设你分别是 m个 `0s` 和 n个 `1s` 的统治者. 另一方面, 有一个只包含 `0s` 和 `1s` 的字符串构成的数组.
现在你的任务是找到可以由 m个 `0s` 和 n个 `1s` 构成的字符串的最大个数. 每一个 `0` 和 `1` 均只能使用一次。

* 分析：注意理解题意，每个字符串只能用一次，就是背包问题。我不知道最后一个字符串是否使用，根据最后一个字符串是否使用分类讨论，产生子问题，引起资源个数的变化，故$f(i,j,k)$表示前i个字符串在jk个资源下的最优值。容易写出递推公式：

  $f(i,j,k) = max(f(i-1,j,k), f(i-1,i-num0,j-num1)),i>num0-1,j>num1-1$,其中`num0`和`num1`分别表示第i-1个字符串中0和1的个数。

  边界条件容易制造，从底向上计算出$f(numstrs,m,n)$即可。

##### 八、综合

###### 1. 最小调整代价

给一个整数数组，调整每个数的大小，使得相邻的两个数的差不大于一个给定的整数target，调整每个数的代价为调整前后的差的绝对值，求调整代价之和最小是多少。整数都是**正整数**，且小于等于**100**

* 分析：数组A长为n,设最后一个整数修改为x,记$f(n)$代表前n个整数的最优值，显然$f(n)=f(n-1)+abs(A[n-1]-x)$

  虽然产生子问题，但是我们不知道x是多少，那就记下来，x范围是[1,100].

  重新定义$f(n,x)$表示A[n-1]修改为x的最优值，那么结果是$min(f(n,x),x\in[1,100]$

  有：$f(n,x) = f(n-1,y)+abs(A[n-1]-x),x\in[1,100],y\in[x-target,x+target]$

  因为有牵连关系，A[n-1]修改为x,会限制A[n-2]的修改范围。

  显然产生子问题，定义$f(i,j)$表示前i个整数且A[i-1]修改为j的情况下的最优值。

  **序列加状态**

###### 2. K数之和

给定 *n* 个不同的正整数，整数 *k*（*k* <= *n*）以及一个目标数字 *target*。　
在这 *n* 个数里面找出 *k* 个数，使得这 *k* 个数的和等于目标数字，求问有多少种方案？

* 分析：**背包问题**，恰好装满背包。分类的标准是**最后一个整数是否进入背包**。

  如果进入背包，则问题变为在前n-1个整数中找到k个数和为target的方案数。

  如果不进背包，则问题变为在前n-1个整数中找到k-1个数和为target-A[n-1]的方案数。

  产生子问题，变化的量都设为方案数的变量，记$f(i,k,s)$表示前i个整数中找出k个数和为s的方案数，显然递推公式为：

  $f(i,k,s)=f(i-1,k,s)+f(i-1,k-1,s-A[i-1])$

  初始化，注意边界条件。

###### 3. 青蛙跳

​	一只青蛙正要过河，这条河分成了 x 个单位，每个单位可能存在石头，青蛙可以跳到石头上，但它不能跳进水里。
​	按照顺序给出石头所在的位置，判断青蛙能否到达最后一块石头所在的位置。刚开始时青蛙在第一块石头上，假设青蛙第一次跳只能跳一个单位的长度。
​	如果青蛙最后一个跳 k 个单位，那么它下一次只能跳 `k - 1` ，`k` 或者 `k + 1` 个单位。注意青蛙只能向前跳。

* 分析：假设最后一步往最后一个石头跳了j步，那么上一个石头的位置为a[n-1]-j,那么最终能否跳到最后一个石头取决于a[n-1]-j位置是否有石头且是否能跳到这个石头。产生子问题，因为把石头的位置放在了数组中，石头位置和数组下标一一对应，不妨用map把石头位置和数组下标存起来方便查找，**设$f(i,j)$表示是否能以最后j步跳到a[i]**，记石头位置到下标索引的函数为g.

  则$f(i,j) = f(g(a[i]-j),j-1)||f(g(a[i]-j),j)||f(g(a[i]-j),j+1)$

  初始化，注意第一步只能跳一步。j的取值范围为[0,n-1].

* 进阶：可以使用`hash_map<int ,hash_set<int> >`来保存某个石头，以及可以跳到此石头的最后一步的步数（集合保存）。减少内存。只需要遍历当前石头的集合，然后试图以合法的步数往下一个石头跳，下一个石头有的话，把此步数加到下一个石头的集合，最后只需要看最后一个石头的集合是否空即可。第一个石头，认为最后以0步跳到此石头

  <img src="./assets/6.png" style="zoom:100%;" />

###### 4. 解码方式2（lin't'co'de 676）

使用以下映射方式将 A-Z 的消息编码为数字:

```
'A' -> 1
'B' -> 2
...
'Z' -> 26
```

除此之外, 编码的字符串也可以包含字符 `*`, 它代表了 1 到 9 的数字中的其中一个.给出包含数字和字符 `*` 的编码消息, 返回所有解码方式的数量. 因为结果可能很大, 所以结果需要对 10^9 + 7 取模

* 分析：两位数可以有两种解码方式。整个字符串根据最后一个字符和最后两个字符分类讨论：

  $f(i) = f(i-1)*w1+ f(i-2)*w2$,其中$w1$是最后一个字符的解码方式数，$w2$是后两个字符的解码方式数，$f(i)$表示前i个字符的解码方式数。

  递推计算即可。

###### 5.最大正方形（lintcode436）

在一个二维01矩阵中找到全为1的最大正方形, 返回它的面积.

* 分析：最大正方形必然以某个坐标为右下角，考虑最大正方形的边长，假设最优解情况下正方形右下角坐标为(i,j),最优解是边长为$f(i,j)$,分析可以知道$f(i,j)$受限与$f(i,j-1),f(i-1,j),f(i-1,j-1)$中的最小值，递推公式为:

  $f[i][j] = min(min(f[i-1][j], f[i][j-1]), f[i-1][j-1]) + 1$

  递推计算即可.

###### 6.扔鸡蛋（leetcode 887）

​	题目：给定k个鸡蛋，1-N总共N层楼。存在一个临界楼层F(0<=F<=N)使得在[1,F]扔鸡蛋不碎，而在[F+1,N]扔鸡蛋会碎。利用这K个鸡蛋，求在最小的试验次数内就能找到这个F楼层，包括在最坏的F情况下。

* 分析：只有一个鸡蛋时，只能亦步亦趋的逐层楼试验。当有多个鸡蛋时，无法知道第一个鸡蛋应该从哪个楼层扔，不妨假设在第m层（1<=m<=N）扔，扔结束，进行分类讨论，如果碎，则考察楼层为[1,m-1]这m-1层楼，否则考察楼层为[m,N]这N-m层楼，出现自问题，原问题规模变小。定义$f(N,K)$为问题的解，由上述假设，当第一次在第m层扔时，$f(N,k)|m = 1+max(f(m-1,k-1), f(N - m,k))$，为什么要求最大值呢？因为我们要在最坏情况下也能排查出这个临界楼层，所以这里必须要取最坏情况。不妨记上述式子为$f(N,k)|m = g(m)$，现在让m动起来，则$f(N,k)|m = min\{g(1),g(2),...,g(i),...,g(N)\}$。在仔细分析一下$g(m)$，记$g(m) = max(h(m), t(m))$，$h(m)$递增，$t(m)$递减，$g(m)$是下凸的，我们的目标就是找到$g(m)$的最小值点，可以使用二分查找，假设二分中点为mid，如果$g(mid)= h(mid)$，目标在mid左边，否则右边，同时应该注意到到函数是离散型的，目标是位于[i,i+1]这样的区间内的（i合法），最终$f(N,k) = min(g(i), g(i+1))$。分析过程在改为一般形式的递推式，从底向上计算即可。

  ``````c++
  class Solution {
  public:
      int binSearch(vector<vector<int>> &v, int lo, int hi, int i,int j){
          int mid;
          while(lo < hi){ mid = (lo + hi) >> 1;
              (v[i - mid][j] < v[mid - 1][j-1]) ? hi = mid : lo = mid + 1; } 
          return --lo;
      }
      int superEggDrop(int K, int N) {
          vector<vector<int>>f(N+1, vector<int>(K+1));
          for(int i = 0;i <= K;i++){//f[0][.]  f[.][0] 非法
              f[0][i] = 0;
              if(i > 0)
                  f[1][i] = 1;
          }
          for(int i = 0; i <= N;i++){
              f[i][0] = INT_MAX;
              if(i > 0)
                  f[i][1] = i;
          }
          // f[i][j] = min{1 + max(f[k -1][j-1], f[i-k][j])}  k:[1,2,3 ... k,...i]
          for(int i = 2;i <= N;i++){
              for(int j = 2;j <= K;j++){
                  f[i][j] = INT_MAX;
        /* 找到 m ,使得 g(m) = max(f[m-1][j-1], f[i-m][j]) 最小. f[x][y]关于x单调增
        记f[m-1][j-1]为h(m)， 记f[i - m][j]为t(m). h(m)递增，t(m)递减. 
        找到target,使得h(target) == t(target), 但离散函数实际应该找到一个i, i<= target <= i+1
                  for(int m = 1; m < i;m++){ //蛮力遍历所有m           
                      f[i][j] = min(f[i][j], 1+max(f[m-1][j-1], f[i-m][j]));
                  }
                  */
                  int floor = binSearch(f,1,i+1,i,j); // 二分找m
                  f[i][j] = min(f[i][j], 1+max(f[floor-1][j-1], f[i-floor][j]));
              }
          }
          return f[N][K];
      }
  };
  ``````

  

##### 背包九讲

###### 一、01背包问题

**问题描述：**有一个背包，容量有限，有一堆物品，每个物品体积和价值已知。最多能装多少价值的东西。

输入：第一行 N， V 空格隔开，表示物品的数量和背包容量

​			接下来N行，第i行表示第i个物品的体积和价值，空格隔开

**分析：**最后一步就是最后一个物品是否入包，从而产生子问题。状态的语义有两种。

* `dp[i][j]`表示：**前i个**物品**恰**能凑齐j体积时的最大价值，显然j在[0,V]内取。这样，**最终的结果是**$max({dp[N][x],x\in[0,V]})$。根据语义来初始化，`dp[0][1]...dp[0][V]`置为-1表示无法使用0个物品来凑大于0的价值, `dp[0][0]`初始化为0。
* `dp[i][j]`表示：**前i个**物品**不超过**j体积限制下能凑出的最大值。这样，**最终的结果是**`dp[N][V]`。根据语义来初始化，`dp[0][0]...dp[0][V]`为0。
* 递推方程：**`dp[i][j] = max(dp[i-1][j], dp[i-1][j - arrVol[i-1]]+arrVal[i-1])`**

状态转移方程根据最后一步定义。分析转移方程，空间可以优化到一维。**`dp[i][j]`和`dp[i-1][j]`、`dp[i-1][j-vol[i-1]]`有关**

``````c++
#include <iostream>
using namespace std;
#define N 1010
int num, capacity;
int arrVol[N], arrVal[N];
int dp[N][N]; // dp[i][j]:前i个物品 ，恰好装j的体积时最大的价值,如果装不了置为-1
int dp2[N];
int main(){
    cin>>num>>capacity;
    for(int i = 0; i < num; ++i){
        cin>>arrVol[i]>>arrVal[i];
    }
  
    for(int i = 1;i <= num;++i){
        // for(int j = 0; j <= capacity;++j){
        //     dp[i][j] = dp[i-1][j];
        //     if(j >= arrVol[i-1])
        //         dp[i][j] = max(dp[i][j], dp[i-1][j-arrVol[i-1]] + arrVal[i-1]);
        // }
        for(int j = capacity;j >= arrVol[i-1];j--)
            dp2[j] = max(dp2[j], dp2[j - arrVol[i-1]] + arrVal[i-1]);
    }
    //cout<<dp[num][capacity]<<endl;
    cout<<dp2[capacity]<<endl;//不必循环比较dp[num][0...capacity]
    return 0;
}
``````

###### 二、完全背包问题

**问题描述：**有一个背包，容量有限，有一堆物品，每个物品体积和价值已知。最多能装多少价值的东西。每个物体可以被装**无限次**。

输入：第一行 N， V 空格隔开，表示物品的数量和背包容量

​			接下来N行，第i行表示第i个物品的体积和价值，空格隔开

**分析**：最后一步就是最后一个物品**类**是否进入背包。

* `dp[i][j]`表示前i个物品在恰好j体积能够装的最大值。初始化根据语义初始，最终结果是`dp[N][V]`。

  经过转化，递归方程（等价变化之后）：**`dp[i][j] = max(dp[i-1][j], dp[i][j-vol[i-1] + val[i-1])`**，可以压缩到一维，计算顺序和01背包不同，是顺序计算。**`dp[i][j]`和`dp[i-1][j]`、`dp[i][j-vol[i-1]]`有关**

``````c++
#include <iostream>
using namespace std;
#define N 10010
int num, capacity;
int vol[N], val[N];
int dp[N][N]; 
int dp2[N];
#define METHOD1
// #define OPTIMIZATION
int main(){
    cin>>num>>capacity;
    for(int i = 0; i < num;i++)cin>>vol[i]>>val[i];
#ifndef METHOD1
    for(int i = 1;i <= num;i++){
        for(int j = 0;j <= capacity;j++){
            dp[i][j] = dp[i-1][j];
            if(j>=vol[i-1])
                dp[i][j] = max(dp[i][j], dp[i][j-vol[i-1]] + val[i-1]);
        }
    }
    cout<<dp[num][capacity];
#endif
//------------------------空间优化----------------
#ifndef OPTIMIZATION
    for(int i = 1;i <= num;i++){
        for(int j = vol[i-1];j <= capacity;j++){
            dp2[j] = max(dp2[j], dp2[j-vol[i-1]] + val[i-1]);
        }
    }
    cout<<dp2[capacity]<<endl;   
#endif
    return 0;
}
``````

###### 三、多重背包问题

**问题描述**：n个物品，一个容量v的背包。每个物品有体积、价值、数量。问可装的最大价值。

最优解的结构：最后一个物品装了K个，用$f(i,j)$表示容量限制为j下，用前i种物品类可以装的最大价值。

递归的定义最优解的值：

​			$$f(i,j) = \begin{cases}   0 & j = 0或i=0  \\ \max\{ f(i, j-k*vol[i-1])+k*val[i-1] \} & 0 \leq k \leq s[i-1]\&\&k*vol[i-1]\leq j \end{cases}$$

``````c++
#include<iostream>
#include <limits.h>
using namespace std;
const int NN = 110;  int N, V; int vol[NN], val[NN], s[NN];  int dp[NN][NN]; int dp2[NN];
//#define NOOPTIMIZATION
#define OPTIMIZATION
int main(){
    cin>>N>>V;
    for(int i = 0; i < N; i++ )cin>>vol[i]>>val[i]>>s[i];
#ifndef NOOPTIMIZATION
    for(int i = 1; i <= N; i++){
        for(int j = 1;j <= V; j++){
            //dp[i][j] = dp[i-1][j];
            dp[i][j] = INT_MIN;
            for(int k = 0; k <= s[i-1] && k*vol[i-1]<=j; k++){
                dp[i][j] = max(dp[i][j], dp[i-1][j - k*vol[i-1]] + k*val[i-1]);
            }
        }
    }
    cout<<dp[N][V]<<endl;
#endif
#ifndef OPTIMIZATION
    for(int i = 1; i <= N; i++){
       for(int j = V;j >= 1;j--){
           for(int k = 0; k * vol[i-1] <= j && k <= s[i-1]; k++){
               dp2[j] = max(dp2[j], dp2[j - k * vol[i-1]] + k*val[i-1]);
           }
       }
    }
    cout<<dp2[V]<<endl;
#endif
    return 0;
}
``````

**再优化**：对每种物品进行重新组合，组合方式：分别1，2，4，8...个物品视为一个大物体，利用二进制思想，例如某个物品个数是n个，二进制拆分能表示出1-n所有的组合。

``````c++
#include <iostream>    #include <utility>   #include <vector>
using namespace std;   const int N = 2010;  int f[N]; int n, m;
int main(){
    cin>>n>>m;    vector<pair<int , int > >goods;
    for(int i = 0; i < n; i++){  
        int v, w, s; cin>>v>>w>>s;
        /*二进制重组每种物品，构造01背包问题*/
        for(int j = 1; j <= s; j*=2){
            s = s-j;
            goods.push_back(make_pair(j * v, j * w));
        }
        if(s>0)goods.push_back(make_pair(s * v, s * w));
    }
    for(auto e:goods){
        for(int k = m;k >= e.first;k--)
            f[k] = max(f[k], f[k - e.first] + e.second);
    }
    cout<<f[m]<<endl;
    return 0;
}
``````

**单调队列优化**：

###### 四、混合背包问题

**问题描述**：n、v表示物品个数和背包容量

​					n行，每行v、w、s表示容量、价值、类型，s等于-1表示01背包，s等于0表示完全背包，s大于0表示多重背包。

**分析**：多重背包按照二进制重组物品，重构所有物品，分为01背包和完全背包两类。

`````c++
#include <iostream>		#include <limits.h>		#include <vector>	#include <string.h>
using namespace std;	int n,v;
/*空间优化*/
int dp2[N];
struct e{
    int kind; int vol; int val;
};
#define METHOD1
//#define METHOD2
int main(){
    cin>>n>>v;
    vector<e>all;
    for(int i = 0; i < n;i++){ //重构为01和完全背包
        int v,w,s;
        cin>>v>>w>>s;
        if(s == -1){ // 01背包
            all.push_back({-1,v,w});
        }else if(s == 0){//完全背包
            all.push_back({0,v,w});
        }else{  // 多重背包
            for(int j = 1;j <= s;j *= 2){
                s -= j;
                all.push_back({-1,j * v, j * w});
            }
            if(s>0)all.push_back({-1,s * v, s * w});
        }
    }
#ifndef METHOD1
    int dp[all.size()+1][v+1];
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= all.size();i++){
        for(int j = 1; j <= v;j++){
            if(all[i-1].kind == -1){ // 01背包
                dp[i][j] = dp[i-1][j];
                if(all[i-1].vol <= j)
                    dp[i][j] = max(dp[i][j], dp[i-1][j - all[i-1].vol] + all[i-1].val);
            }else{  // 完全背包
                dp[i][j] = dp[i-1][j];
                if(all[i-1].val <= j)
                    dp[i][j] = max(dp[i][j], dp[i][j - all[i-1].vol] + all[i-1].val);
            }
        }
    }
    cout<<dp[all.size()][v]<<endl;
#endif
#ifndef METHOD2
    for(auto ee:all){
        if(ee.kind == -1){
            for(int i = v;i >= ee.vol;i--) dp2[i] = max(dp2[i], dp2[i-ee.vol] + ee.val);
        }else{
            for(int i = ee.vol;i <= v;i++) dp2[i] = max(dp2[i], dp2[i-ee.vol] + ee.val);
        }
    }
    cout<<dp2[v]<<endl;
#endif

    return 0;
}
`````

###### 总结

* 二维数组表示状态时，容量从1计算到v
  * 01背包：` dp[i][j] = max(dp[i-1][j], dp[i-1][j - Vol[i-1]]+Val[i-1]);`
  * 完全背包：` dp[i][j] = max(dp[i-1][j], dp[i][j - Vol[i-1]]+Val[i-1]);`

* 一维数组表示状态时，注意容量计算顺序

  * 01背包：降序

  ``````c++
  for(int i = v;i >= ee.vol;i--) dp2[i] = max(dp2[i], dp2[i-ee.vol] + ee.val);
  ``````

  * 完全背包：升序

  ``````c++
  for(int i = ee.vol;i <= v;i++) dp2[i] = max(dp2[i], dp2[i-ee.vol] + ee.val);
  ``````

* 混合背包转化为01和完全背包问题

###### 五、二维费用背包问题

###### 六、分组背包问题

###### 七、背包问题求方案数

###### 八、求背包问题的方案

###### 九、有依赖的背包问题

