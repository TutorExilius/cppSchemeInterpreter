#include "schemeinterpreter.h"

#include "log.h"
#include "node.h"

#include <stack>
#include <sstream>
#include <cmath>

SchemeInterpreter::SchemeInterpreter()
	: root{ nullptr } // create empty root
{
	this->binOperations.insert(
		std::make_pair( "add", []( const double &a, const double &b ){ return a + b; } )
	);

	this->binOperations.insert(
		std::make_pair( "sub", []( const double &a, const double &b ){ return a - b; } )
	);

	this->binOperations.insert(
		std::make_pair( "mult", []( const double &a, const double &b ){ return a * b; } )
	);

	this->binOperations.insert(
		std::make_pair( "diff", []( const double &a, const double &b ){ return a / b; } )
	);

	this->binOperations.insert(
		std::make_pair( "+", []( const double &a, const double &b ){ return a + b; } )
	);

	this->binOperations.insert(
		std::make_pair( "-", []( const double &a, const double &b ){ return a - b; } )
	);

	this->binOperations.insert(
		std::make_pair( "*", []( const double &a, const double &b ){ return a * b; } )
	);

	this->binOperations.insert(
		std::make_pair( "/", []( const double &a, const double &b ){ return a / b; } )
	);

	this->binOperations.insert(
		std::make_pair( "pow", []( const double &a, const double &b ){ return std::pow( a, b ); } )
	);
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

void SchemeInterpreter::calculate( std::shared_ptr<Node> node )
{
	if( node == nullptr )
		return;

	this->calculate( node->left );
	this->calculate( node->right );

	double leftResult = ( node->left != nullptr )
		? node->left->result
		: 0.0;

	double rightResult = ( node->right != nullptr )
		? node->right->result
		: 0.0;

	if( this->binOperations.find( node->operation ) != this->binOperations.end() )
	{
		BinOperation binOperate = this->binOperations[node->operation];
		node->result = binOperate( leftResult, rightResult );
	}

	node->left = nullptr;
	node->right = nullptr;
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

		this->root = std::make_shared<Node>();
		this->buildNode( this->root, scheme, currentParsePos );
	}
	else
	{
		return;
	}
}

void SchemeInterpreter::calculate()
{
	if( this->root == nullptr )
	{
		spdlog::info( "root-nodes is nullptr" );
		return;
	}

	this->calculate( this->root );
}

void SchemeInterpreter::buildNode( std::shared_ptr<Node> root, const char scheme[], int &index )
{
	if( root->left == nullptr )
	{
		root->left = std::make_shared<Node>();
	}

	std::shared_ptr<Node> nextRoot = root->left;
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
					root->right = std::make_shared<Node>();
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
					root->right = std::make_shared<Node>();
				}

				nextRoot = root->right;
			}
		}

		++index;
	}
}

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