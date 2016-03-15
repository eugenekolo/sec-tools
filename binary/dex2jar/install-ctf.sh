
wget https://github.com/pxb1988/dex2jar/releases/download/2.0/dex-tools-2.0.zip
unzip dex-tools-2.0.zip
rm dex-tools-2.0.zip
cd dex2jar-2.0
chmod +x ./*
ln -s $PWD/d2j-dex2jar.sh $CTF_ROOT/bin/dex2jar
