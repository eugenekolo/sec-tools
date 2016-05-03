#!/bin/bash
wget http://www.stillhq.com/pngtools/source/pngtools_0_4.tgz
tar xzf pngtools_0_4.tgz
rm pngtools_0_4.tgz
cd pngtools-0.4
./configure --prefix=$CTF_ROOT
make
make install

