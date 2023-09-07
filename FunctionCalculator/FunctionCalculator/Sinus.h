#pragma once
#include "Operand.h"

class Sinus : public Operand {
public:
	Sinus() : Operand() {}
	Sinus(Sinus& cp) : Operand(cp) {}
	Sinus(Sinus&& mv) noexcept : Operand(mv) {}
	~Sinus() {}

	Operand* Derivative() override;
	int GetPriority() override { return 11; }
	Operand* Clone() override {
		Sinus* returnTree = new Sinus;
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
	Operand* Simplify() override;
};
