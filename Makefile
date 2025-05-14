CXX = g++
CC = gcc # gcc is the compiler for C

# Wall is all warnings, Wextra is extra warnings, std=c++11 is the standard library, pedantic is the pedantic mode, Iinclude is the include directory, and pkg-config --cflags glfw3 is the flags for the glfw3 library
# CXXFLAGS = -Wall -Wextra -std=c++14 -pedantic -I./include $(shell pkg-config --cflags glfw3)

CXXFLAGS = -Wall -Wextra -std=c++14 -pedantic \
  -I./include \
  $(shell pkg-config --cflags glfw3) \
  -I$(shell xcrun --show-sdk-path)/usr/include/c++/v1 \
  -I$(shell xcrun --show-sdk-path)/usr/include

CFLAGS = -I./include # -I means include --> look inside the current directory for the include directory
LIBS = $(shell pkg-config --libs glfw3)

TARGET = output
# OBJECTS = src/main.o src/glad.output
OBJECTS = src/main.o src/glad.o

build: $(TARGET)

src/glad.o: src/glad.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

.PHONY: clean
clean: 
	rm -f src/*.o output 

run: 
	./output