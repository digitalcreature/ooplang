CC=g++
CXXFLAGS=-g

TARGET=ooplang


$(TARGET): main.o Parser.o ParseError.o
	$(CC) $^ -o $@

main.o: parse.hpp
Parser.o: parse.hpp
ParseError.o: parse.hpp

.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -rf *.o