#include <iostream>
#include <stack>
using namespace std;

class Calculator{
private:
public:
	Calculator();
	~Calculator();
	int precedence(char);
	void execute(stack<double> &, stack<char> &, double &);
	bool isOperator(char);
};