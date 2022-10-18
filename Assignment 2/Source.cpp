#include<iostream>
#include<string>
#include"Stack.h"
using namespace std;

bool Is_operator(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == '^')
	{
		return true;
	}
	return false;
}

bool Is_operand(char operand)
{
	if (operand >= 'A' && operand <= 'Z' || operand >= 'a' && operand <= 'z' || operand >= '0' && operand <= '9')
	{
		return true;
	}
	return false;
}

//char round_brackets[2] = { '(',')' };
//char square_brackets[2] = { '[',']' };
//char curly_brackets[2] = { '{','}' };

bool Opening_bracket(char bracket)
{
	if (bracket == '(' || bracket == '[' || bracket == '{')
	{
		return true;
	}
	return false;
}

bool Closing_bracket(char bracket)
{
	if (bracket == ')' || bracket == ']' || bracket == '}')
	{
		return true;
	}
	return false;
}

char match_bracket(char close_bracket)
{
	if (close_bracket == ')')
	{
		return '(';
	}
	else if (close_bracket == ']')
	{
		return '[';
	}
	else if (close_bracket == '}')
	{
		return '{';
	}
}

bool validate_expression(string exp)
{
	if (Is_operator(exp[exp.length() - 1])) //if there is an operator at the end of string
	{
		return false;
	}

	Stack stack;
	for (int i = 0; i < exp.length(); i++)
	{
		if (!(Is_operator(exp[i]) || Is_operand(exp[i]) || Opening_bracket(exp[i]) || Closing_bracket(exp[i])))
		{
			return false;   //means it is some specal character
		}
		else if (Opening_bracket(exp[i]))  
		{
			if (i != exp.length() - 1) //means if it is not the last character
			{
				if (Is_operator(exp[i + 1]) || Closing_bracket(exp[i + 1])) //if it is like (+ OR
				{
					return false; //if there is a closing bracket immediately after a opening bracket
				}
				else if (!(Is_operator(exp[i + 1]))) //CAN IT BE WRITTEN AS ONLY ELSE INSTEAD OF ELSE IF?
				{
					stack.push(exp[i]);
				}
			}
			else if (i != 0 && !(Closing_bracket(exp[i - 1]))) //if it is not the first character and 
			{
				return false;     // there is a closing bracket immediately before the opening bracket
			}
			else //if last character is opening bracket
			{
				return false;
			}
		}
		else if (Is_operator(exp[i])) //2 operators can't come together
		{
			if (i != 0 && i != exp.length() - 1) //it is neither first nor last character
			{
				if (Is_operator(exp[i - 1]) || Is_operator(exp[i + 1]))
				{
					return  false;
				}
			}
			else if (i == 0 || i == exp.length() - 1) //if there is an operator at first or last position
			{
				return false;  
			}
		}
		else if (Closing_bracket(exp[i])) 
		{
			if (i != 0) //closing bracket is not the first character
			{
				if (Is_operator(exp[i - 1]) || Opening_bracket(exp[i - 1]))  //if it is like +)  OR
				{
					return false;	// if there is a opening bracket immediately before a closing bracket
				}
				else if (i!=exp.length()-1 && Opening_bracket(exp[i + 1])) //if it is not the last character
				{
					return false;  //and there is an opening bracket immediately after a closing bracket
				}
				else if (!(Is_operator(exp[i - 1])))
				{
					if (stack.peek() == match_bracket(exp[i])) //if top bracket at stack is matched with closing one
					{
						stack.pop();
					}
					//else if (stack.pop() == '\0') //stack underflow
					//{
					//	return false;
					//}
					else
					{
						return false;
					}
				}
			}
			else //closing bracket is the first character
			{
				return false;
			}
			
		}
		else if (Is_operand(exp[i]))
		{
			//do nothing
		}
	}
	if (!stack.isEmpty())
	{
		return false;
	}
	else
	{
		return true;
	}

}


string infix_to_postfix(string infix)
{
	string postfix;
	Stack stack;

	for (int i = 0; infix[i] != '\0'; i++)
	{
		if (Is_operand(infix[i]))
		{
			postfix = postfix + infix[i];
			if (i != infix.length() - 1 && !(Is_operand(infix[i + 1]))) //if it is not last character and
			{
				postfix = postfix + " ";  //next character is not operand then insert space
			}
			//SEE IF THESE CHANGES HAVE TO BE MADE EVERYWHERE WHEN WE ARE PUSHING 
		}
		else if (Opening_bracket(infix[i])) //starting bracket
		{
			stack.push(infix[i]);
		}
		else if (Is_operator(infix[i]))
		{
			if (stack.isEmpty() || Opening_bracket(stack.peek()) ||
				check_precedence(infix[i]) > check_precedence(stack.peek()))
			{
				stack.push(infix[i]);  //if Stack is empty or there is an opening bracket or incoming operator has 
			}								//higher precedence than the one already exisiting in Stack
			else 
			{			//check precedence
				while (!(stack.isEmpty()) && !(check_precedence(infix[i]) > check_precedence(stack.peek())))
				{
					char ch = stack.pop();
					postfix = postfix + ch;
				}
				stack.push(infix[i]);
			}
		}
		else if (Closing_bracket(infix[i])) 
		{
			while (stack.peek() != match_bracket(infix[i]))
			{
				char ch = stack.pop();
				postfix = postfix + ch;
			}
			stack.pop(); //to eliminate closing bracket
		}
	}
	if (stack.isEmpty())
	{
		return postfix;
	}
	while (!stack.isEmpty())
	{
		char ch = stack.pop();
		postfix = postfix + ch;
	}
	return postfix;
}

int main()
{
	string expression;
	cout << "Enter a expression : " << endl;
	getline(cin, expression);
	//cout << validate_expression(expression) << endl;
	if (validate_expression(expression))
	{
		string post = infix_to_postfix(expression);
		cout << post;
	}
	
}