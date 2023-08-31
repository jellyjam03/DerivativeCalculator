#pragma once
#include "Operand.h"

class Divide : public Operand {
public:
	Divide() : Operand() {}
	Divide(Divide& cp) : Operand(cp) {}
	Divide(Divide&& mv) noexcept : Operand(mv) {}
	~Divide() {}

	Operand* Derivative() override;
	int GetPriority() override { return 1; }
	Operand* Clone() override {
		Divide* returnTree = new Divide;
		returnTree->SetLeft(this->left->Clone());
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
};
