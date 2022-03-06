
DOC_PREFIX = libchrysalis
DOC_ODIR = build/docs


docs:
	pandoc docs/base/extensions.7.md -s -t man -o $(DOC_ODIR)/$(DOC_PREFIX):extensions.7
	pandoc docs/base/C_PSAFE.3.md -s -t man -o $(DOC_ODIR)/$(DOC_PREFIX):C_PSAFE.3
	sudo mkdir -p /usr/local/man/man3 /usr/local/man/man7
	sudo cp $(DOC_ODIR)/$(DOC_PREFIX):extensions.7 /usr/local/man/man7/$(DOC_PREFIX):extensions.7
	sudo cp $(DOC_ODIR)/$(DOC_PREFIX):C_PSAFE.3 /usr/local/man/man3/$(DOC_PREFIX):C_PSAFE.3
	sudo gzip -f /usr/local/man/man7/$(DOC_PREFIX):extensions.7
	sudo gzip -f /usr/local/man/man3/$(DOC_PREFIX):C_PSAFE.3
	sudo mandb

.PHONY:
	docs

