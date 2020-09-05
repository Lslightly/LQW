global m
m = [0]*1001
m[1] = 0


def jie(x):
    a = 0
    while x != 0:
        a += 1
        x //= 10
    return a


def seek(x, c, num):
    for i in range(c//2+1):
        if i == 0:
            continue
        else:
            if m[i] == 0:
                num += 1
                m[i] = seek(x+i*10**jie(c), i, 0)
                num += m[i]
            else:
                num += 1 + m[i]
    return num


n = input()
n = int(n)
num1 = seek(n, n, 0)
print(num1+1)