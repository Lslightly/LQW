# next()函数获取下一个返回值


# Fibonacci数列生成器定义
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b     # 对应赋值
        n = n + 1
    return 'done'


# 0~9平方数生成器
g = (x * x for x in range(10))
print(g)
for i in g:
    print(i)
for n in fib(6):
    print(n)
