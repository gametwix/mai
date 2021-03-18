import random

random.seed()
size = int(input())
test = []
ans = []

for i in range(size):
    a = random.randint(pow(10,100000),pow(10,1000000))
    b = random.randint(pow(10,100000),pow(10,1000000))
    sym = '*'

    ans.append(a * b)
    #ans.append(a - b)
    test.append(a)
    test.append(b)
    test.append(sym)
    

with open("test","w") as f:
    for s in test:
        f.write(str(s)+"\n")
with open("ans","w") as f:
     for s in ans:
        f.write(str(s)+"\n")
