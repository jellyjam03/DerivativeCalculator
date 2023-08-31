#include "Divide.h"
#include "Multiply.h"
#include "Minus.h"

Operand* Divide::Derivative() {
	Divide* returnTree = new Divide;

	//la stanga impartirii
	//f' * g - f * g'
	returnTree->SetLeft(new Minus);
	returnTree->GetLeft()->SetLeft(new Multiply);
	returnTree->GetLeft()->SetRight(new Multiply);
	returnTree->GetLeft()->GetLeft()->SetLeft(this->left->Derivative());   //f'
	returnTree->GetLeft()->GetLeft()->SetRight(this->right->Clone());      //g
	returnTree->GetLeft()->GetRight()->SetLeft(this->left->Clone());	   //f
	returnTree->GetLeft()->GetRight()->SetRight(this->right->Derivative());//g'

	//g*g
	returnTree->SetRight(new Multiply);
	returnTree->GetRight()->SetLeft(this->right->Clone());
	returnTree->GetRight()->SetRight(this->right->Clone());

	return returnTree;
}