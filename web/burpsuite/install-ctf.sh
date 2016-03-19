wget -O ./burp.jar 'https://portswigger.net/DownloadUpdate.ashx?Product=Free'
chmod 755 ./burp.jar
ln -s $PWD/burp.jar $CTF_ROOT/bin/burpsuite
