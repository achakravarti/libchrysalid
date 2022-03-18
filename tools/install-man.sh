#!/bin/sh


# Ensure man page subdirectories exist
sudo mkdir -p /usr/local/share/man/man3
sudo mkdir -p /usr/local/share/man/man7


# Remove previous man page documentation
sudo rm -f /usr/local/share/man/man3/libchrysalis:*
sudo rm -f /usr/local/share/man/man7/libchrysalis:*


# Find man page documentation
__man3=$(find build/docs/ -type f -name "*.3.gz")
__man7=$(find build/docs/ -type f -name "*.7.gz")


# Install man 3 documentation
for x in $__man3; do 
	sudo cp "$x" /usr/local/share/man/man3
done


# Install man 7 documentation
for x in $__man7; do 
	sudo cp "$x" /usr/local/share/man/man7
done


# Update manpage database
sudo mandb

