import random
import sys

class data:
    def __init__(self,num,sym,strk):
        self.num = num
        self.sym = sym
        self.strk = strk


def generate_alphavit():
    size_alpth = random.randint(1,100)
    alphavit = []
    for i in range(0,size_alpth,1):
        alphavit.append(random.randint(1,1000000))
    return alphavit

def generate_pattern(alphavit):
    ids = []
    for i in range(0,random.randint(0,10),1):
        ids.append(random.randint(0,len(alphavit)))
    for i in range(0,random.randint(0,4),1):
        ids[random.randint(1,len(ids))-1] = len(alphavit)
    return ids

def generate_text(alphavit):
    count_lines = random.randint(0,1000)
    text = []
    for i in range(0,count_lines)
        line = []
        for j in range(0,random.randint(0,80))
            line.append(alphavit[random.randint(0, len(alphavit))])
        text.append(line)
    return text





if __name__ == '__main__':
    random.seed()
    
    alphavit = generate_alphavit()
    ids = generate_pattern(alphavit)
    print(ids, ' ', len(alphavit))