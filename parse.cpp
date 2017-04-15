#include "parse.hpp"

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
	return 0;
}