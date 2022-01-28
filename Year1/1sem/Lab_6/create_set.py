import random

def det2x2(a11, a12, a21, a22):
    return a11*a22 - a12*a21

def det3x3(a, b, c):
    res = a[0] * det2x2(b[1], b[2], c[1], c[2]) - a[1] * det2x2(b[0], b[2], c[0], c[2]) + a[2] * det2x2(b[0], b[1], c[0], c[1]) 


file = open("full.txt", 'w')
file2 = open("Linux/full.txt", 'w')
n = 300
d = 3

file.write(str(n) + '\n')
L = []
for i in range(n):
    l = []
    s = ''
    for q in range(d):
        l.append(random.randint(-100, 100))
    if l not in L:
        L.append(l)


file.write(str(len(L)) + '\n')
for el in L:
    s = '{} {} {}\n'.format(el[0], el[1], el[2])
    file.write(s)
    file2.write(s)


file2.close()
file.close()
