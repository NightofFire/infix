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

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <iostream>
#include <stack>
using namespace std;

class Calculator{
private:
public:
	/******************************************************************************/
	/*                           Function Prototypes                              */
	/******************************************************************************/
	Calculator();			//default constructor
	~Calculator();			//default destructor
	/**
	*  precedence(char)  return the precendence of the operator
	*  @param    char		[in]	array of strings to be filled
	*  @pre      none
	*  @post     returns an int
	*  @return   int
	*/
	int precedence(char);
	/**
	*  execute(stack<double> &, stack<char> &, double &)  evaluate the infix expression
	*  @param    stack<double>		[in/out]	stack of operands
	*  @param    stack<double>		[in/out]	stack of operators
	*  @param    double				[in/out]	result of evaluation
	*  @pre      stack<double> and stack<char> are not empty and valid. double is valid
	*  @post     evaulation stored in double
	*  @return   void
	*/
	void execute(stack<double> &, stack<char> &, double &);
	/**
	*  isOperator(char)  return true/false if input is an operator or not
	*  @param    char		[in]	char of operator
	*  @pre      valid char input
	*  @post     return		true/false
	*  @return   bool
	*/
	bool isOperator(char);
};

#endif