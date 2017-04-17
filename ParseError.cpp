#include "parse.hpp"

using namespace OOPLang;

const char *ParseError::what() {
	return "Parse error";
}
