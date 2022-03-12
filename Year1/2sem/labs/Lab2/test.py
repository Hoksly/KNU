from gen import genset
import time
import os
import subprocess


UPTO = 10**10

#Changing with *2 formula
START = 5000
diff = START


def write_to(batch, duration, name = 'out.txt'):
    file = open(name, 'a')
    file.write("{} {}\n".format(batch, duration))


while (START < UPTO):
    genset(diff)
    start = time.time()
    #bashCommand = "cwm --rdf test.rdf --ntriples > test.nt"
    process = subprocess.Popen('./main', stdout=subprocess.PIPE)
    process.communicate()
    end = time.time()
    print("Duration {} is {}".format(START, end-start))
    write_to(START, end-start)
    START += diff
