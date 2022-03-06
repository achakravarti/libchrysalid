# Source directory of man page markdown files.
MAN_IDIR=docs/man

# Output directory of generated man pages.
MAN_ODIR=build/docs/man

MAN_3DIR=/usr/local/man/man3
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
	pandoc $< -s -t man -o $@

clean:
	rm -f $(MAN_ODIR)/man3/*
	rm -f $(MAN_ODIR)/man7/*

install: $(MAN_PG)
	sudo mkdir -p $(MAN_3DIR)
	sudo mkdir -p $(MAN_7DIR)
	sudo rm -f $(MAN_3DIR)/$(MAN_NS)*
	sudo rm -f $(MAN_7DIR)/$(MAN_NS)*
	cd $(MAN_ODIR)/man3;							\
	for f in *.3;								\
		do sudo cp -v -- "$$f" "$(MAN_3DIR)/$(MAN_NS):$$f";		\
	done
	cd $(MAN_ODIR)/man7;							\
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

.PHONY:
	clean docs install uninstall

