CC=g++
CXXFLAGS=-g

TARGET=ooplang


$(TARGET): main.o
	$(CC) $< -o $@

main.o: parse.hpp

.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -rf *.o