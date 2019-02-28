#ifndef SCHEMEINTERPRETER_H
#define SCHEMEINTERPRETER_H

#include <string>

// forward-declarations
struct Node;

enum class Child
{
	LEFT, RIGHT
};

class SchemeInterpreter final
{
public:
	SchemeInterpreter();
	SchemeInterpreter( const SchemeInterpreter &obj ) = default;
	SchemeInterpreter& operator=( const SchemeInterpreter &obj ) = default;
	SchemeInterpreter( SchemeInterpreter &&obj ) = default;
	SchemeInterpreter& operator=( SchemeInterpreter &&obj ) = default;
	~SchemeInterpreter() = default;

	bool isValid( const std::string &scheme );

	void parse( const char scheme[] );
	//void buildTree( std::string &scheme, size_t &index, Node *currentRoot, Node *root );
	void buildNode( Node *root, const char scheme[], int &index );

	double getResult() const;

	// supported operations
	double add( double a, double b ); //   +
	double sub( double a, double b ); //   -
	double mult( double a, double b ); //   *
	double div( double a, double b ); //   /

private:
	std::pair<int, double> extractNumber( const char str[], int &startOffset );
	std::pair<int, std::string> extractOperationString( const char str[], int &startOffset );

	Node *root;
};

#endif // SCHEMEINTERPRETER_H
