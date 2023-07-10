#pragma once
#include "Operator.h"

class Power : public Operator {
public:
	Power(string s) : Operator(s) {}
	~Power() {}

	void Derivative() {}
};
