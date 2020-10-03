# https://www.liaoxuefeng.com/wiki/1016959663602400/1017329367486080
def normalize(name):
    name = name.capitalize()
    return name


L1 = ['adam', 'LISA', 'barT']
L2 = list(map(normalize, L1))
print(L2)
