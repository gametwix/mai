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

def generate_pattern():
    




if __name__ == '__main__':
    random.seed()
    


    
    for i in range(5):
        dd = generate(i)
        with open("tests/test_"+str(i)+".t","w") as f:
            for d in dd:
                f.write(d.sym[0] + ' ' + str(d.num).rjust(3,'0') + ' ' + d.sym[1] + d.sym[2] + '\t'+d.strk + '\n')

        dd = sorted(dd,key=lambda x: x.sym[2])
        dd = sorted(dd,key=lambda x: x.sym[1])
        dd = sorted(dd,key=lambda x: x.num)
        dd = sorted(dd,key=lambda x: x.sym[0])

        with open("tests/test_"+str(i)+".a","w") as f:
            for d in dd:
                f.write(d.sym[0] + ' ' + str(d.num).rjust(3,'0') + ' ' + d.sym[1] + d.sym[2] + '\t'+d.strk + '\n')
    