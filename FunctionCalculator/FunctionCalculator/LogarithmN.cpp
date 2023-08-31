#include "LogarithmN.h"
#include "Minus.h"
#include "Divide.h"
#include "Power.h"
#include "Multiply.h"
#include "Number.h"

Operand* LogarithmN::Derivative() {
	//log'(g(x))(f(x)) = f'(x)/(f(x)*log(e)(g(x))) - g'(x)*log(e)(f(x))/(g(x)*log^2(e)(g(x)))
	Minus* returnTree = new Minus;
	//f'(x)/(f(x)*log(e)(g(x)))
	returnTree->SetLeft(new Divide);
	returnTree->GetLeft()->SetLeft(this->right->Derivative());
	returnTree->GetLeft()->SetRight(new Multiply);
	returnTree->GetLeft()->GetRight()->SetLeft(this->right->Clone());
	returnTree->GetLeft()->GetRight()->SetRight(new LogarithmN);
	returnTree->GetLeft()->GetRight()->GetRight()->SetLeft(new Number(*Number::e));
	returnTree->GetLeft()->GetRight()->GetRight()->SetRight(this->left->Clone());
	//g'(x)*log(e)(f(x))/(g(x)*log^2(e)(g(x)))
	returnTree->SetRight(new Divide);
	//g'(x)*log(e)(f(x))
	returnTree->GetRight()->SetLeft(new Multiply);
	returnTree->GetRight()->GetLeft()->SetLeft(this->left->Derivative());
	returnTree->GetRight()->GetLeft()->SetRight(new LogarithmN);
	returnTree->GetRight()->GetLeft()->GetRight()->SetLeft(new Number(*Number::e));
	returnTree->GetRight()->GetLeft()->GetRight()->SetRight(this->right->Clone());
	//(g(x)*log^2(e)(g(x)))
	returnTree->GetRight()->SetRight(new Multiply);
	returnTree->GetRight()->GetRight()->SetLeft(this->left->Clone());
	returnTree->GetRight()->GetRight()->SetRight(new Power);
	returnTree->GetRight()->GetRight()->GetRight()->SetLeft(new LogarithmN);
	returnTree->GetRight()->GetRight()->GetRight()->GetLeft()->SetLeft(new Number(*Number::e));
	returnTree->GetRight()->GetRight()->GetRight()->GetLeft()->SetRight(this->left->Clone());
	returnTree->GetRight()->GetRight()->GetRight()->SetRight(new Number("2"));

	return returnTree;
}