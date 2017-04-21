#include <sstream>
#include <iostream>
#include "parse.hpp"

using namespace OOPLang;

ParseError::ParseError(const Parser *parser)
	: fname(parser->fname), state(parser->state) {}

std::ostream& OOPLang::operator<<(std::ostream& s, const ParseError& error) {
	return s << "Error: " << error.fname << ":" << error.state.ln << ":" << error.state.cn;
}
