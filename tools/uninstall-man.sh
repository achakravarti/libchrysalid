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


# Remove man pages documentation
sudo rm -f $__man/man3/libchrysalis:*
sudo rm -f $__man/man7/libchrysalis:*

