a = [0]*6
b = [0]*6
a = input()
b = input()
lena = len(a)
lenb = len(b)
suma = 1
sumb = 1
for i in range(lena):
    suma *= ord(a[i]) - ord('A') + 1
for i in range(lenb):
    sumb *= ord(b[i]) - 64
suma %= 47
sumb %= 47
if suma == sumb:
    print('GO')
else:
    print('STAY')
