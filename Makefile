BUILD_DIR=build
SRC_DIR=src
SOURCES=$(shell find src -name "*.cpp")
TARGETS=$(SOURCES:src/%.cpp=build/%)

.PHONY: all clean run

all: $(TARGETS)

init:
	if [ ! -d "$(BUILD_DIR)" ]; then \
		mkdir $(BUILD_DIR); \
	fi

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp
	g++ -g -std=c++11 -Wall -o $@ $<

clean:
	rm $(BUILD_DIR)/*

run:
	cd $(BUILD_DIR); \
	for f in $$(ls); do \
		echo "running $$f ..."; \
		./$$f; \
	done
