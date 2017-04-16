#include "parse.hpp"
#include <iostream>

using namespace OOPLang;

Parser::Parser(std::istream& in)
	: state(), in(in) {
		in.seekg(0);
		nextc();
	}

Parser::State::State() : c(0), ln(1), cn(0), os(0) {}

char Parser::nextc() {
	char c;
	while (in.get(c)) {
		if (c != '\r') {
			if (c == '\n') {
				state.ln ++;
				state.cn = 0;
			}
			else  {
				state.cn ++;
			}
			state.c = c;
			state.os = in.tellg();
			return c;
		}
	}
	fail(new UnexpectedEOF());
}

void Parser::fail(ParseError *error) {
	throw *error;
}

void Parser::parse() {
	try {
		ms("cat");
		std::cout << "matched cat!" << std::endl;
	}
	catch (ParseError &error) {
		std::cerr << "failed to match cat!" << std::endl;
		return;
	}
}


Parser& Parser::mc(char c) {
	if (state.c != c) {
		fail(new ParseError());
	}
	nextc();
	return *this;
}

Parser& Parser::ms(const char *s) {
	while (*s != 0 && *s == state.c) {
		s ++;
		nextc();
	}
	if (*s != 0) fail(new ParseError());
	return *this;
}