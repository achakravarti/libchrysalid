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
MAN_NS=libchrysalis


docs: $(MAN_PG)

$(MAN_PG): $(MAN_SRC)

$(MAN_ODIR)/%: $(MAN_IDIR)/%.md
	pandoc $< --bibliography=docs/references.bib --citeproc -s -t man -o $@

clean:
	rm -f $(MAN_ODIR)/*
	rm -f $(MAN_ODIR)/*
	rm -f build/heap

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

examples: build/heap

build/heap:
	gcc -Wall -Wextra -g -fPIC src/heap.c src/heap-std.c examples/heap.c -o build/heap

.PHONY:
	clean docs install uninstall examples

