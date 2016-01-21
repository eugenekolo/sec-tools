#!/usr/bin/python
"""
Efficient dumb bruteforcer

@author: Eugene Kolo
@email: <firstname>@eugenekolo.com
@date: Dec 2015
"""
import string
import itertools

# See example below
def bruteforce(charset, minlength, maxlength):
    return (''.join(candidate)
        for candidate in itertools.chain.from_iterable(itertools.product(charset, repeat=i)
        for i in range(minlength, maxlength + 1)))

# Efficently bruteforces out everything that matches [a-z]{2,3}[0-9]{1,3}[0-9]{1,3}
# i.e. hf2492, gg22, ggg222222, etc.
for a in bruteforce(string.ascii_lowercase, 2, 3):
	for b in bruteforce(string.digits, 1, 3):
		for c in bruteforce(string.digits, 1, 3):
			pass	
