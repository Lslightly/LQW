import functools


def log(func):
    @functools.wraps(func)
    def wrapper(*args, **kw):
        print('call %s():' % func.__name__)
        print(wrapper.__name__)
        return func()

    return wrapper


@log
def now():
    print('2015-3-25')


now()
print(now.__name__)
