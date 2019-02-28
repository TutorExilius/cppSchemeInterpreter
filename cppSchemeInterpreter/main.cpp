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

	const char *myscheme{ "(mult 111 (add 123.45 99) )" };
	scheme.parse( myscheme );

	system( "PAUSE" );
	return 0;
}