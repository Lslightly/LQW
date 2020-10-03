def reverse(s):
    rt = ''
    lens = len(s)
    for i in range(lens):
        rt += s[lens-i-1]
    return rt


def add(ch1, ch2, k, p3):
    str3 = ""
    i = ord(ch1) +1
    while i < ord(ch2):
        for j in range(k):
            str3 += chr(i)
        i += 1
    if p3 == 1:
        return str3
    elif p3 == 2:
        return reverse(str3)


def add1(ch1, ch2, k, p3):
    str3 = ""
    i = ord(ch1) +1
    while i < ord(ch2):
        for j in range(k):
            str3 += '*'
        i += 1
    return str3


# p1: p1 = 1,填充小写; p1 = 2,填充大写; p1 = 3,填充*
# p2: p2 = k,每个字母或数字填充数为k个
# p3: p3 = 1,顺序; p3 = 2,逆序
# 后继删除减号,右 <= 左,保留
# str1输入字符串
p1, p2, p3 = map(int, input().split(' '))
str1 = [0]*200
str1 = input()
lenstr1 = len(str1)
str1 += '.'
i = 0
while i < lenstr1:
    if ord(str1[i]) == ord('-'):
        if i-1 == -1:
            print('-', end="")
        elif i+1 == lenstr1:
            print('-', end="")
        else:
            while ord(str1[i]) == ord('-'):
                i += 1
                print('-', end="")
            continue
        i += 1
        continue
    if ord(str1[i+1]) != ord('-'):  # 正常打印
        print(str1[i], end="")
    else:  # 遇到-
        if ord(str1[i+2])-ord(str1[i]) == 1:  # 后继
            print("%c" % str1[i], end="")
            i = i+1
        elif ord(str1[i+2]) <= ord(str1[i]):  # 右 <= 左
            print("%c-" % str1[i], end="")
            i = i+1
        # 左 < 右,但是一个为数字，一个为小写字母
        elif (ord(str1[i+2]) > ord(str1[i])) & (((ord(str1[i]) <= ord('9')) & (ord(str1[i]) >= ord('0'))) & ((ord(str1[i+2]) <= ord('z')) & (ord(str1[i+2]) >= ord('a')))):
            print("%c-" % str1[i], end="")
            i += 1
        # 可展开
        else:
            if p1 == 1:
                print("%c%s" % (str1[i], add(str1[i], str1[i+2], p2, p3)), end="")
            elif p1 == 2:
                print("%c%s" % (str1[i], add(str1[i], str1[i+2], p2, p3).upper()), end="")
            else:
                print("%c%s" % (str1[i], add1(str1[i], str1[i+2], p2, p3).upper()), end="")
            i += 1
    i += 1
