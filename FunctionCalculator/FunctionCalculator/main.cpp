#include <iostream>
#include "Postfixate.h"
#include "Expression.h"

int main() 
{
	string infix, postfix;

	cin >> infix;
	postfix = convertPostfixed(infix);
	
	Expression* exp = new Expression(postfix);
	return 0;
}