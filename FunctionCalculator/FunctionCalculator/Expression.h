#pragma once
#include "Operand.h"
#include "Plus.h"
#include "Minus.h"
#include "Multiply.h"
#include "Divide.h"
#include "Power.h"
#include "LogarithmN.h"
#include "Number.h"
#include "Variable.h"

class Expression {
	Operand* op;
	Expression* left, * right;
public:
	Expression(string& s) {
		left = right = NULL;
		op = NULL;

		int offset = -1;
		string substring = s.substr(s.size() - 1, 1);

		switch (s[s.size() - 1]) {
		case '+':
			op = new Plus(substring);
			break;
		case '-':
			op = new Minus(substring);
			break;
		case '*':
			op = new Multiply(substring);
			break;
		case '/':
			op = new Divide(substring);
			break;
		case '^':
			op = new Power(substring);
			break;
		case 'x':
			op = new Variable(substring);
			break;
		default:
			offset = s.find_last_not_of("0123456789");
			substring = s.substr(offset + 1);
			cout << substring << '\n';
			op = new Number(substring);
		}
		if (offset == -1)
			s.erase(s.size() - 1, 1);
		else
			s.erase(offset + 1, s.size() - 1 - offset);

		string operators = "+-*/^()";
		if (operators.find(op->GetInfo()) != string::npos) {
			right = new Expression(s);
			left = new Expression(s);
		}
	}


	~Expression() {
		if (left != NULL) delete left;
		if (right != NULL) delete right;
		if (op != NULL) delete op;
		left = right = NULL;
		op = NULL;
	}

	Expression* GetLeft() { return left; }
	Expression* GetRight() { return right; }
	Operand* GetOperand() { return op; }
};