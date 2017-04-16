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

			// parse
			void parse();
			
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

			// read a character from input
			char nextc();

			// skip whitespace
			Parser &sws();
			// dont skip whitespace (fails if next char is whitespace)
			Parser &nws();

			// match a single character
			Parser &mc(char c);
			// match a string
			Parser &ms(const char *s);

	};

	class ParseError: public std::exception {
		public:
			virtual const char* what();
	};

	class UnexpectedEOF: public ParseError {
		public:
			virtual const char* what();
	};

}