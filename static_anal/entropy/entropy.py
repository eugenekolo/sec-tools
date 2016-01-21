#!/usr/bin/python

import sys, os           
import math

def entropy(byteArr,fileSize):
    freqList = [0]*fileSize
    for b in range(256):
        ctr = 0.0
        for byte in byteArr:
            if ord(byte) == b:
                ctr += 1  
        freqList.append(float(ctr) / fileSize)
    ent = 0.0
    for freq in freqList:
        if freq > 0:
            ent = ent + (freq * math.log(freq, 2))
    ent = -ent
    print 'entropy (bits per character):',ent
    return ent

if len(sys.argv) < 2:
    print("Usage: {} <filename>".format(sys.argv[0]))
    exit(1)

fname = sys.argv[1]
f = open(fname) 
f.seek(0,2)
size = f.tell()
f.seek(0,0)
ent = entropy(f.read(),size)
print "File :\t",fname,"\tEntropy :",ent            
        
