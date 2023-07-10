#pragma once
#include <string>

using namespace std;

class Operand {
protected:
	string* info;
public:
	Operand(string& token) {
		info = new string;
		*info = token;
	}
	~Operand() {
		info->clear();
		delete info;
	}

	char GetInfo() { return info->at(0); }
	virtual void Derivative() = 0;
};
