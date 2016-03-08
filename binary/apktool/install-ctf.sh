
wget https://raw.githubusercontent.com/iBotPeaches/Apktool/master/scripts/linux/apktool
wget https://bitbucket.org/iBotPeaches/apktool/downloads/apktool_2.0.3.jar
mv apktool_2.0.3.jar apktool.jar
chmod +x apktool.jar
chmod +x apktool
ln -s $PWD/apktool.jar $CTF_ROOT/bin
ln -s $PWD/apktool $CTF_ROOT/bin

