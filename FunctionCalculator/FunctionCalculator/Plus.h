#pragma once
#include "Operator.h"

class Plus : public Operator {
public:
	Plus(string& token) : Operator(token) {
	}
	~Plus() {}
	
	void Derivative() {
	}
};
