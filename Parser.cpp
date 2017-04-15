#include "parse.hpp"
#include <iostream>

using namespace OOPLang;

Parser::Parser(std::istream& in)
	: state(), in(in) {
		in.seekg(0);
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
		for (;;) {
			char c = nextc();
			if (c == 'e') {
				std::cout << state.ln << ":" << state.cn << std::endl;
			}
		}
	}
	catch (ParseError &error) {
		return;
	}
}