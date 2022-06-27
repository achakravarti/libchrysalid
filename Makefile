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

# External sources
EXT_SRC=external/cJSON/cJSON.c external/cJSON/cJSON_Utils.c \
	external/iniparser/src/dictionary.c external/iniparser/src/iniparser.c
EXT_OBJ=$(EXT_SRC:%.c=build/%.o)

CC=clang

# Libchrysalid library sources
LIB_SRC!=find src/ -type f -name '*.c' | sort
LIB_OBJ=$(LIB_SRC:src/%.c=build/%.o)
LIB_BIN=build/libchrysalid.so

build/%.o: src/%.c
	$(CC) -fPIC -Wall -c $< -o $@

build/external/cJSON/%.o: external/cJSON/%.c
	mkdir -p build/external/cJSON
	$(CC) -fPIC -Wall -c $< -o $@

build/external/iniparser/src/%.o: external/iniparser/src/%.c
	mkdir -p build/external/iniparser/src
	$(CC) -fPIC -Wall -c $< -o $@

$(LIB_BIN): $(LIB_OBJ) $(EXT_OBJ)
	mkdir -p build/external/iniparser/src
	$(CC) -rdynamic -lpcre2-8 -shared $^ -o $@

lib: $(LIB_BIN)

tests: build/test
	$<

build/test: $(LIB_SRC) $(EXT_SRC) tests/hptr.c tests/utf8.c
	mkdir -p build
	$(CC) $^ -lpcre2-8 -lcriterion -o $@

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
	rm -f build/examples/*
	rm -f build/test
	rm -f build/*.o

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

examples: build/examples/json build/examples/log build/examples/cfg
	build/examples/json
	build/examples/log
	build/examples/cfg

build/examples/json: $(LIB_SRC) $(EXT_SRC) examples/json.c
	mkdir -p build/examples
	$(CC) $^ -lpcre2-8 -o $@

build/examples/log: $(LIB_SRC) $(EXT_SRC) examples/log.c
	mkdir -p build/examples
	$(CC) $^ -lpcre2-8 -o $@

build/examples/cfg: $(LIB_SRC) $(EXT_SRC) examples/cfg.c
	mkdir -p build/examples
	$(CC) $^ -lpcre2-8 -o $@

.PHONY:
	clean docs install uninstall

