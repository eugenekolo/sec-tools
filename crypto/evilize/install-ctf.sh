wget http://www.mscs.dal.ca/~selinger/md5collision/downloads/evilize-0.2.tar.gz
tar zvxf evilize-0.2.tar.gz
rm evilize-0.2.tar.gz
cd evilize-0.2
make
cd ..
ln -s $PWD/evilize-0.2/evilize $CTF_ROOT/bin/evilize
ln -s $PWD/evilize-0.2/md5coll $CTF_ROOT/bin/md5coll


