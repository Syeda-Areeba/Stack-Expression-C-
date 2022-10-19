#pragma once
#include<iostream>
using namespace std;

class Node
{
	int data;
	Node* next;
public:
	Node()
	{
		data = 0;
		next = nullptr;
	}
	Node(int data)
	{
		this->data = data;
		next = nullptr;
	}
	void set_data(int data)
	{
		this->data = data;
	}
	void set_next(Node* ptr)
	{
		next = ptr;
	}
	int get_data() const
	{
		return this->data;
	}
	Node* get_next() const
	{
		return this->next;
	}
};

//class Node
//{
//	char data;
//	Node* next;
//public:
//	Node()
//	{
//		data = 0;
//		next = nullptr;
//	}
//	Node(char data)
//	{
//		this->data = data;
//		next = nullptr;
//	}
//	void set_data(char data)
//	{
//		this->data = data;
//	}
//	void set_next(Node* ptr)
//	{
//		next = ptr;
//	}
//	char get_data() const
//	{
//		return this->data;
//	}
//	Node* get_next() const
//	{
//		return this->next;
//	}
//};

//class Stack
//{
//	Node* top;
//
//public:
//	Stack()
//	{
//		top = NULL;
//	}
//	bool isEmpty()
//	{
//		if (top == NULL)
//		{
//			return true;
//		}
//		return false;
//	}
//	void push(int data)
//	{
//		if (top == nullptr)
//		{
//			top = new Node(data);
//		}
//		else
//		{
//			Node* temp = new Node(data);
//			temp->set_next(top);
//			top = temp;
//		}
//	}
//	char pop()
//	{
//		if (top == NULL)
//		{
//			return '\0';
//		}
//		else
//		{
//			Node* temp = top->get_next();
//			char data = top->get_data();
//			delete top;
//			top = temp;
//			return data;
//		}
//	}
//	char peek()
//	{
//		if (top == NULL)
//		{
//			return '\0';
//		}
//		return top->get_data();
//	}
//};

class Stack
{
	Node* top;

public:
	Stack()
	{
		top = NULL;
	}
	bool isEmpty()
	{
		if (top == NULL)
		{
			return true;
		}
		return false;
	}
	void push(int data)
	{
		if (top == nullptr)
		{
			top = new Node(data);
		}
		else
		{
			Node* temp = new Node(data);
			temp->set_next(top);
			top = temp;
		}
	}
	int pop()
	{
		if (top == NULL)
		{
			return NULL;
		}
		else
		{
			Node* temp = top->get_next();
			int data = top->get_data();
			delete top;
			top = temp;
			return data;
		}
	}
	int peek()
	{
		if (top == NULL)
		{
			return -32768;
		}
		return top->get_data();
	}
};

//int check_precedence(char op)
//{
//	switch (op)
//	{
//	case '^':
//		return 1;
//
//	case '*':
//	case '/':
//		return 2;
//	
//	case '+':
//	case '-':
//		return 3;
//	
//	case '%':
//		return 4;
//
//	default:
//		return  0;
//	}
//}

int check_precedence(char op)
{
	switch (op)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '%':
		return 3;

	case '^':
		return 4;

	default:
		return  0;
	}
}


