CC=g++
CXXFLAGS=-g

TARGET=ooplang


$(TARGET): main.o parse.o
	$(CC) $^ -o $@

main.o: parse.hpp
parse.o: parse.hpp

.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -rf *.o