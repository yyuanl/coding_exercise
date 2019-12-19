# -*- coding:utf-8 -*-
class Solution:
    def jumpFloor(self, number):
        a0 = 1
        a1 = 2
        if number < 1:
            return 0
        if number == 1:
            return a0
        for _ in range(number - 2):
            a1 = a0 + a1
            a0 = a1 - a0
        return a1
        # write code here