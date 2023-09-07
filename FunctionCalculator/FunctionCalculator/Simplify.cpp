#include "Cosinus.h"
#include "Cotangent.h"
#include "Divide.h"
#include "LogarithmN.h"
#include "Minus.h"
#include "Multiply.h"
#include "Number.h"
#include "Plus.h"
#include "Power.h"
#include "Sinus.h"
#include "Tangent.h"
#include "Variable.h"

bool isNumber(Operand* obj);
bool isZero(Operand* obj);
bool isOne(Operand* obj);
bool isE(Operand* obj);
bool isPi(Operand* obj);
string addString(Number* a, Number* b);
string subString(Number* a, Number* b);
string mulString(Number* a, Number* b);
void divString(Operand*& a, Operand*& b);
string powString(Number* a, Number* b);
void reverse(string& x);
bool isEqual(string& a, string& b);
bool isGreater(string& a, string& b);
unsigned long long int toNum(string& x);
string toString(unsigned long long int x);
unsigned long long int gcd(unsigned long long int a, unsigned long long int b);

Operand* Cosinus::Simplify() {
	Operand* rightSimple = NULL;
	if (right != NULL) rightSimple = right->Simplify();

	if (isZero(rightSimple)) {
		Number* returnNumber = new Number("1");
		delete rightSimple;
		return returnNumber;
	}

	if (isPi(rightSimple)) {
		Minus* returnMin = new Minus;
		Number* one = new Number("1");
		returnMin->SetRight(one);
		delete rightSimple;
		return returnMin;
	}

	Cosinus* returnCos = new Cosinus;
	returnCos->SetRight(rightSimple);
	return returnCos;
}

Operand* Cotangent::Simplify() {
	Operand* rightSimple = NULL;
	if (right != NULL) rightSimple = right->Simplify();

	Cotangent* returnCtg = new Cotangent;
	returnCtg->SetRight(rightSimple);
	return returnCtg;
}

Operand* Divide::Simplify() {
	Operand* leftSimple = NULL, * rightSimple = NULL;
	if (left != NULL) leftSimple = left->Simplify();
	if (right != NULL) rightSimple = right->Simplify();

	if (isZero(leftSimple)) {
		Number* returnNum = new Number("0");
		delete leftSimple;
		delete rightSimple;
		return returnNum;
	}

	if (isNumber(leftSimple) && isNumber(rightSimple))
		divString(leftSimple, rightSimple);

	if (isOne(rightSimple)) {
		delete rightSimple;
		return leftSimple;
	}

	Divide* returnDiv = new Divide;
	returnDiv->SetLeft(leftSimple);
	returnDiv->SetRight(rightSimple);

	return returnDiv;
}
Operand* LogarithmN::Simplify() {
	Operand* leftSimple = NULL, * rightSimple = NULL;
	if (left != NULL) leftSimple = left->Simplify();
	if (right != NULL) rightSimple = right->Simplify();

	if (isE(leftSimple) && isE(rightSimple)) {
		Number* returnNumber = new Number("1");
		delete leftSimple;
		delete rightSimple;
		return returnNumber;
	}

	LogarithmN* returnLog = new LogarithmN;
	returnLog->SetLeft(leftSimple);
	returnLog->SetRight(rightSimple);
	return returnLog;
}

Operand* Minus::Simplify() {
	Operand* leftSimple = NULL, * rightSimple = NULL;
	if (left != NULL) leftSimple = left->Simplify();
	if (right != NULL) rightSimple = right->Simplify();

	if (leftSimple == NULL && isZero(rightSimple)) {
		return rightSimple;
	}

	if (isNumber(leftSimple) && isNumber(rightSimple)) {
		if (isGreater(dynamic_cast<Number*>(leftSimple)->GetNumber(), dynamic_cast<Number*>(rightSimple)->GetNumber()) ||
			isEqual(dynamic_cast<Number*>(leftSimple)->GetNumber(), dynamic_cast<Number*>(rightSimple)->GetNumber())) {
			Number* returnNum = new Number((string&)subString(dynamic_cast<Number*>(leftSimple), dynamic_cast<Number*>(rightSimple)));
			delete leftSimple;
			delete rightSimple;
			return returnNum;
		}
		Minus* returnMin = new Minus;
		returnMin->SetRight(new Number((string&)subString(dynamic_cast<Number*>(rightSimple), dynamic_cast<Number*>(leftSimple))));
		delete leftSimple;
		delete rightSimple;
		return returnMin;
	}

	if (isZero(leftSimple)) {
		Minus* returnMin = new Minus;
		returnMin->SetRight(rightSimple);
		delete leftSimple;
		return returnMin;
	}

	if (isZero(rightSimple)) {
		delete rightSimple;
		return leftSimple;
	}

	Minus* returnMinus = new Minus;
	returnMinus->SetLeft(leftSimple);
	returnMinus->SetRight(rightSimple);
	return returnMinus;
}
Operand* Multiply::Simplify() {
	Operand* leftSimple = NULL, * rightSimple = NULL;
	if (left != NULL) leftSimple = left->Simplify();
	if (right != NULL) rightSimple = right->Simplify();

	if (isNumber(leftSimple) && isNumber(rightSimple)) {
		Number* returnNum = new Number((string&)mulString(dynamic_cast<Number*>(leftSimple), dynamic_cast<Number*>(rightSimple)));
		delete leftSimple;
		delete rightSimple;
		return returnNum;
	}

	if (isZero(leftSimple) || isZero(rightSimple)) {
		Number* returnNum = new Number("0");
		delete leftSimple;
		delete rightSimple;
		return returnNum;
	}

	if (isOne(leftSimple)) {
		delete leftSimple;
		return rightSimple;
	}
	if (isOne(rightSimple)) {
		delete rightSimple;
		return leftSimple;
	}

	Multiply* returnMul = new Multiply;
	returnMul->SetLeft(leftSimple);
	returnMul->SetRight(rightSimple);
	return returnMul;
}
Operand* Number::Simplify() { return this->Clone(); }
Operand* Plus::Simplify() {
	Operand* leftSimple = NULL, *rightSimple = NULL;
	if (left != NULL) leftSimple = left->Simplify();
	if (right != NULL) rightSimple = right->Simplify();
	
	if (isNumber(leftSimple) && isNumber(rightSimple)) {
		Number* returnNum = new Number((string&)addString(dynamic_cast<Number*>(leftSimple), dynamic_cast<Number*>(rightSimple)));
		delete leftSimple;
		delete rightSimple;
		return returnNum;
	}

	if (isZero(leftSimple)) {
		delete leftSimple;
		return rightSimple;
	}

	if (isZero(rightSimple)) {
		delete rightSimple;
		return leftSimple;
	}

	Plus* returnPlus = new Plus;
	returnPlus->SetLeft(leftSimple);
	returnPlus->SetRight(rightSimple);
	return returnPlus;
}
Operand* Power::Simplify() {
	Operand* leftSimple = NULL, * rightSimple = NULL;
	if (left != NULL) leftSimple = left->Simplify();
	if (right != NULL) rightSimple = right->Simplify();

	if (isZero(leftSimple) || isOne(leftSimple)) {
		delete rightSimple;
		return leftSimple;
	}

	if (isZero(rightSimple)) {
		delete leftSimple;
		delete rightSimple;
		Number* returnNum = new Number("1");
		return returnNum;
	}

	if (isNumber(leftSimple) && isNumber(rightSimple)) {
		Number* returnNum = new Number((string&)powString(dynamic_cast<Number*>(leftSimple), dynamic_cast<Number*>(rightSimple)));
		delete leftSimple;
		delete rightSimple;
		return returnNum;
	}

	Power* returnPow = new Power;
	returnPow->SetLeft(leftSimple);
	returnPow->SetRight(rightSimple);
	return returnPow;
}
Operand* Sinus::Simplify() {
	Operand* rightSimple = NULL;
	if (right != NULL) rightSimple = right->Simplify();

	if (isZero(rightSimple)) {
		return rightSimple;
	}

	if (isPi(rightSimple)) {
		Number* returnNum = new Number("0");
		delete rightSimple;
		return returnNum;
	}

	Sinus* returnSin = new Sinus;
	returnSin->SetRight(rightSimple);
	return returnSin;
}

Operand* Tangent::Simplify() {
	Operand* rightSimple = NULL;
	if (right != NULL) rightSimple = right->Simplify();

	if (isZero(rightSimple)) {
		return rightSimple;
	}

	if (isPi(rightSimple)) {
		Number* returnNum = new Number("0");
		delete rightSimple;
		return returnNum;
	}

	Tangent* returnTg = new Tangent;
	returnTg->SetRight(rightSimple);
	return returnTg;
}
Operand* Variable::Simplify() { return this->Clone(); }


bool isNumber(Operand* obj) {
	return dynamic_cast<Number*>(obj) != NULL;
}

bool isZero(Operand* obj) {
	if (!isNumber(obj)) return 0;
	return dynamic_cast<Number*>(obj)->GetNumber() == "0";
}

bool isOne(Operand* obj) {
	if (!isNumber(obj)) return 0;
	return dynamic_cast<Number*>(obj)->GetNumber() == "1";
}

bool isE(Operand* obj) {
	if (!isNumber(obj)) return 0;
	return dynamic_cast<Number*>(obj)->GetNumber() == "e";
}

bool isPi(Operand* obj) {
	if (!isNumber(obj)) return 0;
	return dynamic_cast<Number*>(obj)->GetNumber() == "pi";
}

string addString(Number* a, Number* b) {
	string aReverse, bReverse, result = "";
	aReverse = a->GetNumber();
	bReverse = b->GetNumber();
	reverse(aReverse);
	reverse(bReverse);
	
	int i, j, carry = 0, lgRes;
	for (i = 0, j = 0, lgRes = 0; i < aReverse.size() && j < bReverse.size(); i++, j++) {
		carry = carry + aReverse[i] - '0' + bReverse[j] - '0';
		result += carry % 10 + '0';
		carry /= 10;
	}

	for (; i < aReverse.size(); i++) {
		carry = carry + aReverse[i] - '0';
		result += carry % 10 + '0';
		carry /= 10;
	}

	for (; j < bReverse.size(); j++) {
		carry = carry + bReverse[j] - '0';
		result += carry % 10 + '0';
		carry /= 10;
	}

	while (carry) {
		result += carry % 10 + '0';
		carry /= 10;
	}
	reverse(result);
	return result;
}

void reverse(string& x) {
	int i;
	char aux;
	for (i = 0; i < x.size() / 2; i++) {
		aux = x[i];
		x[i] = x[x.size() - 1 - i];
		x[x.size() - 1 - i] = aux;
	}
}

string subString(Number* a, Number* b) {
	unsigned long long int aNum = 0, bNum = 0, i, resNum;
	string result = "";

	aNum = toNum(a->GetNumber());
	bNum = toNum(b->GetNumber());
	resNum = aNum - bNum;

	result = toString(resNum);
	return result;
}

string mulString(Number* a, Number* b) {
	unsigned long long int aNum, bNum, resNum;
	string result;

	aNum = toNum(a->GetNumber());
	bNum = toNum(b->GetNumber());

	resNum = aNum * bNum;
	result = toString(resNum);

	return result;
}

bool isEqual(string& a, string& b) {
	if (a.size() != b.size()) return 0;
	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i]) return 0;
	return 1;
}

bool isGreater(string& a, string& b) {
	if (a.size() > b.size()) return 1;
	if (a.size() < b.size()) return 0;

	for (int i = 0; i < a.size(); i++)
		if (a[i] > b[i]) return 1;
		else if (a[i] < b[i]) return 0;
	return 0;
}

unsigned long long int toNum(string& x) {
	int i;
	unsigned long long int res = 0;
	for (i = 0; i < x.size(); i++) {
		res = res * 10 + x[i] - '0';
	}
	return res;
}

string toString(unsigned long long int x) {
	string res="";

	if (x == 0) {
		res = "0";
		return res;
	}

	while (x) {
		res += x % 10 + '0';
		x /= 10;
	}
	reverse(res);

	return res;
}

void divString(Operand*& a, Operand*& b) {
	unsigned long long int aNum, bNum, cmmdc;
	aNum = toNum(dynamic_cast<Number*>(a)->GetNumber());
	bNum = toNum(dynamic_cast<Number*>(b)->GetNumber());

	cmmdc = gcd(aNum, bNum);
	aNum /= cmmdc;
	bNum /= cmmdc;

	delete a;
	delete b;
	a = new Number((string&)toString(aNum));
	b = new Number((string&)toString(bNum));
}

unsigned long long int gcd(unsigned long long int a, unsigned long long int b) {
	unsigned long long int rest;

	while (b) {
		rest = a % b;
		a = b;
		b = rest;
	}

	return a;
}

string powString(Number* a, Number* b) {
	unsigned long long int aNum, bNum, resNum = 1;
	string result;

	aNum = toNum(a->GetNumber());
	bNum = toNum(b->GetNumber());

	while (bNum) {
		resNum *= aNum;
		bNum--;
	}
	result = toString(resNum);
	
	return result;
}