# Source directory of man page markdown files.
MAN_IDIR=docs/man

# Output directory of generated man pages.
MAN_ODIR=build/docs/man

# System directory for section 3 man pages.
MAN_3DIR=/usr/local/man/man3

# System directory for section 7 man pages.
MAN_7DIR=/usr/local/man/man7

# Source Markdown files for man pages
MAN_SRC!=find $(MAN_IDIR)/ -type f -name '*.md' | sort

# Generated man pages from Markdown source files.
MAN_PG=$(MAN_SRC:$(MAN_IDIR)/%.md=$(MAN_ODIR)/%)

# Man page title namespace
MAN_NS=libchrysalid


tests: build/test
	build/test

build/test: src/hptr.c src/utf8.c tests/hptr.c tests/utf8.c
	mkdir -p build
	clang src/hptr.c src/utf8.c tests/hptr.c tests/utf8.c -lpcre2-8 -lcriterion -o build/test

man:
	tools/mandoc.sh
	tools/install-man.sh

docs: $(MAN_PG)

$(MAN_PG): $(MAN_SRC)

$(MAN_ODIR)/%: $(MAN_IDIR)/%.md
	pandoc $< --bibliography=docs/references.bib --citeproc -s -t man -o $@

clean:
	rm -f $(MAN_ODIR)/*
	rm -f $(MAN_ODIR)/*

install: $(MAN_PG)
	sudo mkdir -p $(MAN_3DIR)
	sudo mkdir -p $(MAN_7DIR)
	sudo rm -f $(MAN_3DIR)/$(MAN_NS)*
	sudo rm -f $(MAN_7DIR)/$(MAN_NS)*
	cd $(MAN_ODIR);								\
	for f in *.3;								\
		do sudo cp -v -- "$$f" "$(MAN_3DIR)/$(MAN_NS):$$f";		\
	done
	cd $(MAN_ODIR);								\
	for f in *.7;								\
		do sudo cp -v -- "$$f" "$(MAN_7DIR)/$(MAN_NS):$$f";		\
	done
	for f in $(MAN_3DIR)/$(MAN_NS)*;					\
		do sudo gzip -f "$$f";						\
	done
	for f in $(MAN_7DIR)/$(MAN_NS)*;					\
		do sudo gzip -f "$$f";						\
	done
	sudo mandb

uninstall: $(MAN_3DIR) $(MAN_7DIR)
	sudo rm -f $(MAN_3DIR)/$(MAN_NS)*
	sudo rm -f $(MAN_7DIR)/$(MAN_NS)*
	sudo mandb

examples: build/examples/cjson
	build/examples/cjson

build/examples/cjson: src/hptr.c src/utf8.c examples/cjson.c
	mkdir -p build/examples
	clang src/hptr.c src/utf8.c examples/cjson.c -lpcre2-8 -o build/examples/cjson

.PHONY:
	clean docs install uninstall

