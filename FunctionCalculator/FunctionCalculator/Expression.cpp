#include "Expression.h"
#include "Plus.h"
#include "Minus.h"
#include "Multiply.h"
#include "Divide.h"
#include "Power.h"
#include "LogarithmN.h"
#include "Number.h"
#include "Variable.h"
#include "Sinus.h"
#include "Cosinus.h"
#include "Tangent.h"
#include "Cotangent.h"

string* Number::e = new string("e");
string* Number::pi = new string ("pi");

Expression::Expression() {
	tree = NULL;
	expression = NULL; //postfixed = NULL;
}

Expression::~Expression() {
	memset(expression, NULL, expression->size());
	//memset(postfixed, NULL, postfixed->size());
	delete expression;
	//delete postfixed;
	delete tree;
}

Operand* Expression::GetTree() { return tree; }

void Expression::SetTree(Operand* toSet) {
	if (tree != NULL) delete tree;
	tree = toSet;
	//trebuie updatata si expresia printr-o parcurgere inordine a arborelui
	if (expression != NULL) delete expression;
	expression = InorderDFS(tree);
}

string* Expression::InorderDFS(Operand* tree) {
	string* returnString = new string("");
	if (tree == NULL) return returnString;

	string root;
	string* left, * right;
	//verifica prioritatea semnelor pentru paranteze

	left = InorderDFS(tree->GetLeft());
	right = InorderDFS(tree->GetRight());
	if (dynamic_cast<Plus*>(tree) != NULL) root = "+";
	if (dynamic_cast<Minus*>(tree) != NULL) root = "-";
	if (dynamic_cast<Divide*>(tree) != NULL) root = "/";
	if (dynamic_cast<Multiply*>(tree) != NULL) root = "*";
	if (dynamic_cast<Power*>(tree) != NULL) root = "^";
	if (dynamic_cast<Number*>(tree) != NULL) root = dynamic_cast<Number*>(tree)->GetNumber();
	if (dynamic_cast<Variable*>(tree) != NULL) root = "x";
	if (dynamic_cast<LogarithmN*>(tree) != NULL) *returnString = "log";//singura exceptie in care operandul se afla in fata fiilor in scrierea infixata
	if (dynamic_cast<Sinus*>(tree) != NULL) root = "sin";
	if (dynamic_cast<Cosinus*>(tree) != NULL) root = "cos";
	if (dynamic_cast<Tangent*>(tree) != NULL) root = "tg";
	if (dynamic_cast<Cotangent*>(tree) != NULL) root = "ctg";


	if (tree->GetLeft() != NULL)
		if (tree->GetLeft()->GetPriority() < tree->GetPriority())
			*returnString = *returnString + "(" + *left + ")";
		else
			*returnString = *returnString + *left;
	if (dynamic_cast<LogarithmN*>(tree) == NULL)
		*returnString = *returnString + root;
	if (tree->GetRight() != NULL)
		if (tree->GetRight()->GetPriority() < tree->GetPriority() || 
			dynamic_cast<Minus*>(tree) != NULL && tree->GetRight()->GetPriority() == tree->GetPriority() || 
			tree->GetPriority() == 11 ||
			dynamic_cast<Divide*>(tree) != NULL && tree->GetRight()->GetPriority() == tree->GetPriority())
			*returnString = *returnString + "(" + *right + ")";
		else
			*returnString = *returnString + *right;
	delete left;
	delete right;
	return returnString;
}

void Expression::Print() {
	cout << *expression;
}

string* Expression::convertPostfixed(string& infix) {
	string postfix, operators = "+-*/^()lsct";
	stack<string> s;
	map<string, int> priority = { {"+", 0}, {"-", 0}, {"*", 1}, {"/", 1}, {"^", 2}, {"(", -1}, {")", -1}, {"log", 3}, {"sin", 3}, {"cos", 3}, {"tg", 3}, {"ctg", 3} };
	int i;
	for (i = 0; i < infix.size(); i++) {
		if (operators.find(infix[i]) != string::npos) {
			AddOperator(postfix, infix, i, s, priority);
		}
		else {
			AddOperand(postfix, infix, i, s, operators);
		}
	}
	while (!s.empty()) {
		postfix += ",";
		postfix += s.top();
		s.pop();
	}
	string* aux = new string(postfix);
	return aux;
}

void Expression::AddOperator(string& postfix, string& infix, int& i, stack<string>& s, map<string, int>& priority) {
	if (infix[i] == '(') {
		s.push(infix.substr(i, 1));
		return;
	}

	if (infix[i] == ')') {
		while (s.top() != "(") {
			postfix += ",";
			postfix += s.top();
			s.pop();
		}
		s.pop();
		return;
	}

	int lg = 1;
	if (infix[i] == 'l' || infix[i] == 's' || infix[i] == 'c') lg = 3;
	if (infix[i] == 't') lg = 2;

	if (infix[i] == '-' && (i == 0 || infix[i - 1] == '('))
		postfix += ",0";

	while (s.size() != 0 && priority[infix.substr(i, lg)] <= priority[s.top()]) {
		postfix += ",";
		postfix += s.top();
		s.pop();
	}
	s.push(infix.substr(i, lg));
	i = i + lg - 1;
}

void Expression::AddOperand(string& postfix, string& infix, int& i, stack<string>& s, string& operators) {
	postfix += ",";
	while (i < infix.size() && operators.find(infix[i]) == string::npos) {
		postfix += infix[i];
		i++;
	}
	i--;
}

void Expression::Initialize(string* str) {
	expression = new string(*str);
	string* postfixed;
	postfixed = convertPostfixed(*str);
	tree = DepthFirstTreeInit(*postfixed);
}

istream& operator>>(istream& input, Expression& obj) {
	string aux;
	input >> aux;
	obj.Initialize(&aux);
	return input;
}

ostream& operator<<(ostream& output, Expression& obj) {
	output << *obj.expression;
	return output;
}

Operand* Expression::DepthFirstTreeInit(string& s) {
	Operand* returnTree = NULL;

	bool leaf = 0;
	bool trigo = 0;
	int offset = -1, lg = 1;
	string substring = s.substr(s.size() - 1, 1);

	switch (s[s.size() - 1]) {
	case '+':
		returnTree = new Plus;
		break;
	case '-':
		returnTree = new Minus;
		break;
	case '*':
		returnTree = new Multiply;
		break;
	case '/':
		returnTree = new Divide;
		break;
	case '^':
		returnTree = new Power;
		break;
	case 'g':
		switch (s[s.size() - 3]) {
		case 'l':
			returnTree = new LogarithmN;
			lg = 3;
			break;
		case 'c':
			returnTree = new Cotangent;
			trigo = 1;
			lg = 3;
			break;
		default:
			returnTree = new Tangent;
			trigo = 1;
			lg = 2;
			break;
		}
		break;
	case 'n':
		returnTree = new Sinus;
		trigo = 1;
		lg = 3;
		break;
	case 's':
		returnTree = new Cosinus;
		trigo = 1;
		lg = 3;
		break;
	case 'x':
		returnTree = new Variable;
		leaf = 1;
		break;
	default:
		leaf = 1;
		lg = s.size() - s.find_last_of(",") - 1;
		offset = s.find_last_of(",");
		substring = s.substr(offset + 1);
		returnTree = new Number(substring);
	}
	if (s.find(',') != string::npos)
		s.erase(s.size() - lg - 1, lg + 1);
	else
		s.erase(s.size() - lg, lg);

	if (!leaf) {
		returnTree->SetRight(DepthFirstTreeInit(s));
		if (!trigo)
			returnTree->SetLeft(DepthFirstTreeInit(s));
	}

	/*string operators = "+-/*^()";
	if (operators.find(op->GetInfo()) != string::npos) {
		right = new Expression(s);
		left = new Expression(s);
	}*/
	return returnTree;
}