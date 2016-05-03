wget "https://downloads.sourceforge.net/project/yafu/1.34/yafu-1.34.zip?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fyafu%2F&ts=1446080941&use_mirror=skylineservers" -O yafu.zip
mkdir yafu
mv yafu.zip yafu
cd yafu
unzip yafu.zip
chmod 755 yafu
ln -s $PWD/yafu $CTF_ROOT/bin/yafu
