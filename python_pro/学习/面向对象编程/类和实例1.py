class Student(object):

    def __init__(self, name, score):
        self.name = name
        self.score = score


bart = Student('Bart', 59)
lisa = Student('Lisa', 87)
bart.age = 8
print(bart.age)
print(lisa.age)
