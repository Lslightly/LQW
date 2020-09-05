def person(name, age, **kw):
    print('name:', name, 'age:', age, 'other:', kw)


print("person('Jack', 20, gender='Man', city='Los Angeles')")
person('Jack', 20, gender='Man', city='Los Angeles')

extra = {'city': 'Beijing', 'gender': 'Man'}
print("person('Michael', 20, extra)")
person('Michael', 20, **extra)
