str1 = [0]*20
str1 = input()
len1 = len(str1)
flag = 1
for i in range(len1):
    if ord('.') == ord(str1[i]):
        flag = 2
        key = i
        break
    elif ord('/') == ord(str1[i]):
        flag = 3
        key = i
        break
    elif ord('%') == ord(str1[i]):
        flag = 4
        key = i
        break
if flag == 1:  # 整数部分,数字为0处理,最后为0处理
    if int(str1) == 0:
        print(0)
    else:
        k = len1
        for i in range(len1):  # 最后一位是0处理
            if ord(str1[len1-1-i]) == ord('0'):
                k -= 1
            else:
                break
        for i in range(k):
            print(str1[k-1-i], end="")
elif flag == 2:  # 小数部分,小数点前面部分与整数部分处理方式类似
    if int(str1[0]) == 0:    # 小数点后面部分仅相反,key为小数点前位数
        print(0, end="")
    else:
        k = key
        for i in range(key):
            if ord(str1[key-1-i]) == ord('0'):
                k -= 1
            else:
                break
        for i in range(k):
            print(str1[k-1-i], end="")
    print('.', end="")  # 处理后面部分
    k = key+1
    while k < len1:
        if ord(str1[k]) == ord('0'):
            k += 1
        else:
            break
    if k == len1:
        print(0)
    else:
        i = len1-1
        while i >= k:
            print(str1[i], end="")
            i -= 1
elif flag == 3:  # 处理,借用整数的处理方式即可,对分子的0进行处理
    if int(str1[0]) == 0:
        print(0, end="")
    else:
        k = key
        for i in range(key):
            if ord(str1[key - 1 - i]) == ord('0'):
                k -= 1
            else:
                break
        for i in range(k):
            print(str1[k - 1 - i], end="")
    print('/', end="")  # 处理后面部分
    k = len1-1
    while k > key:
        if ord(str1[k]) == ord('0'):
            k-=1
        else:
            break
    while k > key:
        print(str1[k], end="")
        k -= 1
else:  # 处理百分数部分
    if int(str1[0]) == 0:
        print(0, end="")
    else:
        k = key
        for i in range(key):
            if ord(str1[key - 1 - i]) == ord('0'):
                k -= 1
            else:
                break
        for i in range(k):
            print(str1[k - 1 - i], end="")
    print('%', end="")