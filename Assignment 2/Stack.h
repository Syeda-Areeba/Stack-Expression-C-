#pragma once
#include<iostream>
using namespace std;

class Node
{
	int data;
	Node* next;

public:

	Node();
	Node(int data);
	void set_data(int data);
	void set_next(Node* ptr);
	int get_data() const;
	Node* get_next() const;
};

class Stack
{
	Node* top;

public:

	Stack();
	bool isEmpty();
	void push(int data);
	int pop();
	int peek();
};