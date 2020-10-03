class MyObject(object):
    def __init__(self):
        self.x = 9

    def power(self):
        return self.x * self.x


obj = MyObject()
print(hasattr(obj, 'x'))  # 有属性'x'吗
print(obj.x)
print(hasattr(obj, 'y'))
setattr(obj, 'y', 19)  # 设置属性y
print(hasattr(obj, 'y'))
print(getattr(obj, 'y'))
print(obj.y)
print(getattr(obj, 'z', 404))   # 获取属性'z',如果存在,返回属性值,不存在返回默认值
