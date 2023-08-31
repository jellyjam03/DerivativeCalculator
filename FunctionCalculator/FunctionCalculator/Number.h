#pragma once
#include "Operand.h"

class Number : public Operand {
	string* number;
public:
	static string* e, * pi;
	Number() : Operand(), number(NULL) {}
	Number(string& s) : Operand() { number = new string(s); }
	Number(const char* s) : Operand() { number = new string(s); }
	Number(Number& cp) : Operand() { this->number = new string(cp.GetNumber()); }
	Number(Number&& mv) noexcept : Operand() { this->number = new string(mv.GetNumber()); delete &mv; }
	~Number() {}

	string& GetNumber() { return *number; }

	Operand* Derivative() override {
		Number* returnTree = new Number("0");
		return returnTree;
	}
	int GetPriority() override { return 10; }
	Operand* Clone() override {
		Number* returnTree = new Number(this->GetNumber());
		return returnTree;
	}
};