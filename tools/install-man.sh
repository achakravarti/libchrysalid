#!/bin/sh

# Determing root directory for man pages; on Linux FHS it is /usr/local/man and
# in FreeBSD it is /usr/local/share/man
if [ "$(uname)" = "Linux" ]; then
	__man="/usr/local/man"
elif [ "$(uname)" = "FreeBSD" ]; then
	__man="/usr/local/share/man"
else
	echo "Unsupported OS; exiting..."
	exit
fi


# Ensure man page subdirectories exist
sudo mkdir -p $__man/man3
sudo mkdir -p $__man/man7


# Remove previous man paguxe documentation
sudo rm -f $__man/man3/libchrysalis:*
sudo rm -f $__man/man7/libchrysalis:*


# Find man page documentation
__man3=$(find build/docs/ -type f -name "*.3.gz")
__man7=$(find build/docs/ -type f -name "*.7.gz")


# Install man 3 documentation
for x in $__man3; do 
	sudo cp "$x" $__man/man3
done


# Install man 7 documentation
for x in $__man7; do 
	sudo cp "$x" $__man/man7
done


# Update manpage database
sudo mandb

