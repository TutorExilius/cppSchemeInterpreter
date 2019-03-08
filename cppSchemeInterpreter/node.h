#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory>

struct Node
{
	// replace later with std::vector ?
	std::shared_ptr<Node> left = nullptr;
	std::shared_ptr<Node> right = nullptr;

	double result = 0.0;
	std::string operation;

	bool hasNoChilds()
	{
		if( this->left == nullptr && this->right == nullptr )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	double operate()
	{
		if( this->operation == "add" )
		{
			return this->left->result + this->right->result;
		}
		else if( this->operation == "mult" )
		{
			return this->left->result * this->right->result;
		}
		else // default		
		{			
			return 0.0;
		}
	}
};

#endif // NODE_H
