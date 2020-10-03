import sys
def trim(s):
    s1, s2 = '', ''
    flag = 0
    for i in s:
        if flag:
            s1 = s1+i
        elif (i != ' ') & (flag == 0):
            s1 = s1+i
            flag = 1
    s1 = s1[::-1]
    flag = 0
    for i in s1:
        if flag:
            s2 = s2+i
        elif (i != ' ') & (flag == 0):
            s2 = s2+i
            flag = 1
    s2 = s2[::-1]
    return s2

# 测试:
if trim('hello  ') != 'hello':
    print('测试失败!')
elif trim('  hello') != 'hello':
    print('测试失败!')
elif trim('  hello  ') != 'hello':
    print('测试失败!')
elif trim('  hello  world  ') != 'hello  world':
    print('测试失败!')
elif trim('') != '':
    print('测试失败!')
elif trim('    ') != '':
    print('测试失败!')
else:
    print('测试成功!')
