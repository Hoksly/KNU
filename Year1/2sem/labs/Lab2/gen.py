from random import randint, choice
import string

def genword(l:int):
    if l == 0:
        return ''
    else:
        return genword(l-1) + choice(string.ascii_letters)

def genset(num):
    s = ''
    for i in range(num):
        l = randint(1, 128)
        s += genword(l) + '\n'
        
    file = open('input.txt', 'a')
    file.write(s)
    file.close()
