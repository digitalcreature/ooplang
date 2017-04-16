#include "parse.hpp"
#include <iostream>
#include <ctype.h>

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
		ms("cats").ms("are").ms("cool");
		std::cout << "matched!" << std::endl;
	}
	catch (ParseError &error) {
		std::cerr << "failed!" << std::endl;
		return;
	}
}

Parser& Parser::sws() {
	try {
		while(isspace(state.c)) nextc();
	}
	catch (UnexpectedEOF &error) {}
	return *this;
}

Parser& Parser::nws() {
	if (isspace(state.c)) {
		fail(new ParseError());
	}
	nextc();
	return *this;
}


Parser& Parser::mc(char c) {
	sws();
	if (state.c != c) {
		fail(new ParseError());
	}
	nextc();
	return *this;
}

Parser& Parser::ms(const char *s) {
	sws();
	while (*s != 0 && *s == state.c) {
		s ++;
		nextc();
	}
	if (*s != 0) fail(new ParseError());
	return *this;
}