#!/bin/bash

tar xzf Image-ExifTool-10.15.tar.gz
rm Image-ExifTool-10.15.tar.gz
cd Image-ExifTool-10.15
perl Makefile.PL
make
ln -s $PWD/exiftool $CTF_ROOT/bin/exiftool
export PERL5LIB=${PERL5LIB}:${PWD}/lib
