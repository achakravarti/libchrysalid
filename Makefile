
MAN_PREFIX = libchrysalis


docs
	pandoc base/extensions.7.md -s -t man -o $(MAN_PREFIX):extensions.7
	pandoc base/C_PSAFE.3.md -s -t man -o $(MAN_PREFIX):C_PSAFE.3

