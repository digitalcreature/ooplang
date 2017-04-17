#pragma once

#include <istream>
#include <stack>
#include <vector>

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

			// stack of previous states
			std::stack<State> stack;
			Parser &push();			// save state on stack
			State pop();				// pop state from stack and return
			void restore();	// pop state from stack and restore parser state from it

			// input file being read from
			std::istream& in;

			// read a character from input
			char nextc();

			// skip whitespace
			Parser &sws();
			// dont skip whitespace (fails if next char is whitespace)
			Parser &nws();

			// match a single character
			Parser &mc(char c);
			// match an arbitrary string
			Parser &ms(const char *s);

			Parser &m_block(std::vector<double>& nums);
			Parser &m_expr(double& n);
			Parser &m_sum(double& n);
			Parser &m_product(double& n);
			Parser &m_atom(double& n);
			Parser &m_number(double& n);

	};

	class ParseError: public std::exception {
		public:
			virtual const char* what();
	};

	class StackUnderflowException: public std::exception {
		public:
			virtual const char* what() {
				return "Parser state stack underflow! Nothing to pop.";
			}
	};

}