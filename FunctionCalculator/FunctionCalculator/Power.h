#pragma once
#include "Operand.h"


class Power : public Operand {
public:
	Power() : Operand() {}
	Power(Power& cp) : Operand(cp) {}
	Power(Power&& mv) noexcept : Operand(mv) {}
	~Power() {}

	Operand* Derivative() override;
	int GetPriority() override { return 2; }
	Operand* Clone() override {
		Power* returnTree = new Power;
		returnTree->SetLeft(this->left->Clone());
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
	Operand* Simplify() override;
};
