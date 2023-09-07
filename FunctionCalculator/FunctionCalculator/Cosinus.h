#pragma once
#include "Operand.h"

class Cosinus : public Operand {
public:
	Cosinus() : Operand() {}
	Cosinus(Cosinus& cp) : Operand(cp) {}
	Cosinus(Cosinus&& mv) noexcept : Operand(mv) {}
	~Cosinus() {}

	Operand* Derivative() override;
	int GetPriority() override { return 11; }
	Operand* Clone() override {
		Cosinus* returnTree = new Cosinus;
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
	Operand* Simplify() override;
};
