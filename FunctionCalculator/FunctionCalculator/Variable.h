#pragma once
#include "Operand.h"
#include "Number.h"

class Variable : public Operand {
public:
	Variable() : Operand() {}
	Variable(Variable& cp) : Operand() {}
	Variable(Variable&& mv) noexcept : Operand() {}
	~Variable() {}

	Operand* Derivative() override;
	int GetPriority() override { return 10; }
	Operand* Clone() override {
		Variable* returnTree = new Variable;
		return returnTree;
	}
};
