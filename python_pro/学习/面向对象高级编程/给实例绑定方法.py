from types import MethodType


class Student(object):
    pass


def set_age(self, age):
    self.age = age


s = Student()
s.set_age = MethodType(set_age, s)
s.set_age(25)
print(s.age)
