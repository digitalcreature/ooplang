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
		ifstream file(argv[1]);
		if (file) {
			Parser parser(file);
			parser.parse();
			// do parser things
			file.close();
			return 0;
		}
		else {
			cerr << "could not open file" << endl;
			return 1;
		}
	}
}