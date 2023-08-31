#pragma once
#include <string>

class Expression;

using namespace std;

class Operand {
protected:
	Operand* left, * right;
public:
	Operand() {
		left = right = NULL;
	}
	Operand(Operand& cp) {
		if (left != NULL) delete left;
		if (right != NULL) delete right;
		left = cp.GetLeft()->Clone();
		right = cp.GetRight()->Clone();
	}
	Operand(Operand&& mv) noexcept {
		if (left != NULL) delete left;
		if (right != NULL) delete right;
		left = mv.left;
		right = mv.right;

		mv.left = mv.right = NULL;
	}
	~Operand() {
		if (left!= NULL) delete left;
		if (right != NULL) delete right;
	}

	void SetLeft(Operand* op) {
		if (left != NULL) delete left;
		left = op;
	}

	void SetRight(Operand* op) {
		if (right != NULL) delete right;
		right = op;
	}

	Operand* GetLeft() { return left; }
	Operand* GetRight() { return right; }
	virtual Operand* Derivative() = 0;
	virtual int GetPriority() = 0;
	virtual Operand* Clone() = 0;
};