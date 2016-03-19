sudo apt-get install -y libgmp3-dev
git clone https://github.com/azet/msieve.git
cd msieve
make all
ln -s $PWD/msieve $CTF_ROOT/bin/msieve
