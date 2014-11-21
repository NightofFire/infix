#include <iostream>
#include "Calculator.h"
using namespace std;

Calculator::Calculator()
{}
Calculator::~Calculator()
{}
int Calculator::precedence(char p)
{
	if (p == '+' || p == '-')
		return 1;
	else if (p == '*' || p == '/')
		return 2;
	else if (p == '^')
		return 3;
	else if (p == '(' || p == ')')
		return 0;
}
void Calculator::execute(stack<double> & operands, stack<char> &operators, double &result)
{
	double operand1 = 0;
	double operand2 = 0;
	char operator1;

	operand2 = operands.top();
	operands.pop();
	operand1 = operands.top();
	operands.pop();
	operator1 = operators.top();
	operators.pop();
	//cout << operator1 << endl;
	if (operator1 == '+')
	{
		cout << operand1 << " + " << operand2 << endl;
		result = operand1 + operand2;
	}
	else if (operator1 == '-')
	{
		cout << operand1 << " - " << operand2 << endl;
		result = operand1 - operand2;
	}
	else if (operator1 == '*')
	{
		cout << operand1 << " * " << operand2 << endl;
		result = operand1 * operand2;
	}
	else if (operator1 == '/')
	{
		cout << operand1 << " / " << operand2 << endl;
		result = operand1 / operand2;
	}
	else
	{
		cout << operand1 << " ^ " << operand2 << endl;
		result = pow(operand1, operand2);
	}
	operands.push(result);
	cout << "finish execute " << endl;
}
bool Calculator::isOperator(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '(' || op == ')')
		return true;
	else
		return false;
}