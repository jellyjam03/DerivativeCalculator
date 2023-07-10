#pragma once
#include "Operand.h"

class Operator : public Operand {
public:
	Operator(string& token) : Operand(token) {
	}
	~Operator() {
	}

	virtual void Derivative() = 0;
};
