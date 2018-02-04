BUILD_DIR=build
SRC_DIR=src

.PHONY: all clean run

all: \
	$(BUILD_DIR)/1_1 \
	$(BUILD_DIR)/1_2 \
	$(BUILD_DIR)/1_3 \
	$(BUILD_DIR)/1_4

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		mkdir $(BUILD_DIR); \
	fi; \
	g++ -g -std=c++11 -Wall -o $@ $<

clean:
	rm $(BUILD_DIR)/*

run:
	@cd $(BUILD_DIR); \
	for f in $$(ls); do \
		echo "running $$f ..."; \
		./$$f; \
	done
