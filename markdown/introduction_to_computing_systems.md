#### 2进制补码

* 2's complement intergers
  * 正数补码与负数补码相加刚好为0，负数补码就是这么选择的
    * 00101+11011 -> 00000
* 正数的二进制码前面的0可以随意添加，负数的二进制码前面的1可以随意添加，不改变值，在做两个不同二进制位的数的加法与减法的时候可以根据正数还是负数相应添加0位与1位

> this operation is called Sign-Extension(SEXT), operating on bit patterns of different lengths, while not affecting the values of the numbers being represented

* 