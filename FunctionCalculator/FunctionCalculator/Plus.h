#pragma once
#include "Operand.h"

class Plus : public Operand {
public:
	Plus() : Operand() {}
	Plus(Plus& cp) : Operand(cp) {}
	Plus(Plus&& mv) noexcept : Operand(mv) {}
	~Plus() {}
	
	Operand* Derivative() override {
		Plus* returnTree = new Plus;
		returnTree->SetLeft(left->Derivative());
		returnTree->SetRight(right->Derivative());
		return returnTree;
	}
	int GetPriority() override { return 0; }
	Operand* Clone() override {
		Plus* returnTree = new Plus;
		returnTree->SetLeft(this->left->Clone());
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
};
