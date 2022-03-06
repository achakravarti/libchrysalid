# Source directory of man page markdown files.
MAN_IDIR=docs/man

# Output directory of generated man pages.
MAN_ODIR=build/docs/man

# Source Markdown files for man pages
MAN_SRC!=find $(MAN_IDIR)/ -type f -name '*.md' | sort

# Generated man pages from Markdown source files.
MAN_PG=$(MAN_SRC:$(MAN_IDIR)/%.md=$(MAN_ODIR)/%)


#DOC_PREFIX = libchrysalis
#DOC_ODIR = build/docs


#docs:
	#pandoc docs/base/extensions.7.md -s -t man -o $(DOC_ODIR)/$(DOC_PREFIX):extensions.7
	#pandoc docs/base/C_PSAFE.3.md -s -t man -o $(DOC_ODIR)/$(DOC_PREFIX):C_PSAFE.3
	#sudo mkdir -p /usr/local/man/man3 /usr/local/man/man7
	#sudo cp $(DOC_ODIR)/$(DOC_PREFIX):extensions.7 /usr/local/man/man7/$(DOC_PREFIX):extensions.7
	#sudo cp $(DOC_ODIR)/$(DOC_PREFIX):C_PSAFE.3 /usr/local/man/man3/$(DOC_PREFIX):C_PSAFE.3
	#sudo gzip -f /usr/local/man/man7/$(DOC_PREFIX):extensions.7
	#sudo gzip -f /usr/local/man/man3/$(DOC_PREFIX):C_PSAFE.3
	#sudo mandb


docs: $(MAN_PG)

$(MAN_PG): $(MAN_SRC)

$(MAN_ODIR)/%: $(MAN_IDIR)/%.md
	pandoc $< -s -t man -o $@

clean:
	rm -f $(MAN_ODIR)/man3/*
	rm -f $(MAN_ODIR)/man7/*

.PHONY:
	clean docs

