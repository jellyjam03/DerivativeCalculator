#pragma once
#include <string>
#include <stack>
#include <map>

using namespace std;

string convertPostfixed(string infix);
void AddOperator(string& postfix, string& infix, int& i, stack<char>& s, map<char, int>& priority);
void AddOperand(string& postfix, string& infix, int& i, stack<char>& s, string& operators);
