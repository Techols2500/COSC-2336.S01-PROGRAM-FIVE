//************************************************************************** 
//
// Programming Excerise 5  
// CLASS: COSC 2336.S01
// AUTHOR: TYLER ECHOLS 
// DAtE: Nov 2017  
//
//**************************************************************************  

#ifndef MATH_TREE_H
#define MATH_TREE_H

#include "WCS_Pointer.h"

#include "Token.h"

class MathTree
{
public:
	enum	Result { OK };
private:
	struct Node : RefCount
	{
		Node(const Token &);
		Token					Toke;
		bool					LeftSideDone;
		WCS_Pointer <Node>		pParent;
		WCS_Pointer <Node>		pLeft;
		WCS_Pointer <Node>		pRight;
	};
public:
	MathTree();
	~MathTree();
	void					DeleteTree();
	Variable::ValueType		Evaluate();
	WCS_Pointer <Node> &	GetLeftMostOperator(const WCS_Pointer <Node> &);
	Result					InsertBinaryOperator(const Token &);
	Result					InsertOperand(const Token &);
	Result					InsertUnaryOperator(const Token &);
private:
	MathTree(const MathTree &);
	MathTree &	operator =	(const MathTree &);

	WCS_Pointer <Node>			pRoot;
	WCS_Pointer <Node>			pLastOperator;
};

#endif