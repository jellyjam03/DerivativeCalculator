#pragma once
#include "Operand.h"

class Minus : public Operand {
public:
	Minus() : Operand() {}
	Minus(Minus& cp) : Operand(cp) {}
	Minus(Minus&& mv) noexcept : Operand(mv) {}
	~Minus() {}
	
	Operand* Derivative() override {
		Minus* returnTree = new Minus;
		if (this->left != NULL)
			returnTree->SetLeft(this->left->Derivative());
		else
			returnTree->SetLeft(NULL);
		returnTree->SetRight(this->right->Derivative());

		return returnTree;
	}
	int GetPriority() override { return 0; }
	Operand* Clone() override {
		Minus* returnTree = new Minus;
		returnTree->SetLeft(this->left->Clone());
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
};
