#include "parse.hpp"
#include <iostream>
#include <ctype.h>

using namespace OOPLang;

Parser::Parser(std::istream& in)
	: state(), in(in), stack() {
		in.seekg(0);
		nextc();
	}

Parser::State::State() : c(0), ln(1), cn(0), os(0) {}

Parser &Parser::push() {
	stack.push(state);
	return *this;
}

Parser::State Parser::pop() {
	if (!stack.empty()) {
		State state = stack.top();
		stack.pop();
		return state;
	}
	throw StackUnderflowException();
}

void Parser::restore() {
	state = pop();
	in.seekg(state.os);
}

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
	state.os = in.tellg();
	return state.c = 0;
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
	while(isspace(state.c)) nextc();
	return *this;
}

Parser& Parser::nws() {
	if (isspace(state.c)) {
		throw ParseError();
	}
	nextc();
	return *this;
}


Parser& Parser::mc(char c) {
	sws();
	if (state.c != c) {
		throw ParseError();
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
	if (*s != 0) throw ParseError();
	return *this;
}