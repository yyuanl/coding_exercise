链表反转，两个结点见的指向反转。

思路：定义三个指针left,mid,right，将mid结点指向left结点，**right在反转前应记录mid的下一个结点**，以便继续向后滑动。应将left和right初始化为NULL。