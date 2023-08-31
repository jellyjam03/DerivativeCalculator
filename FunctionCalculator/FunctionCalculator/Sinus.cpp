#include "Sinus.h"
#include "Multiply.h"
#include "Cosinus.h"

Operand* Sinus::Derivative() {
	Multiply* returnTree = new Multiply;
	returnTree->SetLeft(new Cosinus);
	returnTree->GetLeft()->SetRight(this->right->Clone());
	returnTree->SetRight(this->right->Derivative());
	return returnTree;
}