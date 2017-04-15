#pragma once

#include <istream>

namespace OOPLang {

	typedef unsigned int uint;

	class Parser;					// parser parses a single file
	class ParseError;				// base class for parsing errors

	class Parser {

		public:

			// constructor
			Parser(std::istream& in);
			
			// read a character from input
			char nextc();
			
		private:
			
			// state of parsing automota
			struct State {
				State();
				char c;					// last character read
				uint ln;					// line number
				uint cn;					// column number
				std::streampos os;	// file offset
			} state;

			// input file being read from
			std::istream& in;
			
			// fail parsing, throw exception
			void fail(ParseError *error);

	};

	class ParseError: public std::exception {
	
		public:
			virtual const char* what();

	};

}