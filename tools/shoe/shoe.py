#!/usr/bin/python
"""Socket wrapper to be netcat like

Inspired by shoe.rb from crowell @ https://github.com/crowell/shoe.rb
Tested on python2 and python3.

@note: Currently `tie` is bugged and blocks. KeyboardInterrupt doesn't exit properly...
@note: read_until_end is a bit broken. it's not guaranteed to end 1s after last char
    as such I recommend to use read_for(10) or something to guarantee the max is 10s.

@author: Eugene Kolo
@email: eugene@kolobyte.com
@date: Dec 2015

"""

import socket
import sys
import threading
import time
import re
import select

class Shoe():

    def __init__(self, host, port):
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._socket.connect((host, port))
        self._socket.setblocking(0)

    def write(self, data):
        """ 
        @note: Requires you to put a \n yourself.
        """
        self._socket.send(data)

    def read_for(self, secs):
        response = ""
        timeout = time.time() + secs
        while True:
            is_ready = select.select([self._socket], [], [], secs)
            try:
                if is_ready:
                    response += self._socket.recv(1)
            except:
                pass
            if timeout < time.time():
                break

        return response

    def read_until(self, mystr, is_regex=False):
        response = ""
        self._socket.setblocking(1)
        if is_regex:
            while not re.findall(mystr, response):
                response += self._socket.recv(1)
        else:
            while response.endswith(mystr) != True:
                response += self._socket.recv(1)

        self._socket.setblocking(0)
        return response

    def read_until_end(self, secs=1):
        """ 
        Defaults to 1 second between characters
        """
        response = ""
        timeout = time.time() + secs
        while True:
            is_ready = select.select([self._socket], [], [], secs)
            try:
                if is_ready:
                    response += self._socket.recv(1)
                    if timeout < time.time():
                        timeout = time.time() + 1 # You get one more second pal 
            except:
                pass
            if timeout < time.time():
                break
    
        return response

    def tie(self):
        self._socket.settimeout(None)

        ## Hey listen!
        def _listen():
            while True:
                data = self._socket.recv(4096)
                print(data)
        t = threading.Thread(target = _listen).start()

        ## Hey write!
        while True:
            payload = sys.stdin.readline()
            if payload == "":
                continue

            self.write(payload)

    def close(self):
        self._socket.close()
    