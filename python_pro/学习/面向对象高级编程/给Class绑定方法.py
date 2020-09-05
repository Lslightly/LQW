class Student(object):
    pass


def set_score(self, score):
    self.score = score


Student.set_score = set_score
s = Student()
s.set_score(100)
print(s.score)
