CC=g++
CXXFLAGS=-g -std=c++11

TARGET=ooplang


$(TARGET): main.o Parser.o ParseError.o Parser_rules.o
	$(CC) $^ -o $@

main.o: parse.hpp
Parser.o: parse.hpp
Parser_rules.o: parse.hpp
ParseError.o: parse.hpp

.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -rf *.o