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

	const char *myscheme{ "(+ 123.45 (+ 333 999))" };
	scheme.parse( myscheme );

	system( "PAUSE" );
	return 0;
}