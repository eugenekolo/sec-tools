wget http://upx.sourceforge.net/download/upx-3.91-amd64_linux.tar.bz2
tar xjf upx-3.91-amd64_linux.tar.bz2
rm upx-3.91-amd64_linux.tar.bz2
mv upx-3.91-amd64_linux upx
ln -s $PWD/upx/upx $CTF_ROOT/bin/upx
