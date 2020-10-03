def calc(*number):
    sum = 0
    for i in number:
        sum += i * i
    return sum


print("print(calc(3, 4)):", calc(3, 4))
print("print(calc(*[3, 4])):", calc(*[3, 4]))
print('print(calc()):', calc())
