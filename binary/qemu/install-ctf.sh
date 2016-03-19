echo "[*] Only installing i386, and ARM support for QEMU"
curl http://wiki.qemu-project.org/download/qemu-2.4.0.1.tar.bz2 | tar xj
cd qemu-2.4.0.1
./configure --target-list=i386-softmmu,arm-softmmu
make -j4
sudo make install

