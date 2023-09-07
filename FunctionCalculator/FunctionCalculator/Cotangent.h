#pragma once
#include "Operand.h"

class Cotangent : public Operand {
public:
	Cotangent() : Operand() {}
	Cotangent(Cotangent& cp) : Operand(cp) {}
	Cotangent(Cotangent&& mv) noexcept : Operand(mv) {}
	~Cotangent() {}

	Operand* Derivative() override;
	int GetPriority() override { return 11; }
	Operand* Clone() override {
		Cotangent* returnTree = new Cotangent;
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
	Operand* Simplify() override;
};
