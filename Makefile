
DOC_PREFIX = libchrysalis
DOC_ODIR = build/docs


docs:
	pandoc docs/base/extensions.7.md -s -t man -o $(DOC_ODIR)/$(DOC_PREFIX):extensions.7
	pandoc docs/base/C_PSAFE.3.md -s -t man -o $(DOC_ODIR)/$(DOC_PREFIX):C_PSAFE.3

.PHONY:
	docs

