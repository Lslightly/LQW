def createCounter():
    def g():
        n = 1
        while True:
            yield n
            n += 1
        return None

    ge = g()

    def counter():
        return next(ge)

    return counter


counterA = createCounter()
print(counterA(), counterA(), counterA(), counterA(), counterA())  # 1 2 3 4 5
counterB = createCounter()
if [counterB(), counterB(), counterB(), counterB()] == [1, 2, 3, 4]:
    print('测试通过!')
else:
    print('测试失败!')
