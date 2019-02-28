#include "schemeinterpreter.h"

#include "log.h"
#include "node.h"

#include <stack>
#include <sstream>

SchemeInterpreter::SchemeInterpreter()
: root{ nullptr } // create empty root
{
}

bool SchemeInterpreter::isValid( const std::string & scheme )
{
	if( scheme.size() > 0 && scheme.find( '(' ) == std::string::npos )
	{
		return false;
	}

	std::stack<int> myStack;

	for( const auto &ch : scheme )
	{
		if( ch == '(' )
		{
			myStack.push( 1 );
		}
		else if( ch == ')' )
		{
			if( myStack.empty() )
				return false;

			myStack.pop();
		}
	}

	return myStack.empty();
}

void SchemeInterpreter::parse( const char scheme[] )
{
	if( !this->isValid( std::string{ scheme } ) )
	{
		spdlog::error( "Invalid scheme: {}", scheme );
		return;
	}

	if( scheme[0] == '(' )
	{
		int currentParsePos = 1;

		this->root = new Node;
		this->buildNode( this->root, scheme, currentParsePos );
	}
	else
	{
		return;
	}
	//size_t index = 0;
	//this->buildTree( scheme, index, this->root, this->root );

	/*
	bool left = true;

	Node *currentRoot = this->root;

	for( size_t i{ 0 }; i<scheme.size(); ++i )
	{
		const char &ch{ scheme[i] };

		if( ::isdigit( ch ) )
		{
			double number = 0.0;
			std::tie(i,number) = this->extractNumber( scheme.c_str(), i );

			if( left )
			{
				left = false;

				this->root->left = new Node{ nullptr, nullptr, number, "" };
			}
			else
			{
				this->root->right = new Node{ nullptr, nullptr, number, "" };
			}
		}
		else if( ch == '(' || ch == ')' )
		{

		}
		else if( not::isspace( ch ) )
		{
			std::string operation;

			std::tie( i, operation ) = this->extractOperationString( scheme.c_str(), i );

			this->root->operation = operation;
		}
	}
	*/
}

void SchemeInterpreter::buildNode( Node *root, const char scheme[], int &index )
{
	if( root->left == nullptr )
	{
		root->left = new Node;
	}

	Node *nextRoot = root->left;
	Child nextChildRoot_trigger = Child::LEFT;

	char ch;

	const std::string tmp{ scheme };

	while( index < tmp.size() )
	{
		ch = scheme[index];

		if( not::isdigit( ch ) && not::isspace( ch ) && ch != '(' && ch != ')' )
		{
			std::string operation;
			std::tie( index, operation ) = this->extractOperationString( scheme, index );
			root->operation = operation;
		}
		else if( ch == ')' )
		{
			return;
		}
		else if( ::isdigit( ch ) )
		{
			double number = 0.0;
			std::tie( index, number ) = this->extractNumber( scheme, index );

			if( nextChildRoot_trigger == Child::LEFT )
			{
				nextChildRoot_trigger = Child::RIGHT;

				root->left->result = number;

				if( root->right == nullptr )
				{
					root->right = new Node;
				}

				nextRoot = root->right;
			}
			else
			{
				root->right->result = number;
			}
		}
		else if( ch == '(' )
		{
			this->buildNode( nextRoot, scheme, ++index );

			if( nextChildRoot_trigger == Child::LEFT )
			{
				nextChildRoot_trigger = Child::RIGHT;

				if( root->right == nullptr )
				{
					root->right = new Node;
				}

				nextRoot = root->right;
			}
		}
			
		++index;
	}	
}

/*
void SchemeInterpreter::buildTree( std::string &scheme,
								   size_t &index, 
								   Node *currentRoot,
								   Node *root )
{
	bool left = true;

	const size_t strSize{ scheme.size() };

	double rootResult = 0.0;

	for( ; index < strSize; ++index )
	{
		const char &ch{ scheme[index] };

		if( ::isdigit( ch ) )
		{
			double number = 0.0;
			std::tie( index, number ) = this->extractNumber( scheme.c_str(), index );

			if( left )
			{
				left = false;
			}

			rootResult = number;
		}
		else if( ch == '(' )
		{
			currentRoot->left = new Node{ nullptr, nullptr, 0.0, "" };
			currentRoot->right = new Node{ nullptr, nullptr, 0.0, "" };

			Node *whichChild = nullptr;
			
			if( left )
			{
				currentRoot->left->result = rootResult;
				whichChild = currentRoot->left;
			}
			else
			{
				currentRoot->right->result = rootResult;
				whichChild = currentRoot->right;
			}

			this->buildTree( scheme, ++index, whichChild, currentRoot );
		}
		else if( not::isspace( ch ) )
		{
			std::string operation;

			std::tie( index, operation ) = this->extractOperationString( scheme.c_str(), index );

			root->operation = operation;
		}
	}
}
*/

std::pair<int, std::string> SchemeInterpreter::extractOperationString( const char str[], 
																	   int &startOffset )
{
	std::stringstream operationStream;

	int lastNonSpaceCharPos{ startOffset };

	char ch = '\0';
	int i{ startOffset };

	while( ( ch = str[i] ) != '\0' )
	{
		if( !::isspace( ch ) )
		{
			lastNonSpaceCharPos = i;
			operationStream << ch;
		}
		else
		{
			break;
		}

		++i;
	}

	return std::make_pair( lastNonSpaceCharPos, operationStream.str() );
}

std::pair<int, double> SchemeInterpreter::extractNumber( const char str[], 
														 int &startOffset )
{
	std::stringstream numberStream;

	int lastDigitPos{ startOffset };

	char ch = '\0';
	int i{ startOffset };

	while( ( ch = str[i] ) != '\0' )
	{
		if( ::isdigit( ch ) || ch == '.' )
		{
			lastDigitPos = i;
			numberStream << ch;
		}
		else
		{
			break;
		}

		++i;
	}

	double number = 0.0;
	numberStream >> number;

	return std::make_pair( lastDigitPos, number );
}

double SchemeInterpreter::getResult() const
{
	return this->root->result;
}

double SchemeInterpreter::add( double a, double b )
{
	return a + b;
}

double SchemeInterpreter::sub( double a, double b )
{
	return a - b;
}

double SchemeInterpreter::mult( double a, double b )
{
	return a * b;
}

double SchemeInterpreter::div( double a, double b )
{
	return a / b;
}
