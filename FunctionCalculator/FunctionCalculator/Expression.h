#pragma once
#include <iostream>
#include <map>
#include <stack>
#include "Operand.h"


class Expression {
	string* expression;
	Operand* tree;
public:
	Expression();
	~Expression();

	Operand* GetTree();
	void SetTree(Operand* toSet);
	string* InorderDFS(Operand* tree);
	string* convertPostfixed(string& infix);
	void AddOperator(string& postfix, string& infix, int& i, stack<string>& s, map<string, int>& priority);
	void AddOperand(string& postfix, string& infix, int& i, stack<string>& s, string& operators);
	void Initialize(string* str);
	Operand* DepthFirstTreeInit(string& str);
	friend istream& operator>>(istream& input, Expression& obj);
	friend ostream& operator<<(ostream& output, Expression& obj);

	void Print();
};