#pragma once

#include <istream>

namespace OOPLang {

	typedef unsigned int uint;

	class Parser {
		public:
			Parser(std::istream& in);
			char nextc();				// read a character from input
		private:
			struct State {
				State();
				char c;					// last character read
				uint ln;					// line number
				uint cn;					// column number
				std::streampos os;	// file offset
			} state;
			std::istream& in;
	};

}