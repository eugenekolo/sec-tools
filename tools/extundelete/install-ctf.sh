#!/bin/sh

cd extundelete-0.2.4
sudo apt-get install -y e2fslibs-dev
./configure && make
ln -s $PWD/src/extundelete $CTF_ROOT/bin/extundelete
cd ..

