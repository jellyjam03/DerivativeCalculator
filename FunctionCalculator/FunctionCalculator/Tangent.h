#pragma once
#include "Operand.h"

class Tangent : public Operand {
public:
	Tangent() : Operand() {}
	Tangent(Tangent& cp) : Operand(cp) {}
	Tangent(Tangent&& mv) noexcept : Operand(mv) {}
	~Tangent() {}

	Operand* Derivative() override;
	int GetPriority() override { return 11; }
	Operand* Clone() override {
		Tangent* returnTree = new Tangent;
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
};
