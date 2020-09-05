word = [0]*10
str1 = [0]*1000000
word = input()
str1 = input()
lenword = len(word)
word = word.lower()
str1 = str1.lower()
times = 0
key = 0
flag = False
lenstr1 = len(str1)
spaceflag = True
for i in range(lenstr1):
    if ord(str1[i]) == ord(' '):
        if flag & (i-key == lenword):
            times += 1
            if times == 1:
                k = key
        flag = False
        spaceflag = True
    elif (not flag) & (ord(str1[i]) != ord(word[0])) & (spaceflag):
        spaceflag = False
    elif (not flag) & (ord(str1[i]) == ord(word[0])) & (spaceflag):
            flag = True
            key = i
            spaceflag = False
    elif flag:
        if i-key >= lenword:
            flag = False
        elif ord(str1[i]) != ord(word[i-key]):
            flag = False
if times == 0:
    print(-1)
else:
    print(times, k)
