#pragma once
#include "Operator.h"

class Minus : public Operator {
public:
	Minus(string& token) : Operator(token) {
	}
	~Minus() {}

	void Derivative() {
		
	}
};
