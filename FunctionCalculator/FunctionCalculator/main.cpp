#include "Expression.h"

int main() 
{
	/*Expression* func = new Expression;

	cin >> *func;
	Expression* deriv = new Expression;
	deriv->SetTree(func->GetTree()->Derivative());
	cout << *deriv;*/
	string* input = new string;
	Expression* func = NULL;
	cin >> *input;
	for (int i = 0; i < 100000; i++) {
		func = new Expression;
		func->Initialize(input);
		delete func;
	}
	return 0;
}