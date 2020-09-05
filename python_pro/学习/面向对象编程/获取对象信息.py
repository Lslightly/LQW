class Mydog(object):
    def __len__(self):
        return 100


dog = Mydog()
print(dir(dog))
print(len(dog))
