#pragma once
#include "Operator.h"

class Divide : public Operator {
public:
	Divide(string s) : Operator(s) {}
	~Divide() {}

	void Derivative() {}
};
