sudo apt-get install g++ libssl-dev
git clone https://github.com/bwall/HashPump.git
cd HashPump
make
ln -s $PWD/hashpump $CTF_ROOT/bin/hashpump
