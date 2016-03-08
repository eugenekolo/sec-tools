git clone https://github.com/GDSSecurity/PadBuster.git
perl -MCPAN -e 'install Crypt::SSLeay'
ln -s $PWD/PadBuster/padBuster.pl $CTF_ROOT/bin/padbuster
chmod +x $CTF_ROOT/bin/padbuster
