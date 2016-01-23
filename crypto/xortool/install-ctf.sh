git clone https://github.com/hellman/xortool.git
sudo pip2 install -e ./xortool

ln -s $PWD/xortool/xortool/xortool $CTF_ROOT/bin/xortool
ln -s $PWD/xortool/xortool/xortool-xor $CTF_ROOT/bin/xortool-xor
