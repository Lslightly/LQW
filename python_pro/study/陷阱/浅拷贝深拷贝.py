# https://blog.csdn.net/sctec/article/details/84976288

# 切片为浅拷贝
a = [1, 2, [3, 4]]
b = a[:]
print(a is b)
a[2][0] = 'hey'
print(a)
print(b)

# a和b地址不同
# 结果
# False
# [1, 2, ['hey', 4]]
# [1, 2, ['hey', 4]]
