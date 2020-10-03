import functools


int2 = functools.partial(int, base=2)
max10 = functools.partial(max, 10)

print(int2('1111'))
print(max10(1, 2, 3))
