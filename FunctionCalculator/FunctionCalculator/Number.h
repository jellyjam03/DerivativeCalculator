#pragma once
#include "Operand.h"

class Number : public Operand {
public:
	Number(string s) : Operand(s) {}
	~Number() {}

	void Derivative() {}
};
