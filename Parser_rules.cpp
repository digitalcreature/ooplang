#include "parse.hpp"
#include <ctype.h>

using namespace OOPLang;

Parser &Parser::m_block(std::vector<double>& nums) {
	double n;
	for (;;) {
		try {
			m_expr(n);
			nums.push_back(n);
		}
		catch (ParseError& e) {
			if (state.c == 0) {
				return *this;
			}
			else {
				throw;
			}
		}
	}
}

Parser &Parser::m_expr(double &n) {
	return m_sum(n);
}

Parser &Parser::m_sum(double &n) {
	m_product(n);
	double m;
	for (;;) {
		try {
			push().ms("+").m_product(m).pop();
			n += m;
		}
		catch (ParseError& e) {
			try {
				restore();
				push().ms("-").m_product(m).pop();
				n -= m;
			}
			catch (ParseError& e) {
				restore();
				break;
			}
		}
	}
	return *this;
}

Parser &Parser::m_product(double &n) {
	m_atom(n);
	double m;
	for (;;) {
		try {
			push().ms("*").m_atom(m).pop();
			n *= m;
		}
		catch (ParseError& e) {
			try {
				restore();
				push().ms("/").m_atom(m).pop();
				n /= m;
			}
			catch (ParseError& e) {
				restore();
				break;
			}
		}
	}
	return *this;
}

Parser &Parser::m_atom(double &n) {
	try {
		push().ms("(").m_expr(n).ms(")").pop();
	}
	catch (ParseError& e) {
		restore();
		m_number(n);
	}
	return *this;
}

Parser &Parser::m_number(double &n) {
	sws();
	if (isdigit(state.c)) {
		n = 0;
		while(isdigit(state.c)) {
			n *= 10;
			n += state.c - '0';
			nextc();
		}
		return *this;
	}
	else {
		throw ParseError(this);
	}
}