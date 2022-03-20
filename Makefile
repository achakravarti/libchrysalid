# Build directory
BUILD_DIR=build

# Generated man pages
MAN_PAGES!=find $(BUILD_DIR) -type f -name \'*.gz\'


# Target to build man pages
man: $(MAN_PAGES)

# Target to clean build directory
clean:
	rm -rfv build/*

# Target to install components
install: $(MAN_PAGES)
	tools/install-man.sh

# Target to uninstall components
uninstall:
	tools/uninstall-man.sh

# Target to build example programs
examples: build/heap


# Rule to build pages
$(MAN_PAGES):
	tools/build-man.sh

# Rule to build heap example program
build/heap:
	gcc -Wall -Wextra -g -fPIC src/heap.c examples/heap.c -o build/heap



# Phony targets
.PHONY:
	clean man install uninstall examples

