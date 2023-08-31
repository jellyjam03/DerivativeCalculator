#include "Multiply.h"
#include "Plus.h"

Operand* Multiply::Derivative() {
	Plus* returnTree = new Plus;
	returnTree->SetLeft(new Multiply);
	returnTree->SetRight(new Multiply);
	returnTree->GetLeft()->SetLeft(this->left->Derivative());
	returnTree->GetLeft()->SetRight(this->right->Clone());
	returnTree->GetRight()->SetLeft(this->left->Clone());
	returnTree->GetRight()->SetRight(this->right->Derivative());
	return returnTree;
}