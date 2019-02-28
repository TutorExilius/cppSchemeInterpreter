#ifndef NODE_H
#define NODE_H

#include <string>

struct Node
{
	// replace later with std::vector ?
	Node *left = nullptr;
	Node *right = nullptr;

	double result = 0.0;
	std::string operation;
};

#endif // NODE_H
