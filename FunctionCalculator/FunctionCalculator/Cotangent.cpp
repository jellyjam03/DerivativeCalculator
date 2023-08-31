#include "Cotangent.h"
#include "Multiply.h"
#include "Minus.h"
#include "Number.h"
#include "Divide.h"
#include "Power.h"
#include "Sinus.h"

Operand* Cotangent::Derivative() {
	//ctg'(f(x)) = (0-1/sin(f(x))^2) * f'(x) 
	Multiply* returnTree = new Multiply;
	//(0-1/sin(f(x))^2)
	returnTree->SetLeft(new Minus);
	returnTree->GetLeft()->SetLeft(new Number("0"));
	returnTree->GetLeft()->SetRight(new Divide);
	returnTree->GetLeft()->GetRight()->SetLeft(new Number("1"));
	//sin(f(x))^2
	returnTree->GetLeft()->GetRight()->SetRight(new Power);
	returnTree->GetLeft()->GetRight()->GetRight()->SetLeft(new Sinus);
	returnTree->GetLeft()->GetRight()->GetRight()->GetLeft()->SetRight(this->right->Clone());
	returnTree->GetLeft()->GetRight()->GetRight()->SetRight(new Number("2"));
	//f'(x)
	returnTree->SetRight(this->right->Derivative());

	return returnTree;
}