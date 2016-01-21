#!/usr/bin/python

##########################
# cribdrag - An interactive crib dragging tool
# Daniel Crowley
# Copyright (C) 2013 Trustwave Holdings, Inc.
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
# You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
##########################

import sys
import argparse

def sxor(s1,s2):    
    # convert strings to a list of character pair tuples
    # go through each tuple, converting them to ASCII code (ord)
    # perform exclusive or on the ASCII code
    # then convert the result back to ASCII (chr)
    # merge the resulting array of characters as a string
    return ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(s1,s2))

parser = argparse.ArgumentParser(description='xorstrings is a utility which comes with cribdrag, the interactive crib dragging tool. xorstrings takes two ASCII hex encoded strings and XORs them together. This can be useful when cryptanalyzing ciphertext produced by the One Time Pad algorithm or a stream cipher when keys are reused, as one can XOR two ciphertexts together and then crib drag across the result, which is both plaintexts XORed together.')
parser.add_argument('data1', help='Data encoded in an ASCII hex format (ie. ABC would be 414243)')
parser.add_argument('data2', help='Data encoded in an ASCII hex format (ie. ABC would be 414243)')
args = parser.parse_args()

s1 = args.data1.decode('hex')
s2 = args.data2.decode('hex')

s3 = sxor(s1, s2)

print s3.encode('hex')

