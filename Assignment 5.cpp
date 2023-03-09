//************************************************************************** 
//
// Programming Excerise 5  
// CLASS: COSC 2336.S01
// AUTHOR: TYLER ECHOLS 
// DAtE: Nov 2017  
//
//**************************************************************************  

#include <iostream>
#include <string>
#include <string.h>
#include "MathTree.h"
#include "Token.h"

using namespace std;
//geology (chkn) for science class
bool isOperator(string);
bool isDigit(string);

void main()
{
	int intArray[100];
	MathTree tree;
	string kbInput = "";
	string command = "";
	string digitOneInput = "";
	string digitTwoInput = "";
	string operatorInput = "";

	int inputLength = 0;
	int space = 0;
	int digitOne = 0;
	int digitTwo = 0;

	for (int k = 0; k < 100; k++)
	{
		intArray[k] = 0;
	}


	cout << "Please enter one of the following commands: " << endl;
	cout << "C# - C followed by a whole number (up to 3 digits with a possible minus sign) will insert the number into the tree as a constant " << endl;
	cout << "V## - V followed by two digits (00 through 99) will cause a variable to be placed in the tree" << endl;
	cout << "v## # - v followed by two digits (which variable), a space, and up to three digits with possible minus sign (value) will set that variable to that value" << endl;
	cout << "O+# - O followed by an operator ('+', '-', '*', '/') followed by a single digit number inserts the operator into the tree with the variable representing the precedence, with higher numbers equalling higher precedence" << endl;
	cout << "E - evaluates the tree and prints the resulting value" << endl;
	cout << "D - deletes the tree" << endl;
	cout << "X - terminates the program" << endl;

	do
	{
		cout << "Please enter a command: ";
		getline(cin, kbInput);					//reads in user input
		inputLength = kbInput.length();			//gets the length of the user input

		if (inputLength != 0)					//checks if there is any user input
		{
			command = kbInput.at(0);			//gets the first letter of user input to determine the command
		}
		else
		{
			command = "invalid";				//if there is no user input, sets the command to an impossible value
		}

		//command 1, C
		if (command == "C")
		{
			if ((inputLength > 1) && (inputLength < 6)) //check if length is greater than 1 and less than 6
			{
				digitOneInput = kbInput.substr(1); //put the substring after C into digitOneInput; 

				if (digitOneInput.at(0) == '-') //check if there is a negative sign in the space after C
				{
					if (digitOneInput.length() > 1) //making sure that the - isn't the only character
					{
						digitOneInput = digitOneInput.substr(1); //put the substring after the negative into digitOneInput
						if (isDigit(digitOneInput)) //checks if digitOneInput is a valid digit
						{
							digitOne = atoi(digitOneInput.c_str()); //convert the string to an integer and store it in digitOne
							digitOne = digitOne * -1; //multiply digitOne by negative one
							Token token(Token::ConstantToken, digitOne);
							tree.InsertOperand(token); //insert digitOne into the tree. 						  
							cout << "Constant " << token.GetWhich() << " has been added to the tree." << endl;
						}
						else
						{
							cout << "Invalid command" << endl;
						}
					}
					else
					{
						cout << "Invalid input" << endl;
					}
				}
				else //no negative sign //Token token (Token::ConstantToken,  digitOne); 
				{
					if (isDigit(digitOneInput)) //checks if digitOneInput is a valid digit
					{
						if (digitOneInput.length() < 4) //making sure that there are a maximum of 3 digits
						{
							digitOne = atoi(digitOneInput.c_str()); //convert the string to an integer and store it in digitOne
						}
						Token token(Token::ConstantToken, digitOne);
						tree.InsertOperand(token); //insert digitOne into the tree. 						  
						cout << "Constant " << token.GetWhich() << " has been added to the tree." << endl;
					}
					else
					{
						cout << "Invalid command" << endl;
					}
				}
			}
			else
			{
				cout << "Invalid Command" << endl;
			}
		}
		else
		{
			//command 2, V
			if (command == "V")
			{
				if (kbInput.length() == 3)
				{
					digitOneInput = kbInput.substr(1); //put substring after V into digitOneInput
													   //OPTIONAL: check if digitOneInput is a valid variable name, and test with a loop that checks zero through nine for the first number, and zero through nine for the second. If invalid, invalid command
					if (isDigit(digitOneInput)) //checks if digitOneInput is a valid digit
					{
						digitOne = atoi(digitOneInput.c_str());
						Token token(Token::VariableToken, intArray[digitOne]);
						tree.InsertOperand(token); //insert digitOne into the tree. 						  
												   //insert digitOneInput as a variable into the tree. 
						cout << token.GetWhich() << endl;
						cout << "Variable " << digitOneInput << " has been added to the tree." << endl;
					}
					else
					{
						cout << "Invalid command" << endl;
					}
				}
				else
				{
					cout << "Invalid input" << endl;
				}
			}
			else
			{
				//command 3, v
				if (command == "v")
				{
					if ((kbInput.length() > 5) && (kbInput.length() < 9))//length !< 5 and !>9
					{
						if (kbInput.at(3) == ' ') //4th spot is a space
						{
							digitOneInput = kbInput.substr(1, 2);
							digitTwoInput = kbInput.substr(4);
							if (isDigit(digitOneInput))
							{
								if (digitTwoInput.at(0) == '-') //check if there is a negative sign in the space after C
								{
									if (digitTwoInput.length() > 1) //making sure that the - isn't the only character
									{
										digitTwoInput = digitTwoInput.substr(1); //put the substring after the negative into digitTwoInput
										if (isDigit(digitTwoInput))
										{
											digitOne = atoi(digitOneInput.c_str());
											digitTwo = atoi(digitTwoInput.c_str());
											digitTwo = digitTwo * -1;
											intArray[digitOne] = digitTwo;
											cout << "Variable " << digitOne << " has been set to " << digitTwo << endl;
										}
										else
										{
											cout << "Invalid command" << endl;
										}
									}
									else
									{
										cout << "Invalid input" << endl;
									}
								}
								else //no negative sign
								{
									if (isDigit(digitTwoInput))
									{
										if (digitTwoInput.length() < 4) //making sure that there are a maximum of 3 digits
										{
											digitOne = atoi(digitOneInput.c_str());
											digitTwo = atoi(digitTwoInput.c_str());
											intArray[digitOne] = digitTwo;
											cout << "Variable " << digitOne << " has been set to " << digitTwo << endl;
										}

									}
									else
									{
										cout << "Invalid command" << endl;
									}
								}
							}
							else
							{
								cout << "Invalid command" << endl;
							}
						}
					}
					else
					{
						cout << "Invalid input" << endl;
					}
				}
				else
				{
					//command 4, O
					if (command == "O")
					{
						if (kbInput.length() == 3)
						{
							operatorInput = kbInput.at(1);
							if (isOperator(operatorInput)) //check if second char is a valid operator. if not, invalid input
							{
								if (isdigit(kbInput.at(2))) //check if digit is a valid single digit number. if not, invalid input
								{
									if (operatorInput == "+")
									{
										Token token(Token::OperatorPlusToken, (kbInput.at(2)));
										tree.InsertBinaryOperator(token);
										cout << "Operator + with a precedence of " << kbInput.at(2) << " was added to the tree." << endl;
									}
									else
									{
										if (operatorInput == "-")
										{
											Token token(Token::OperatorMinusToken, (kbInput.at(2)));
											tree.InsertBinaryOperator(token);
											cout << "Operator - with a precedence of " << kbInput.at(2) << " was added to the tree." << endl;
										}
										else
										{
											if (operatorInput == "*")
											{
												Token token(Token::OperatorAsteriskToken, (kbInput.at(2)));
												tree.InsertBinaryOperator(token);
												cout << "Operator * with a precedence of " << kbInput.at(2) << " was added to the tree." << endl;
											}
											else
											{
												if (operatorInput == "/")
												{
													Token token(Token::OperatorSlashToken, (kbInput.at(2)));
													tree.InsertBinaryOperator(token);
													cout << "Operator / with a precedence of " << kbInput.at(2) << " was added to the tree." << endl;
												}
											}
										}
									}
									//set the operator precedence
									//place the operator with the proper precedence into the tree. 
								}
								else
								{
									cout << "Invalid input" << endl;
								}
							}
							else
							{
								cout << "Invalid input" << endl;
							}
						}
						else
						{
							cout << "Invalid input" << endl;
						}
					}
					else
					{
						if (command == "E")
						{
							cout << "The evaluated value is " << tree.Evaluate() << endl;
						}
						else
						{
							if (command == "D")
							{
								tree.DeleteTree();
								cout << "The tree has been deleted" << endl;
							}
							else
							{
								if (command == "X")
								{
									cout << "Terminating program..." << endl;
								}
								else
								{
									cout << "Invalid command" << endl;
								}
							}
						}
					}
				}
			}
		}
	} while (command != "X");
}

bool isOperator(string s)
{
	if ((s == "+") || (s == "-") || (s == "*") || (s == "/"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isDigit(string s)
{
	for (int k = 0; k < s.length(); k++) //check if s is a valid integer
	{
		if (!(isdigit(s.at(k))))
		{
			return false;
		}
	}
	return true;
}
