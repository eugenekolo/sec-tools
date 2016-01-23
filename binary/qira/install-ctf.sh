wget -qO- qira.me/dl | unxz | tar x && cd qira
echo "If this install fails, try changing the line PIP=pip2 to PIP=pip or vice versa in install.sh"
sed -i "s/PIP=\"pip\"/PIP=\"pip2\"/" ./install.sh
./install.sh
ln -s /usr/local/bin/qira $CTF_ROOT/bin/qira

