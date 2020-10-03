# https://www.liaoxuefeng.com/wiki/1016959663602400/1017316949097888
def findMinAndMax(L):
    if not L:
        return None, None
    else:
        maxn = 0
        minn = L[0]
        for i in L:
            maxn = max(maxn, i)
            minn = min(minn, i)
        return minn, maxn


if findMinAndMax([]) != (None, None):
    print('测试失败!')
elif findMinAndMax([7]) != (7, 7):
    print('测试失败!')
elif findMinAndMax([7, 1]) != (1, 7):
    print('测试失败!')
elif findMinAndMax([7, 1, 3, 9, 5]) != (1, 9):
    print('测试失败!')
else:
    print('测试成功!')
