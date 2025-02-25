# https://www.liaoxuefeng.com/wiki/1016959663602400/1017404530360000
def is_palindrome(n):
    L1 = []
    while n != 0:
        L1.append(n % 10)
        n //= 10
    L2 = L1[:]
    L2.reverse()
    return L1 == L2


output = filter(is_palindrome, range(1, 1000))
print('1~1000:', list(output))
if list(filter(is_palindrome, range(1, 200))) == [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99,
                                                  101, 111, 121, 131, 141, 151, 161, 171, 181, 191]:
    print('测试成功!')
else:
    print('测试失败!')
