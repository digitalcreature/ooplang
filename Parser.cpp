#include "parse.hpp"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <cstdarg>

using namespace OOPLang;

Parser::Parser(std::istream *in, std::string fname)
	: in(in), fname(fname), state(), stack() {
		in->seekg(0);
		nextc();
	}

Parser::Parser(std::string fname)
	: Parser(new std::ifstream(fname), fname) {}

Parser::~Parser() {
	delete in;
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
	in->seekg(state.os);
}

char Parser::nextc() {
	char c;
	while (in->get(c)) {
		if (c != '\r') {
			if (c == '\n') {
				state.ln ++;
				state.cn = 0;
			}
			else  {
				state.cn ++;
			}
			state.c = c;
			state.os = in->tellg();
			return c;
		}
	}
	state.os = in->tellg();
	return state.c = 0;
}

void Parser::parse() {
	try {
		std::vector<double> nums;
		m_block(nums);
		for (const double& n : nums) {
			std::cout << n << std::endl;
		}
	}
	catch (ParseError &error) {
		std::cerr << error << std::endl;
		return;
	}
}

Parser& Parser::sws() {
	while(isspace(state.c)) nextc();
	return *this;
}

Parser& Parser::nws() {
	if (isspace(state.c)) {
		throw ParseError(this);
	}
	nextc();
	return *this;
}

Parser& Parser::mc(char c) {
	sws();
	if (state.c != c) {
		throw ParseError(this);
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
	if (*s != 0) throw ParseError(this);
	return *this;
}

Parser& Parser::ms(const char **v, uint n ...) {
	va_list args;
	va_start(args, n);
	for (int i = 0; i < n; i ++) {
		try {
			const char *s = va_arg(args, const char*);
			push();
			ms(s);
			pop();
			*v = s;
			break;
		}
		catch (ParseError &error)  {
			restore();
		}
	}
	throw ParseError(this);
	va_end(args);
	return *this;
}