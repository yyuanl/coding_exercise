# 第0项是0，从0开始，输入n

class Solution:
    def Fibonacci(self, n):
    # 递归实现
        # if n == 0:
            # num = 0
        # if n == 1:
            # num = 1
        # if n > 1:
            # num = self.Fibonacci(n - 1) + self.Fibonacci(n - 2)        
        # if n < 0:
            # num = None
        # return num
     # 从头计算，永远都是 c = a + b， 一个大数加上一个小数,大数来自加过和，小数来自上次加和的大数。避免重复计算。
     # 记忆：b,a,c 从头往后滑动
        if n == 0:
            return 0
        if n == 1:
            return 1
        a = 1
        b = 0
        ret = 0
        for i in range(n - 1):
            print('{}th loop'.format(i + 1))
            ret = a + b
            b = a
            a = ret
        return ret
    
if __name__ == '__main__':
    s = Solution()
    print(s.Fibonacci(4))