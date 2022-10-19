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
				/* if it is like (+ OR there is a closing bracket immediately after a opening bracket */
				if (Is_operator(exp[i + 1]) || Closing_bracket(exp[i + 1])) 
				{
					return false; 
				}

				/* if it is not the first character and there is a closing bracket or an operand immediately 
				before the opening bracket */
				else if (i != 0 && (Closing_bracket(exp[i - 1]) || (Is_operand(exp[i - 1]))))
				{
					return false;
				}

				else if (!(Is_operator(exp[i + 1]))) //CAN IT BE WRITTEN AS ONLY ELSE INSTEAD OF ELSE IF?
				{
					stack.push(exp[i]);
				}
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
				/* if it is like +)  OR there is a opening bracket immediately before a closing bracket */
				if (Is_operator(exp[i - 1]) || Opening_bracket(exp[i - 1]))  
				{
					return false;	
				}

				/* if it is not the last character and there is an opening bracket or there is an operand 
				 immediately after a closing bracket ===> like ")(" or ")+" */   
				else if (i != exp.length() - 1 && (Opening_bracket(exp[i + 1]) || (Is_operand(exp[i + 1]) )))
				{
					return false;  
				}

				else /*if (!(Is_operator(exp[i - 1])))*/
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
		//else if (Is_operand(exp[i]))
		//{
		//	//do nothing
		//}
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

float evaluate_operation(float num_1, float num_2, char op)
{
	switch(op)
	{
	case '+':
		return (num_2 + num_1);

	case '-':
		return (num_2 - num_1);

	case '*':
		return (num_2 * num_1);

	case '/':
		if (num_1 == 0)
		{
			return -32768;
		}
		return (num_2 / num_1);

	case '%':
		return (int(num_2) % int(num_1));

	case '^':
		int power = 1;
		for (int i = 0; i < num_1; i++)
		{
			power = power * num_2;
		}
		return power;
	}
}

int evaluate_postfix(string postfix)
{
	Stack stack;
	int multi_digit = 0;
	int ans = 0;

	for (int i = 0; postfix[i] != '\0'; i++)
	{
		if (Is_operand(postfix[i]))
		{
			if (i != postfix.length() && !(Is_operand(postfix[i + 1])) && postfix[i + 1]!= ' ') //if it is not last character and is single digit
			{
				stack.push(postfix[i]);
			}
			multi_digit = multi_digit * 10 + (postfix[i] - '0');
		}
		else if (postfix[i] == ' ')
		{
			stack.push(multi_digit);
			multi_digit = 0;
		}
		else if (Is_operator(postfix[i]))
		{
			int no_1 = stack.pop();
			int no_2 = stack.pop();

			ans = evaluate_operation(no_1, no_2, postfix[i]);
			if (ans == -32768)
			{
				cout << "Can't Divide by Zero" << endl;
				return ans;
			}
			stack.push(ans);
		}
	}
	return stack.pop();
}

int main()
{
	string expression;
	cout << "Enter a expression : " << endl;
	getline(cin, expression);
	//cout << validate_expression(expression) << endl;
	while (!validate_expression(expression))
	{
		cout << "WRONG. Enter a expression : " << endl;
		getline(cin, expression);
	}
	string postfix = infix_to_postfix(expression);
	cout << postfix << endl;
	int answer = evaluate_postfix(postfix);
	cout << answer << endl;

	cout << (23 - 14 / (9 - (5 + 9))*87 % 7) << endl;
}