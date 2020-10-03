def takefirst(elem):  # 取第一个元素果实数量
    return elem[0]


m, n, k = input().split()  # m:表示行数  n:表示列数  k:表示时间
m = int(m)
n = int(n)
k = int(k)

# frunum[1],frunum[2]:表示(i,j)处  frunum[0]:表示花生数量
# i=0表示路面

# 输入frunum
exist = 0  # 存在的果实的株数
frunum = []
for i in range(m):
    str1=list(map(int, input().split(' ')))
    lenstr1 =len(str1)
    for j in range(lenstr1):
        frunum.append([str1[j], i+1, j+1])
frunum.append([0, 0, 0])
frunum.append([0, 0, 0])

# 对果实数从大到小排序
frunum.sort(key=takefirst)  # 以花生数量进行升序排序
frunum.reverse()  # 倒序

# 开始计时k 并 计数:sum1 i:第几柱比较大的
sum1 = 0
i = 0
k -= frunum[0][1]
if k-1 >= frunum[0][1]:  # 你第一柱总得采到吧,采不到也太惨了
    while k > 0:
        if (k-1 < abs(frunum[i+1][1]-frunum[i][1])+abs(frunum[i+1][2]-frunum[i][2])+frunum[i+1][1]+1) | (frunum[i+1][0] == 0):
            # k-1表示如果你这柱采了,要采下一株,判断能不能采,还有如果下一株是0，你为什么要去采它呢？
            sum1 += frunum[i][0]
            break
        else:
            sum1 += frunum[i][0]
            k -= 1
            k -= abs(frunum[i+1][1]-frunum[i][1])+abs(frunum[i+1][2]-frunum[i][2])
            i += 1
print(sum1)
