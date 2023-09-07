#pragma once
#include "Operand.h"

class LogarithmN: public Operand {
public:
	LogarithmN() : Operand() {}
	LogarithmN(LogarithmN& cp) : Operand(cp) {}
	LogarithmN(LogarithmN&& mv) noexcept : Operand(mv) {}
	~LogarithmN() {}

	Operand* Derivative() override;
	int GetPriority() override { return 11; }
	Operand* Clone() override {
		LogarithmN* returnTree = new LogarithmN;
		returnTree->SetLeft(this->left->Clone());
		returnTree->SetRight(this->right->Clone());
		return returnTree;
	}
	Operand* Simplify() override;
};
