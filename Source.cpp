#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include <cmath>
#include <sstream>
#include <iomanip> 
using namespace std;

int precedence(char p)
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
void execute(stack<double> & operands, stack<char> &operators, double &result)
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
int main()
{
	if (isdigit('a'))
		cout << "dsadas" << endl;
	stack<double> operands;
	stack<char> operators;
	double result;
	string line;
	string temp;
	string hey;
	char exp[100];
	cout << "Enter an expression" << endl;
	getline(cin, line);
	stringstream ss;
	ss << line;
	while (ss >> temp)
	{
		hey += temp;
	}
	//cout << hey << endl;

	for (int i = 0; i < hey.length(); i++)
	{
		if (isdigit(hey[i]))
		{
			int startPos = i;
			while (i != hey.length() && hey[i] != '+' && hey[i] != '-' && hey[i] != '*' && hey[i] != '/' && hey[i] != '^')
			{
				//cout << hey[i] << endl;
				i++;
			}
			int endPos = i;
			int length = endPos - startPos;
			string temp = hey.substr(startPos, length);
			//cout << temp << endl;
			double value = stod(temp);
			operands.push(value);
			i--;
			//cout << "value : "<< value << endl;
			/*istringstream convert(hey[i]);
			double temp;
			convert >> temp;
			cout << temp << endl;
			operands.push(temp);*/
		}
		else
		{
			cout << "ENTERED" << endl;
			//cout << hey[i] << endl;
			switch (hey[i])
			{
			case '(':
				operators.push(hey[i]);
				cout << hey[i] << endl;
				break;
			case '+': case '-': case '*': case '/': case '^':
				if (operators.empty())
				{
					cout << hey[i] << endl;
					operators.push(hey[i]);
				}
				else if (precedence(hey[i]) >= precedence(operators.top()))
				{
					//cout << "+" << endl;
					cout << "2 " << hey[i] << endl;
					operators.push(hey[i]);
					//cout << "+1" << endl;
				}
				else
				{
					cout << "3 " << hey[i] << endl;
					while (!operators.empty() && precedence(hey[i]) <= precedence(operators.top()))
					{
						execute(operands, operators, result);
					}
					operators.push(hey[1]);
				}
				break;
			case ')':
				cout << ")" << endl;
				while (operators.top() != '(')
				{
					execute(operands, operators, result);
				}
				operators.pop();
				break;

			default:
				cerr << "ERROR" << endl;
				break;
			}
		}
	}
	while (!operators.empty())
	{
		cout << "popping" << endl;
		cout << operators.top() << endl;
		execute(operands, operators, result);
		//operators.pop();
		cout << "finish popping" << endl;
	}
	result = operands.top();
	//cout << operands.top() << endl;
	//cout << operators.top() << endl;
	//execute(operands, operators, result);
	//execute(operands, operators, result);
	cout << "The result is " << setprecision(2) << result << endl;


	return 0;
}