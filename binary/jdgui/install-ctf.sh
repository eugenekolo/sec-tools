mkdir -p jdgui
cd jdgui
wget http://jd.benow.ca/jd-gui/downloads/jd-gui-0.3.5.linux.i686.tar.gz
tar xzf jd-gui-0.3.5.linux.i686.tar.gz
rm jd-gui-0.3.5.linux.i686.tar.gz
ln -s $PWD/jd-gui $CTF_ROOT/bin/jdgui

