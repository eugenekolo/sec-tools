
wget https://raw.githubusercontent.com/iBotPeaches/Apktool/master/scripts/linux/apktool
wget https://bitbucket.org/iBotPeaches/apktool/downloads/apktool_2.0.3.jar
sudo apt-get install libc6:i386 libgcc1:i386 gcc-4.6-base:i386 libstdc++5:i386 libstdc++6:i386
mv apktool_2.0.3.jar apktool.jar
chmod +x apktool.jar
chmod +x apktool
ln -s $PWD/apktool.jar $CTF_ROOT/bin
ln -s $PWD/apktool $CTF_ROOT/bin

