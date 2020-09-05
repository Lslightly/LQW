L = ['Micheal', 'Mike', 'Jane']
# L[x:y:step] 从x到y(不包括y)的元素,step表示步长
# x不存在表示从0开始
# y不存在表示到-1为止,包括-1
print(L[:3])  # 从索引0开始不包含索引3
print(L[-2:-1])  # 不包括-1
print(L[-2:])
print(L[::2])
print((0, 1, 2, 3, 4, 5, 6)[:3])
print('THREELWLQO'[-9::2])

