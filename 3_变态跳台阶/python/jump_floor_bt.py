# -*- coding:utf-8 -*-
class Solution:
    def jumpFloorII(self, number):
        s_n = 0
        f_n = 0
        for _ in range(number):
            f_n = s_n + 1
            s_n = s_n + f_n
        return f_n
            
            
            
        # write code here