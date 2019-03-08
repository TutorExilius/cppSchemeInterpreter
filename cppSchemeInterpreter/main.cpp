#include <stack>
#include <iostream>
#include <string>
using namespace std;

#include "log.h"
#include "schemeinterpreter.h"

int main()
{
	init_log( "logs/log.txt" );

	SchemeInterpreter scheme;

	const char *myscheme{ "(pow (* 3 1) (+ 1 1))" };
	scheme.parse( myscheme );
	scheme.calculate();

	std::cout << "Result:" << scheme.getResult() << std::endl;

	system( "PAUSE" );
	return 0;
}