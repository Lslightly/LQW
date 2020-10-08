#### 2进制补码

* 2's complement intergers
  * 正数补码与负数补码相加刚好为0，负数补码就是这么选择的。
    * 00101+11011 -> 00000
* 正数的二进制码前面的0可以随意添加，负数的二进制码前面的1可以随意添加，不改变值，在做两个不同二进制位的数的加法与减法的时候可以根据正数还是负数相应添加0位与1位。

> this operation is called Sign-Extension(SEXT), operating on bit patterns of different lengths, while not affecting the values of the numbers being represented.

#### AND, OR, NOT

* using a bit mask to isolate bits with particular significance from original pattern.
  * isolate the rightmost two bits from a eight-bit pattern:  using 00000011, result: 000000xy.

* bit-wise AND: apply AND operation individually to each pair of bits in the two source operands.

* inclusive-OR <=> bitwise OR.

#### Exclusive-OR

* abbr: XOR
* two patterns are identical if the output of XOR is all zeros.

#### the Bit Vector

* n-bit pattern to keep track of n units' status:
  * 1 <=> free
  * 0 <=> busy
  * clear the leftmost 1 bit, others keep: using 01111111, AND, result: 0???????.
  * let the leftmost 1 bit free: using 10000000, OR, result: 1???????.

#### Float Pointing Data Type

* float:
  * 32 bits
    * 1 for sign(positive or negative)
    * 8 for range(exponent field)
    * 23 for precision(fraction field)