sudo apt-get install -y gcc-multilib
git clone https://github.com/codelion/pathgrind.git
cd pathgrind
git apply ../pathgrind.patch
./install.sh

ln -s $PWD/fuzz/fuzz.py $CTF_ROOT/bin/pathgrind-fuzz
ln -s $PWD/fuzz/gui.py $CTF_ROOT/bin/pathgrind-gui
ln -s $PWD/fuzz/plotfuzz.py $CTF_ROOT/bin/pathgrind-plot
