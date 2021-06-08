import math 

sum = 0
p = 0.1**(90)
q = 1 - p
for i in range(1,14):
    sum = sum + math.comb(13, i)*(p**i)*(q**(13-i))
    print(sum)