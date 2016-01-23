#!/bin/bash

echo [*] This is going to take a while ...
curl http://wiki.qemu-project.org/download/qemu-2.4.0.1.tar.bz2 | tar xj
cd qemu-2.4.0.1
./configure
make
