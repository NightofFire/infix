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
#include <cmath>
#include "Calculator.h"
using namespace std;

/******************************************************************************/
/*                           Function Definitions                             */
/******************************************************************************/
/**
	Calculator() A default constructor for the Calculator class
*/
Calculator::Calculator()
{}
/**
	Calculator() A default constructor for the Calculator class
*/
Calculator::~Calculator()
{}
/**
	precedence(p)  return the precedence of the operator
*/
int Calculator::precedence(char p)
{
	if (p == '+' || p == '-')			//if the operator is '+' or '-', return 1
		return 1;
	else if (p == '*' || p == '/')		//if the operator is '*' or '/', return 2
		return 2;
	else if (p == '^')					//if the operator is '^'		 return 3
		return 3;
	else if (p == '(' || p == ')')		//if the operator is '(' or ')', return 0
		return 0;
}
/**
	execute(&operands, &operators, &result)  evaluate infix expression 
*/
void Calculator::execute(stack<double> & operands, stack<char> &operators, double &result)
{
	double operand1 = 0;				//storage for first operand
	double operand2 = 0;				//storage for first operand
	char operator1;						//storage for operator

	operand2 = operands.top();			//store the first operand
	operands.pop();						//delete it from the stack
	operand1 = operands.top();			//store the second operand
	operands.pop();						//delete it from the stack
	operator1 = operators.top();		//store the operator
	operators.pop();					//delete it from the stack

	if (operator1 == '+')				//if operator is '+', add
	{
		result = operand1 + operand2;
	}
	else if (operator1 == '-')			//if operator is '-', subtract
	{
		result = operand1 - operand2;
	}
	else if (operator1 == '*')			//if operator is '*', multiple
	{
		result = operand1 * operand2;
	}
	else if (operator1 == '/')			//if operator is '/', divide
	{
		result = operand1 / operand2;
	}
	else if (operator1 == '^')			//if operator is '^', raise it to that power
	{
		result = pow(operand1, operand2);
	}
	operands.push(result);				//push the result to the top of the operand stack
}
/**
	precedence(p)  return true/false if input is an operator or not
*/
bool Calculator::isOperator(char op)
{
	//return true if the char is one of these operators
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '(' || op == ')')
		return true;
	//else return false
	else
		return false;
}