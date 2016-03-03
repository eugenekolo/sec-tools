#!/bin/bash
purple='\033[0;35m'
off='\033[0m'
wget http://mh-nexus.de/downloads/HxDSetupEN.zip
unzip HxDSetupEN.zip
printf "${purple}We're about to launch setup.exe with Wine.\n"
printf "Press <next> for everything if you want the default installation to work.\n"
printf "This assumes your wine directory for C:\Program Files (x86) is:\n"
printf "~/drive_c/Program Files (x86)/ . If that's not true, you're on your own${off}\n"
wine setup.exe
rm setup.exe
rm HxDSetupEN.zip
echo "\"wine $HOME/.wine/drive_c/Program Files (x86)/HxD/HxD.exe\"" > $CTF_ROOT/bin/hxd
chmod +x $CTF_ROOT/bin/hxd



