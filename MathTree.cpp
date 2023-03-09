//************************************************************************** 
//
// Programming Excerise 5  
// CLASS: COSC 2336.S01
// AUTHOR: TYLER ECHOLS 
// DAtE: Nov 2017  
//
//**************************************************************************  

#include "MathTree.h"

MathTree::Node::Node(const Token & T) : Toke(T)
{
}

MathTree::MathTree()
{
}

MathTree::~MathTree()
{
	DeleteTree();
}

void MathTree::DeleteTree()
{
	if (pRoot.Exists())
	{
		WCS_Pointer <Node>	pNode(GetLeftMostOperator(pRoot));
		WCS_Pointer <Node>	pTemp(GetLeftMostOperator(pRoot));

		while (pNode.Exists())
		{
			if (!(*pNode).LeftSideDone)
			{
				(*pNode).Toke.SetValue((*(*pNode).pLeft).Toke.GetValue());
				(*pNode).LeftSideDone = true;
				pNode = GetLeftMostOperator((*pNode).pRight);
			}
			else
			{
				pTemp = (*pNode).pParent;
				pNode.SetToNull();
			}
			pNode = pTemp;
		}
		cout << (*pRoot).Toke.GetValue() << " has been deleted from the tree." << endl;
	}
	else
	{
		cout << "No tree to delete!" << endl;
	}
}

Variable::ValueType MathTree::Evaluate()
{
	if (pRoot.Exists())
	{
		WCS_Pointer <Node>	pNode(GetLeftMostOperator(pRoot));

		while (pNode.Exists())
			if (!(*pNode).LeftSideDone)
			{
				(*pNode).Toke.SetValue((*(*pNode).pLeft).Toke.GetValue());
				(*pNode).LeftSideDone = true;
				pNode = GetLeftMostOperator((*pNode).pRight);
			}
			else
			{
				switch ((*pNode).Toke.GetType())
				{
				case Token::OperatorPlusToken:
					(*pNode).Toke.SetValue((*pNode).Toke.GetValue() + (*(*pNode).pRight).Toke.GetValue());
					break;
				case Token::OperatorMinusToken:
					(*pNode).Toke.SetValue((*pNode).Toke.GetValue() - (*(*pNode).pRight).Toke.GetValue());
					break;
				case Token::OperatorAsteriskToken:
					(*pNode).Toke.SetValue((*pNode).Toke.GetValue() * (*(*pNode).pRight).Toke.GetValue());
					break;
				case Token::OperatorSlashToken: //CHECK FOR DIVIDE BY ZERO
					(*pNode).Toke.SetValue((*pNode).Toke.GetValue() / (*(*pNode).pRight).Toke.GetValue());
					break;
				}
				pNode = (*pNode).pParent;
			}
		return (*pRoot).Toke.GetValue();
	}
	else
		return 0;
}

WCS_Pointer <MathTree::Node> & MathTree::GetLeftMostOperator(const WCS_Pointer <Node> & pStart)
{
	WCS_Pointer <Node> Ptr(pStart);

	while ((*Ptr).pLeft.Exists())
	{
		(*Ptr).LeftSideDone = false;
		Ptr = (*Ptr).pLeft;
	}
	return (*Ptr).pParent;
}

MathTree::Result MathTree::InsertBinaryOperator(const Token & Toke)
{
	WCS_Pointer <Node>	pNode(new Node(Toke));

	while (pLastOperator && (Toke.GetPrecedence() <= (*pLastOperator).Toke.GetPrecedence()))
		pLastOperator = (*pLastOperator).pParent;
	if (pLastOperator.Exists())
	{
		(*pNode).pLeft = (*pLastOperator).pRight;
		(*pNode).pParent = pLastOperator;
		(*pLastOperator).pRight = pNode;
		(*(*pNode).pRight).pParent = pNode;
	}
	else
	{
		(*pNode).pLeft = pRoot;
		(*pRoot).pParent = pNode;
		pRoot = pNode;
	}
	pLastOperator = pNode;
	return OK;

	/*
	if (pLastOperator.DoesNotExist ())
	{
	(*pRoot).pParent	= pNode;
	(*pNode).pLeft		= pRoot;
	pRoot				= pNode;
	pLastOperator		= pNode;
	return OK;
	}
	else
	{
	if (Toke.GetPrecedence () > (*pLastOperator).Toke.GetPrecedence ())
	{
	(*pNode).pLeft				= (*pLastOperator).pRight;
	(*(*pNode).pLeft).pParent	= pNode;
	(*pLastOperator).pRight		= pNode;
	(*pNode).pParent			= pLastOperator;
	pLastOperator				= pNode;
	return OK;
	}
	else
	{
	while (pLastOperator && (Toke.GetPrecedence () <= (*pLastOperator).Toke.GetPrecedence ()))
	pLastOperator = (*pLastOperator).pParent;
	if (pLastOperator.Exists ())
	{
	(*pNode).pLeft				= (*pLastOperator).pRight;
	(*pNode).pParent			= pLastOperator;
	(*pLastOperator).pRight		= pNode;
	(*(*pNode).pRight).pParent	= pNode;
	}
	else
	{
	(*pNode).pLeft		= pRoot;
	(*pRoot).pParent	= pNode;
	pRoot				= pNode;
	}
	pLastOperator				= pNode;
	}
	}
	*/
}

MathTree::Result MathTree::InsertOperand(const Token & Toke)
{
	WCS_Pointer <Node>	pNode(new Node(Toke));

	if (pRoot.DoesNotExist())
		pRoot = pNode;
	else
	{
		(*pLastOperator).pRight = pNode; //If pLastOperator is not division, and operand is not zero zero. //operator slash token 
		(*pNode).pParent = pLastOperator;
	}
	return OK;
}

MathTree::Result MathTree::InsertUnaryOperator(const Token & Toke)
{
	Token				Temp(Token::ConstantToken, 0);

	InsertOperand(Temp);
	return InsertBinaryOperator(Toke);
}