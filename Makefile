BUILD_DIR=build
SRC_DIR=src

.PHONY: all clean

all: \
	$(BUILD_DIR)/1_1.exe

$(BUILD_DIR)/%.exe: $(SRC_DIR)/%.cpp
	g++ -std=c++11 -Wall -o $@ $<

clean:
	del $(BUILD_DIR)\*.exe
