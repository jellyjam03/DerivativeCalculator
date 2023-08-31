#include "Power.h"
#include "Multiply.h"
#include "Divide.h"
#include "LogarithmN.h"
#include "Number.h"
#include "Plus.h"

Operand* Power::Derivative() {
	//(f(x)^g(x))' = f(x)^g(x) * (g'(x)*ln(f(x)) + f'(x)*g(x)/f(x))
	//cam complicata
	Multiply* returnTree = new Multiply;
	// f(x)^g(x)
	returnTree->SetLeft(this->Clone());
	returnTree->SetRight(new Plus);
	//g'(x)*ln(f(x))
	returnTree->GetRight()->SetLeft(new Multiply);
	returnTree->GetRight()->GetLeft()->SetLeft(this->right->Derivative());
	returnTree->GetRight()->GetLeft()->SetRight(new LogarithmN);
	returnTree->GetRight()->GetLeft()->GetRight()->SetLeft(new Number(*Number::e));
	returnTree->GetRight()->GetLeft()->GetRight()->SetRight(this->left->Clone());
	//f'(x)*g(x)/f(x)
	returnTree->GetRight()->SetRight(new Divide);
	returnTree->GetRight()->GetRight()->SetRight(this->left->Clone());
	returnTree->GetRight()->GetRight()->SetLeft(new Multiply);
	returnTree->GetRight()->GetRight()->GetLeft()->SetLeft(this->left->Derivative());
	returnTree->GetRight()->GetRight()->GetLeft()->SetRight(this->right->Clone());

	return returnTree;
}