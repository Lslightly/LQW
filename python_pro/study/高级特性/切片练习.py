# https://www.liaoxuefeng.com/wiki/1016959663602400/1017269965565856
def trim(s):
    lens = len(s)
    for i in range(lens):
        if s[i] != ' ':
            s = s[i:]
            break
        if i == lens-1:
            return ''
    lens = len(s)
    for i in range(lens):
        if s[lens-i-1] != ' ':
            s = s[:lens-i]
            break
    return s


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
