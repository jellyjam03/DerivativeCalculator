#include "Tangent.h"
#include "Multiply.h"
#include "Divide.h"
#include "Power.h"
#include "Cosinus.h"
#include "Number.h"

Operand* Tangent::Derivative() {
	Multiply* returnTree = new Multiply;
	//tg'(f(x)) = 1/cos(x)^2 * f'(x)
	returnTree->SetLeft(new Divide);
	returnTree->GetLeft()->SetLeft(new Number("1"));
	returnTree->GetLeft()->SetRight(new Power);
	returnTree->GetLeft()->GetRight()->SetLeft(new Cosinus);
	returnTree->GetLeft()->GetRight()->GetLeft()->SetRight(this->right->Clone());
	returnTree->GetLeft()->GetRight()->SetRight(new Number("2"));
	//f'(x)
	returnTree->SetRight(this->right->Derivative());
	
	return returnTree;
}