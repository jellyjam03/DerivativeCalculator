#pragma once
#include "Operand.h"

class Variable : public Operand {
public:
	Variable(string s) : Operand(s) {}
	~Variable() {}

	void Derivative() {}
};
