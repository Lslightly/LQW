# https://www.liaoxuefeng.com/wiki/1016959663602400/1017268131039072
def move(n, a, b, c):
    if n == 1:
        print(a, '-->', c)
    else:
        move(n-1, a, c, b)
        print(a, '-->', c)
        move(n-1, b, a, c)


n = input()
n = int(n)
move(n, 'A', 'B', 'C')
