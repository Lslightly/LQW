n = input()
L = list(map(int, input().split(' ')))
L.sort()
for i in L[:-1]:
    print(i, end=" ")
print(L[-1], end="")
