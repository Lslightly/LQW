def judgew(x, y):  # 判断每重循环的阶数
    if x.isdigit() & y.isalpha():
        return 1
    elif (x.isdigit() & y.isdigit()) | (x.isalpha() & y.isalpha()):
        return 0
    elif x.isalpha() & y.isdigit():
        return -1


# t:表示几个程序 statement:表示他的说法，字符串 l:表示程序行数 w:表示复杂度幂次 0表示常数复杂度 其他表示n^w
# nume,numf:表示E,F数量
# pro:表示每行的代码 line:表示每行的情况,为list的list组
t = input()
t = int(t)
for i in range(t):  # 输入t段程序
    wsum = 0  # wsum:程序中幂次的和
    step = 0  # flag:F,E对应个数
    nume = 0
    numf = 0
    statement = [0]*2
    statement = input().split()
    l = int(statement[0])
    if ord(statement[1][2]) == ord('1'):  # 输入他的陈述的幂次
        w = 0
    else:
        w = int(statement[1][4:-1])
    line = []
    value = set([])
    linevalue = []
    flag = 0  # 标记循环0阶深度
    flagvalue = True
    for j in range(l):  # 输入程序
        pro = [0] * 110
        pro = input().split()
        if ord(pro[0]) == ord('F'):
            numf += 1
            wj = judgew(pro[2], pro[3])
            line.append([pro[0], pro[1], wj])
            value.add(pro[1])
            linevalue.append(pro[1])
            if len(value) != numf:
                flagvalue = False
        elif (ord(pro[0]) == ord('E')) & flagvalue:
            numf -= 1
            line.append(['E'])
            value.remove(linevalue[-1])
            linevalue.pop(-1)
    if (numf != 0) | (not flagvalue):
        print('ERR')



