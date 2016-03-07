#!/bin/bash -e

sudo apt-get install -y python-lzma
git clone --depth 1 https://github.com/devttys0/binwalk.git
sudo pip install -e binwalk

ln -s /usr/local/bin/binwalk $CTF_ROOT/bin
