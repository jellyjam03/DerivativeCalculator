#include "Postfixate.h"

string convertPostfixed(string infix) {
	string postfix, operators = "+-*/^()";
	stack<char> s;
	map<char, int> priority = { {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'^', 2}, {'(', -1}, {')', -1} };
	int i;
	for (i = 0; i < infix.size(); i++) {
		if (operators.find(infix[i]) != string::npos) {
			AddOperator(postfix, infix, i, s, priority);
		}
		else {
			AddOperand(postfix, infix, i, s, operators);
		}
	}
	while (!s.empty()) {
		postfix += s.top();
		s.pop();
	}
	return postfix;
}

void AddOperator(string& postfix, string& infix, int& i, stack<char>& s, map<char, int>& priority) {
	if (infix[i] == '(') {
		s.push(infix[i]);
		return;
	}

	if (infix[i] == ')') {
		while (s.top() != '(') {
			postfix += s.top();
			s.pop();
		}
		s.pop();
		return;
	}

	while (s.size() != 0 && priority[infix[i]] <= priority[s.top()]) {
		postfix += s.top();
		s.pop();
	}
	s.push(infix[i]);
}

void AddOperand(string& postfix, string& infix, int& i, stack<char>& s, string& operators) {
	while (i < infix.size() && operators.find(infix[i]) == string::npos) {
		postfix += infix[i];
		i++;
	}
	i--;
}