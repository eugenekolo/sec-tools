wget https://www.unix-ag.uni-kl.de/~conrad/krypto/pkcrack/pkcrack-1.2.2.tar.gz
tar xzf pkcrack-1.2.2.tar.gz
rm pkcrack-1.2.2.tar.gz
cd pkcrack-1.2.2/src
make
ln -s $PWD/extract $CTF_ROOT/bin/extract
ln -s $PWD/zipdecrypt $CTF_ROOT/bin/zipdecrypt
ln -s $PWD/pkcrack $CTF_ROOT/bin/pkcrack
ln -s $PWD/makekey $CTF_ROOT/bin/makekey
ln -s $PWD/findkey $CTF_ROOT/bin/findkey

