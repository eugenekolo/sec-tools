echo "[*] This can take a while as you might need Java"
sudo apt-get install openjdk-7-jre

wget -O ./burp.jar 'https://portswigger.net/DownloadUpdate.ashx?Product=Free'
chmod 755 ./burp.jar
ln -s $PWD/burp.jar $CTF_ROOT/bin/burpsuite
