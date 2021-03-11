import random

random.seed()
size = int(input())
test = []
ans = []

for i in range(size):
    a = random.randint(0,100000000000000000000000)
    b = random.randint(0,100000000000000000000000)
    s = random.randint(0,2)
    sym = ' '
    if s == 0:
        sym = '+'
        ans.append(a + b)
    elif s == 1:
        sym = '-'
        if b > a :
            ans.append('Error')
        else:
            ans.append(a - b)
    elif s == 2:
        sym = '*'
        ans.append(a * b)
    test.append(a)
    test.append(b)
    test.append(sym)
    

with open("test","w") as f:
    for s in test:
        f.write(str(s)+"\n")
with open("ans","w") as f:
     for s in ans:
        f.write(str(s)+"\n")
