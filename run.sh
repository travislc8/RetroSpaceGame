#!/bin/bash
ps -e | grep " main" | awk -F ' ' '{system("kill " $1)}'
cd build
swaymsg "workspace 2"
make
./main &> log.txt 
