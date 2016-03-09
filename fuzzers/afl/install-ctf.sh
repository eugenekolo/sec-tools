wget http://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz
tar xzf afl-latest.tgz 
rm afl-latest.tgz
mv afl-*/ afl
cd afl
ls -la 
make

cd qemu_mode
sudo apt-get install -y bison libglib2.0-dev
./build_qemu_support.sh
cd ../..

ln -s $PWD/afl/{afl-as,afl-cmin,afl-fuzz,afl-gcc,afl-gotcpu,afl-plot,afl-qemu-trace,afl-showmap,afl-tmin,afl-whatsup} $CTF_ROOT/bin
