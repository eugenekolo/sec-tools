sudo apt-get install -y python-pip python-dev libffi-dev libssl-dev libxml2-dev libxslt1-dev libjpeg8-dev zlib1g-dev
sudo pip2 install mitmproxy
ln -s /usr/local/bin/mitmdump $CTF_ROOT/bin/mitmdump
ln -s /usr/local/bin/mitmweb $CTF_ROOT/bin/mitmweb
ln -s /usr/local/bin/mitmproxy $CTF_ROOT/bin/mitmproxy
