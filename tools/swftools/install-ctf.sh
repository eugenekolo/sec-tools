wget http://www.swftools.org/swftools-0.9.2.tar.gz
tar xzf swftools-0.9.2.tar.gz
rm swftools-0.9.2.tar.gz
cd swftools-0.9.2
./configure --prefix="${CTF_ROOT}"
make && make install
rm -r ${CTF_ROOT}/share
