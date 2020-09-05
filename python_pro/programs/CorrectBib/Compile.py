def Introduction():
    print('Please choose the mode you want to modify the bib file:\n'
          'input b/w for the \'brief\' or \'whole\' version\n'
          'the 1st input for \\bibbrev\n'
          'the 2nd input for \\bibconf\n')
    option1, option2 = map(str, input().split(' '))
    while ((option1 != 'b') & (option1 != 'w')) | ((option2 != 'b') & (option2 != 'w')):
        print('Please input in the right format, like \'b w<ENTER>\' or \'w w<ENTER>\'. Thank you!')
        option1, option2 = map(str, input().split(' '))
    return option1, option2
# 返回第一个{后面那个字符所在位置,若无,返回-1
def TheFirstCurlyBrace(L):
    i = 0
    for ch in L:
        if ch == '{':
            return i + 1
        i += 1
    return -1


def WhatIsTheType(L, start):
    while L[start] == ' ':
        start += 1
    if L[start] != '\\':
        return 0
    else:
        if L[start:start + len('\\bibbrev')] == '\\bibbrev':
            return 1
        elif L[start:start + len('\\bibconf')] == '\\bibconf':
            return 2


def SelectTheBriefOne(L, start):
    L1 = ''
    height = 0
    for i in L[start:]:
        if i == '{':
            height += 1
            L1 += i
        elif i == '}':
            height -= 1
            if height < 0:
                break
            else:
                L1 += i
        else:
            L1 += i
    return L1


def SelectTheWholeOne(L, start):
    L1 = ''
    height = 0
    s = start
    for i in L[start:]:  # s停在{处
        if i == '{':
            height += 1
        elif i == '}':
            height -= 1
            if height < 0:
                s += 1
                break
        s += 1
    start = s+1  # start停在{后第一个字母
    height = 0
    for i in L[start:]:
        if i == '{':
            height += 1
            L1 += i
        elif i == '}':
            height -= 1
            if height < 0:
                break
            else:
                L1 += i
        else:
            L1 += i
    return L1


def SelectTheMiddleBrace(L, start):
    L1 = ''
    place = start
    for i in L[start:]:
        if i != ']':
            L1 += i
            place += 1
        else:
            break
    return L1, place + 2  # place+2为]{后的位置


class OneLine(object):
    def __init__(self, string):
        self.__line = string

    def JudgeType(self):
        start = TheFirstCurlyBrace(self.__line)
        if start == -1:
            l = Normal(self.__line, start)
            return l
        else:
            whichtype = WhatIsTheType(self.__line, start)
            if whichtype == 0:
                l = Normal(self.__line, start)
            elif whichtype == 1:
                l = Brev(self.__line, start)
            elif whichtype == 2:
                l = Conf(self.__line, start)
            return l


class Normal(OneLine):
    def __init__(self, string, begin):
        self.__line = string
        self.__start = begin


    def put(self, option1, option2):
        with open('output.bib', 'a') as f:
            f.write(self.__line)


class Brev(OneLine):
    def __init__(self, string, begin):
        self.__line = string
        self.__start = begin

    def put(self, option1, option2):
        with open('output.bib', 'a') as f:
            if option1 == 'b':
                self.__line = self.__line[:self.__start] + SelectTheBriefOne(
                    self.__line, self.__start + len('\\bibbrev{')) + '},\n'
            elif option1 == 'w':
                self.__line = self.__line[:self.__start] + SelectTheWholeOne(self.__line,
                                                                                 self.__start + len('\\bibbrev{')) + '},\n'
            for i in self.__line:
                f.write(i)


class Conf(OneLine):
    def __init__(self, string, begin):
        self.__line = string
        self.__start = begin

    def put(self, option1, option2):
        with open('output.bib', 'a') as f:
            middle, place = SelectTheMiddleBrace(self.__line, self.__start + len('\\bibconf['))
            if option2 == 'b':
                self.__line = self.__line[:self.__start] + middle + ' ' + SelectTheBriefOne(self.__line,
                                                                                                  place) + '},\n'
            if option2 == 'w':
                self.__line = self.__line[:self.__start] + middle + ' ' + SelectTheWholeOne(self.__line,
                                                                                                  place) + '},\n'
            for i in self.__line:
                f.write(i)


with open('iottest.bib', 'r') as f:
    L = f.readlines()
with open('output.bib', 'w') as f:
    pass
option1, option2 = Introduction()

for i in L:
    line = OneLine(i)
    i = line.JudgeType()
    i.put(option1, option2)
