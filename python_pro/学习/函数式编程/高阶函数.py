# https://www.liaoxuefeng.com/wiki/1016959663602400/1017329367486080
def add(x, y, f):
    return f(x)+f(y)


print(add(-1, -2, abs))
