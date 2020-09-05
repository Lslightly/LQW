class Student(object):
    name = 'Student'


s = Student()
print(s.name)  # 打印name属性，因为实例并没有name属性，所以会继续查找class的name属性
print(Student.name)  # 打印类的name属性
s.name = 'Michael'
print(s.name)  # 实例属性优先级高于类属性
print(Student.name)
del s.name  # 删除实例属性
print(s.name)
# 结果：
# Student
# Student
# Michael
# Student
# Student
