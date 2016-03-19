# -*- mode: ruby -*- vi: set ft=ruby :

$bootstrap = <<SCRIPT
sudo apt-get update
sudo apt-get install -y git
git clone https://github.com/eugenekolo/sec-tools.git /home/vagrant/sec-tools/
/home/vagrant/sec-tools/sec-tools setup
export CTF_ROOT="/home/vagrant/sec-tools"
./sec-tools/sec-tools install all
SCRIPT

Vagrant.configure(2) do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.hostname = "sec-tools"
  config.vm.provider "virtualbox" do |v|
    v.memory = 1024
  end
  config.vm.provision "shell", privileged: false, inline: $bootstrap
end
