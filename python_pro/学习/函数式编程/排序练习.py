# https://www.liaoxuefeng.com/wiki/1016959663602400/1017408670135712
def by_name(t):
    return t[0]


def by_score(t):
    return t[1]


L = [('Bob', 75), ('Adam', 92), ('Bart', 66), ('Lisa', 88)]
L2 = sorted(L, key=by_name)     # 按姓名ASCII码从小到大排序
print(L2)
L2 = sorted(L, key=by_score, reverse=True)  # 成绩从高到低排序
print(L2)
