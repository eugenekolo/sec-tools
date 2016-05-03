#!/bin/bash

wget http://www.sno.phy.queensu.ca/~phil/exiftool/Image-ExifTool-10.15.tar.gz
tar xzf Image-ExifTool-10.15.tar.gz
rm Image-ExifTool-10.15.tar.gz
cd Image-ExifTool-10.15
perl Makefile.PL
make
ln -s $PWD/exiftool $CTF_ROOT/bin/exiftool
