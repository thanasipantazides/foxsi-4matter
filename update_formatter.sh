#!/bin/zsh
# Because Raspberry Pi is not usually connected to internet,
# this script pulls latest git and copies it to the Pi for testing.

cd ~/Documents/FOXSI/foxsi4-formatter
git pull
scp -r ~/Documents/FOXSI/foxsi4-formatter foxsi@raspberrypi.local:/home/foxsi/
echo "all done!"
