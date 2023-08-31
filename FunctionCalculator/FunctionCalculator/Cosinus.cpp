#include "Cosinus.h"
#include "Multiply.h"
#include "Number.h"
#include "Sinus.h"
#include "Minus.h"

Operand* Cosinus::Derivative() {
	Multiply* returnTree = new Multiply;
	returnTree->SetLeft(new Minus);
	returnTree->GetLeft()->SetLeft(new Number("0"));
	returnTree->GetLeft()->SetRight(new Sinus);
	returnTree->GetLeft()->GetRight()->SetRight(this->right->Clone());
	returnTree->SetRight(this->right->Derivative());
	return returnTree;
}