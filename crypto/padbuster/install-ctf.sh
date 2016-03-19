sudo apt-get install -y libssl-dev
git clone https://github.com/GDSSecurity/PadBuster.git
(echo o conf prerequisites_policy follow;echo o conf commit; echo install Crypt::SSLeay;)|sudo cpan
ln -s $PWD/PadBuster/padBuster.pl $CTF_ROOT/bin/padbuster
chmod +x $CTF_ROOT/bin/padbuster

