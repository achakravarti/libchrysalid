# Build directory
BUILD_DIR=build


#################################################################################
# MAN PAGE TARGETS
#################################################################################

MAN_SRC!=find docs/components -type f -name '*.m4'
MAN_BIN=$(MAN_SRC:%.m4=$(BUILD_DIR)/%.7.gz)

.PHONY: man
man: $(MAN_BIN)

$(MAN_BIN):
	tools/build-man.sh


#################################################################################
# EXAMPLE TARGETS
#################################################################################

.PHONY: examples
examples: build/heap

build/heap:
	gcc -Wall -Wextra -g -fPIC src/heap.c examples/heap.c -o build/heap


#################################################################################
# (UN)INSTALL TARGETS
#################################################################################

.PHONY: install
install: $(MAN_BIN)
	tools/install-man.sh

.PHONY: uninstall
uninstall:
	tools/uninstall-man.sh


#################################################################################

# CLEAN TARGETS
#################################################################################

.PHONY: clean
clean:
	rm -rfv build/*

