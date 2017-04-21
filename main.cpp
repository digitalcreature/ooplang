#include "parse.hpp"
#include <iostream>
#include <fstream>

using namespace OOPLang;
using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cerr << "No input file given." << endl;
		cerr << "Usage:" << endl;
		cerr << " $ " << argv[0] << " file" << endl;
		return 1;
	}
	else {
		Parser parser(argv[1]);
		parser.parse();
		// do parser things
		return 0;
	}
}