#include "parse.hpp"

using namespace OOPLang;

Parser::Parser(std::istream& in)
	: state(), in(in) {}

Parser::State::State() : c(0), ln(1), cn(0), os(0) {}

char Parser::nextc() {
	char c;
	if (in.get(c)) {
		if (c != '\r') {
			if (c == '\n') {
				state.ln ++;
				state.cn = 0;
			}
			else  {
				state.cn ++;
			}
			state.c = c;
		}
		return state.c;
	}
	return 0;
}