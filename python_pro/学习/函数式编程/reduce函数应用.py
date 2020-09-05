# https://www.liaoxuefeng.com/wiki/1016959663602400/1017329367486080
from functools import reduce


def fn(x, y):
    return 10 * x + y


print(reduce(fn, [1, 3, 5, 7, 9]))
