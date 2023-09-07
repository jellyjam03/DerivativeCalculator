#pragma once
#include "Operand.h"

class Multiply : public Operand {
public:
	Multiply() : Operand() {}
	Multiply(Multiply& cp) : Operand(cp) {}
	Multiply(Multiply&& mv) noexcept : Operand(mv) {}
	~Multiply() {}

	Operand* Derivative() override;
	int GetPriority() override { return 1; }
	Operand* Clone() override {
		Multiply* returnTree = new Multiply;
		returnTree->SetLeft(this->left->Clone());
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
	Operand* Simplify() override;
};
