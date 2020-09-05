def createCounter():
    s = 0

    def counter():
        nonlocal s  # 声明外层局部变量
        s += 1
        return s

    return counter


counterA = createCounter()
print(counterA(), counterA(), counterA(), counterA(), counterA())  # 1 2 3 4 5
counterB = createCounter()
if [counterB(), counterB(), counterB(), counterB()] == [1, 2, 3, 4]:
    print('测试通过!')
else:
    print('测试失败!')
