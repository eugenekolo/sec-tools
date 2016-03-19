# -*- mode: ruby -*-
# vi: set ft=ruby :

$bootstrap = <<SCRIPT
sudo apt-get update
sudo apt-get install git
git clone https://github.com/eugenekolo/sec-tools.git /home/vagrant/sec-tools/
/home/vagrant/sec-tools/sec-tools setup && source ~/.bashrc
SCRIPT

Vagrant.configure(2) do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.hostname = "sec-tools"
  config.vm.provision "shell", privileged: false, inline: $bootstrap
end
