import random
import sys

class data:
    def __init__(self,num,sym,strk):
        self.num = num
        self.sym = sym
        self.strk = strk


def generate():

    dd=[]
    rint = random.randint(1, 1000)
    for i in range(0,rint,1):
        num = random.randint(0,999)
        sym = []
        strk = ''
        for j in range(0,3,1):
            sym.append(chr(random.randint(65,90)))
        rstr = random.randint(1, 64)
        for j in range(0,rstr,1):
            s = str(chr(random.randint(65,90)))
            strk+= s.lower()
        dd.append(data(num,sym,strk))
    return dd



if __name__ == '__main__':
    random.seed()
    


    dd = generate()
    for i in range(10):
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
    



            



