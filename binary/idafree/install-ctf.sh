purple='\033[0;35m'
off='\033[0m'

wget https://out7.hex-rays.com/files/idafree50.exe
printf "${purple}We're about to launch idafree50.exe with Wine.\n"
printf "Press <next> for everything if you want the default installation to work.\n"
printf "This assumes your wine directory for C:\Program Files (x86) is:\n"
printf "~/drive_c/Program Files (x86)/ . If that's not true, you're on your own${off}\n"
wine idafree50.exe
# Click okay for everything
rm idafree50.exe
echo "wine \"$HOME/.wine/drive_c/Program Files (x86)/IDA Free/idag.exe\"" > $CTF_ROOT/bin/idafree
chmod +x $CTF_ROOT/bin/idafree

