wget -qO- qira.me/dl | unxz | tar x && cd qira
echo "[*] If this install fails, try changing the line PIP=pip2 to PIP=pip or vice versa in install.sh"
sed -i "s/PIP=\"pip\"/PIP=\"pip2\"/" ./install.sh
sed -i "s/apt-get install/apt-get install -y/" ./install.sh
./install.sh
sudo pip2 install gevent
ln -s /usr/local/bin/qira $CTF_ROOT/bin/qira

