#include <iostream>
#include "Postfixate.h"

int main() 
{
	string infix, postfix;

	cin >> infix;
	postfix = convertPostfixed(infix);
	cout << postfix;
	return 0;
}
