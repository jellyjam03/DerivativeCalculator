#include "Expression.h"

int main() 
{
	Expression* func = new Expression;

	cin >> *func;
	Expression* deriv = new Expression;
	deriv->SetTree(func->GetTree()->Derivative());
	cout << *deriv;

	return 0;
}