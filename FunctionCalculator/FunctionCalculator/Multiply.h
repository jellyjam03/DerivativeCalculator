#pragma once
#include "Operator.h"

class Multiply : public Operator {
public:
	Multiply(string s) : Operator(s) {}
	~Multiply() {}

	void Derivative() {}
};
