#include<iostream>
#include<string>
#include"Stack.h"
using namespace std;

int main()
{
	string expression;
	cout << "Enter a expression (without any space) : " << endl;
	getline(cin, expression);

	while (!validate_expression(expression))
	{
		cout << "INVALID. Please try again." << endl;
		cout << "Enter a expression (without any space) : " << endl;
		getline(cin, expression);
	}

	string postfix = infix_to_postfix(expression);
	cout << "Postfix expression is: " << postfix << endl;
	int answer = evaluate_postfix(postfix);

	if (answer != -32768)
	{
		cout << "Final Answer is: " << answer << endl;
	}
	return 0;
}