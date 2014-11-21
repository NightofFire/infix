/*******************************************************************************
Title          : cp395_hwk3.cpp
Author         : Cheng Pan
Created on     : November 20, 2014
Description    : Infix expression evaluation using 2 stacks
Purpose        : Practice with stacks and input text processing
Usage          : ./hw3_cp395 file.txt
Build with     : g++ -o hw3_cp395 hwk3_cp395.cpp Calculator.cpp
Modifications  :
*******************************************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include "Calculator.h"
using namespace std;

int main(int argc, char* argv[])
{
	ifstream file;
	//if there's a commandline argument, open it
	if (argc > 1 && argc < 3)
	{
		file.open(argv[1]);
		if (!file.is_open())		//check if the file opened or not
		{
			exit(1);
			cerr << "Invalid file" << endl;
		}
	}
	Calculator calculator;			//initialize Calculator class
	string line;					//string storage for infix expression
	while (true)
	{
		if (argc > 1 && getline(file,line))
		{
		}
		else
		{
			cout << "Enter an expression" << endl;
			getline(cin, line);
			if (cin.eof())
			{
				exit(0);
			}
		}
		string expression;			//infix expression without spaces
		stringstream ss;			//stringstream to erase the spaces
		string temp;				//temp storage for each word
		ss << line;
		while (ss >> temp)
		{
			expression += temp;
		}
		if (line == "")				//input cannot be empty
		{
			continue;
		}
		stack<double> operands;		//stack for operands
		stack<char> operators;		//stack for operators
		double result;				//store result in double
		bool skip = false;			
		int parenCounter = 0;		//counter for parentheses

		//loop to parse the input
		for (int i = 0; i < expression.length(); i++)
		{
			//use substr to get line number from string
			if (isdigit(expression[i]))
			{
				int startPos = i;					//starting position of substr
				while (i != expression.length() && !calculator.isOperator(expression[i]))
				{
					i++;
				}
				int endPos = i;						//end position
				int length = endPos - startPos;		//length of substr
				string temp = expression.substr(startPos, length);
				//use istringstream to convert string to double
				istringstream iss(temp);
				double value;
				iss >> value;
				operands.push(value);
				i--;
			}
			else if (isalpha(expression[i]))		//if input contains letters, skip it
			{
				skip = true;
				break;
			}
			else
			{
				//counts the parentheses
				if (expression[i] == '(')
				{
					parenCounter++;
				}
				else if (expression[i] == ')')
				{
					parenCounter--;
					if (parenCounter < 0)
					{
						break;
					}
				}
				//switch statement to check the operators
				switch (expression[i])
				{
				case '(':
					operators.push(expression[i]);
					break;
				case '+': case '-': case '*': case '/': case '^':
					if (operators.empty())
					{
						//push to stack if stack is empty
						operators.push(expression[i]);
					}
					else if (calculator.precedence(expression[i]) >= calculator.precedence(operators.top()))
					{
						//if expression[i] have a higher or equal precendence to operator on top of the stack, push
						operators.push(expression[i]);
					}
					else
					{
						//if xpression[i] have a lower precendence than the operator on top of the stack
						while (!operators.empty() && calculator.precedence(expression[i]) <= calculator.precedence(operators.top()))
						{
							//evaluate the expression
							calculator.execute(operands, operators, result);
						}
						//push the operator
						operators.push(expression[1]);
					}
					break;
				case ')':
					if (operators.top() == '(')
					{
						//skip if "()" appears
						skip = true;
					}
					else
					{
						//evaluate until it reaches the left parentheses
						while (operators.top() != '(')
						{
							calculator.execute(operands, operators, result);
						}
						//pop the left parentheses
						operators.pop();
					}
					break;

				default:
					skip = true;
					break;
				}
			}
		}
		//evaluate the rest of the expression
		if (!skip && parenCounter == 0)
		{
			while (!operators.empty())
			{
				calculator.execute(operands, operators, result);
			}
			result = operands.top();
			//output the result
			cout << fixed << setprecision(3) << result << " = " << line << endl;
		}
	}
	return 0;
}