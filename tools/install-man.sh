#!/bin/sh


sudo mkdir -p /usr/local/man/man3
sudo rm -f /usr/local/man/man3/libchrysalid:*


__man3=$(find build/docs/ -type f -name "*.3.gz")

for x in $__man3; do 
	sudo cp "$x" /usr/local/man/man3
done

sudo mandb

