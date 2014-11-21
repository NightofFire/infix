#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include "Calculator.h"
using namespace std;

int main(int argc, char* argv[])
{
	ifstream file;
	if (argc > 1 && argc < 3)
	{
		file.open(argv[1]);
		if (!file.is_open())
		{
			exit(1);
			cerr << "Invalid file" << endl;
		}
		cout << "1" << endl;
	}
	Calculator calculator;
	string line;
	while (true)
	{
		cout << "Enter an expression" << endl;
		if (argc > 1 && getline(file,line))
		{
		}
		else
		{
			getline(cin, line);
		}
		string expression;
		stringstream ss;
		string temp;
		ss << line;
		while (ss >> temp)
		{
			expression += temp;
		}
		cout << expression << endl;
		if (line == "")
		{
			continue;
		}
		stack<double> operands;
		stack<char> operators;
		double result;
		bool skip = false;
		int parenCounter = 0;
		
		//getline(cin, line);

		//cout << expression << endl;

		for (int i = 0; i < expression.length(); i++)
		{
			if (isdigit(expression[i]))
			{
				int startPos = i;
				while (i != expression.length() && !calculator.isOperator(expression[i]))
				{
					//cout << expression[i] << endl;
					i++;
				}
				int endPos = i;
				int length = endPos - startPos;
				string temp = expression.substr(startPos, length);
				//cout << temp << endl;
				double value = stod(temp);
				operands.push(value);
				i--;
				//cout << "value : "<< value << endl;
				/*istringstream convert(expression[i]);
				double temp;
				convert >> temp;
				cout << temp << endl;
				operands.push(temp);*/
			}
			else if (isalpha(expression[i]))
			{
				skip = true;
				break;
			}
			else
			{
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
				/*if (parenCounter<0 || parenCounter>0)
				{
					cout << "error" << endl;
					exit(1);
				}*/
				cout << "ENTERED" << endl;
				//cout << expression[i] << endl;
				switch (expression[i])
				{
				case '(':
					operators.push(expression[i]);
					cout << expression[i] << endl;
					break;
				case '+': case '-': case '*': case '/': case '^':
					if (operators.empty())
					{
						cout << expression[i] << endl;
						operators.push(expression[i]);
					}
					else if (calculator.precedence(expression[i]) >= calculator.precedence(operators.top()))
					{
						//cout << "+" << endl;
						cout << "2 " << expression[i] << endl;
						operators.push(expression[i]);
						//cout << "+1" << endl;
					}
					else
					{
						cout << "3 " << expression[i] << endl;
						while (!operators.empty() && calculator.precedence(expression[i]) <= calculator.precedence(operators.top()))
						{
							calculator.execute(operands, operators, result);
						}
						operators.push(expression[1]);
					}
					break;
				case ')':
					cout << ")" << endl;
					if (operators.top() == '(')
					{
						skip = true;
					}
					else
					{
						while (operators.top() != '(')
						{
							calculator.execute(operands, operators, result);
						}
						operators.pop();
					}
					break;

				default:
					cerr << "ERROR" << endl;
					break;
				}
			}
		}
		if (!skip && parenCounter == 0)
		{
			while (!operators.empty())
			{
				cout << "popping" << endl;
				cout << operators.top() << endl;
				calculator.execute(operands, operators, result);
				cout << "finish popping" << endl;
			}
			result = operands.top();
			//cout << operands.top() << endl;
			//cout << operators.top() << endl;
			//execute(operands, operators, result);
			//execute(operands, operators, result);
			cout << "The result is " << setprecision(4) << result << " = " << line << endl;
		}
	}
	return 0;
}