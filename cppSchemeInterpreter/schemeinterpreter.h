#ifndef SCHEMEINTERPRETER_H
#define SCHEMEINTERPRETER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

#include "node.h"

enum class Child
{
	LEFT, RIGHT
};

class SchemeInterpreter final
{
public:
	using BinOperation = std::function<double(double, double)>;

	SchemeInterpreter();
	SchemeInterpreter( const SchemeInterpreter &obj ) = default;
	SchemeInterpreter& operator=( const SchemeInterpreter &obj ) = default;
	SchemeInterpreter( SchemeInterpreter &&obj ) = default;
	SchemeInterpreter& operator=( SchemeInterpreter &&obj ) = default;
	~SchemeInterpreter() = default;

	bool isValid( const std::string &scheme );

	void parse( const char scheme[] );
	void calculate();

	//void buildTree( std::string &scheme, size_t &index, Node *currentRoot, Node *root );
	void buildNode(std::shared_ptr<Node> root, const char scheme[], int &index );

	double getResult() const;

private:
	void calculate( std::shared_ptr<Node> node );

	std::pair<int, double> extractNumber( const char str[], int &startOffset );
	std::pair<int, std::string> extractOperationString( const char str[], int &startOffset );

	std::unordered_map<std::string,BinOperation> binOperations;
	std::shared_ptr<Node> root;
};

#endif // SCHEMEINTERPRETER_H
