#include <iostream>
#include "Parser.h"


using namespace std;

Parser parser;

int main() {

	try {
		cout << parser.calculate("5+545665566") << endl;
	}
	

	catch (char error[]) {
		cout << error << endl;
	}





	return 0;
}