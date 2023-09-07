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

Operand* Cosinus::Derivative() {
	Multiply* returnTree = new Multiply;
	returnTree->SetLeft(new Minus);
	returnTree->GetLeft()->SetLeft(new Number("0"));
	returnTree->GetLeft()->SetRight(new Sinus);
	returnTree->GetLeft()->GetRight()->SetRight(this->right->Clone());
	returnTree->SetRight(this->right->Derivative());
	return returnTree;
}

Operand* Cotangent::Derivative() {
	//ctg'(f(x)) = (0-1/sin(f(x))^2) * f'(x) 
	Multiply* returnTree = new Multiply;
	//(0-1/sin(f(x))^2)
	returnTree->SetLeft(new Minus);
	returnTree->GetLeft()->SetLeft(new Number("0"));
	returnTree->GetLeft()->SetRight(new Divide);
	returnTree->GetLeft()->GetRight()->SetLeft(new Number("1"));
	//sin(f(x))^2
	returnTree->GetLeft()->GetRight()->SetRight(new Power);
	returnTree->GetLeft()->GetRight()->GetRight()->SetLeft(new Sinus);
	returnTree->GetLeft()->GetRight()->GetRight()->GetLeft()->SetRight(this->right->Clone());
	returnTree->GetLeft()->GetRight()->GetRight()->SetRight(new Number("2"));
	//f'(x)
	returnTree->SetRight(this->right->Derivative());

	return returnTree;
}

Operand* Divide::Derivative() {
	Divide* returnTree = new Divide;

	//la stanga impartirii
	//f' * g - f * g'
	returnTree->SetLeft(new Minus);
	returnTree->GetLeft()->SetLeft(new Multiply);
	returnTree->GetLeft()->SetRight(new Multiply);
	returnTree->GetLeft()->GetLeft()->SetLeft(this->left->Derivative());   //f'
	returnTree->GetLeft()->GetLeft()->SetRight(this->right->Clone());      //g
	returnTree->GetLeft()->GetRight()->SetLeft(this->left->Clone());	   //f
	returnTree->GetLeft()->GetRight()->SetRight(this->right->Derivative());//g'

	//g*g
	returnTree->SetRight(new Multiply);
	returnTree->GetRight()->SetLeft(this->right->Clone());
	returnTree->GetRight()->SetRight(this->right->Clone());

	return returnTree;
}

Operand* LogarithmN::Derivative() {
	//log'(g(x))(f(x)) = f'(x)/(f(x)*log(e)(g(x))) - g'(x)*log(e)(f(x))/(g(x)*log^2(e)(g(x)))
	Minus* returnTree = new Minus;
	//f'(x)/(f(x)*log(e)(g(x)))
	returnTree->SetLeft(new Divide);
	returnTree->GetLeft()->SetLeft(this->right->Derivative());
	returnTree->GetLeft()->SetRight(new Multiply);
	returnTree->GetLeft()->GetRight()->SetLeft(this->right->Clone());
	returnTree->GetLeft()->GetRight()->SetRight(new LogarithmN);
	returnTree->GetLeft()->GetRight()->GetRight()->SetLeft(new Number(*Number::e));
	returnTree->GetLeft()->GetRight()->GetRight()->SetRight(this->left->Clone());
	//g'(x)*log(e)(f(x))/(g(x)*log^2(e)(g(x)))
	returnTree->SetRight(new Divide);
	//g'(x)*log(e)(f(x))
	returnTree->GetRight()->SetLeft(new Multiply);
	returnTree->GetRight()->GetLeft()->SetLeft(this->left->Derivative());
	returnTree->GetRight()->GetLeft()->SetRight(new LogarithmN);
	returnTree->GetRight()->GetLeft()->GetRight()->SetLeft(new Number(*Number::e));
	returnTree->GetRight()->GetLeft()->GetRight()->SetRight(this->right->Clone());
	//(g(x)*log^2(e)(g(x)))
	returnTree->GetRight()->SetRight(new Multiply);
	returnTree->GetRight()->GetRight()->SetLeft(this->left->Clone());
	returnTree->GetRight()->GetRight()->SetRight(new Power);
	returnTree->GetRight()->GetRight()->GetRight()->SetLeft(new LogarithmN);
	returnTree->GetRight()->GetRight()->GetRight()->GetLeft()->SetLeft(new Number(*Number::e));
	returnTree->GetRight()->GetRight()->GetRight()->GetLeft()->SetRight(this->left->Clone());
	returnTree->GetRight()->GetRight()->GetRight()->SetRight(new Number("2"));

	return returnTree;
}

Operand* Minus::Derivative() {
	Minus* returnTree = new Minus;
	if (this->left != NULL)
		returnTree->SetLeft(this->left->Derivative());
	else
		returnTree->SetLeft(NULL);
	returnTree->SetRight(this->right->Derivative());

	return returnTree;
}

Operand* Multiply::Derivative() {
	Plus* returnTree = new Plus;
	returnTree->SetLeft(new Multiply);
	returnTree->SetRight(new Multiply);
	returnTree->GetLeft()->SetLeft(this->left->Derivative());
	returnTree->GetLeft()->SetRight(this->right->Clone());
	returnTree->GetRight()->SetLeft(this->left->Clone());
	returnTree->GetRight()->SetRight(this->right->Derivative());
	return returnTree;
}

Operand* Number::Derivative() {
	Number* returnTree = new Number("0");
	return returnTree;
}

Operand* Plus::Derivative() {
	Plus* returnTree = new Plus;
	returnTree->SetLeft(left->Derivative());
	returnTree->SetRight(right->Derivative());
	return returnTree;
}

Operand* Power::Derivative() {
	//(f(x)^g(x))' = f(x)^g(x) * (g'(x)*ln(f(x)) + f'(x)*g(x)/f(x))
	//cam complicata
	Multiply* returnTree = new Multiply;
	// f(x)^g(x)
	returnTree->SetLeft(this->Clone());
	returnTree->SetRight(new Plus);
	//g'(x)*ln(f(x))
	returnTree->GetRight()->SetLeft(new Multiply);
	returnTree->GetRight()->GetLeft()->SetLeft(this->right->Derivative());
	returnTree->GetRight()->GetLeft()->SetRight(new LogarithmN);
	returnTree->GetRight()->GetLeft()->GetRight()->SetLeft(new Number(*Number::e));
	returnTree->GetRight()->GetLeft()->GetRight()->SetRight(this->left->Clone());
	//f'(x)*g(x)/f(x)
	returnTree->GetRight()->SetRight(new Divide);
	returnTree->GetRight()->GetRight()->SetRight(this->left->Clone());
	returnTree->GetRight()->GetRight()->SetLeft(new Multiply);
	returnTree->GetRight()->GetRight()->GetLeft()->SetLeft(this->left->Derivative());
	returnTree->GetRight()->GetRight()->GetLeft()->SetRight(this->right->Clone());

	return returnTree;
}

Operand* Sinus::Derivative() {
	Multiply* returnTree = new Multiply;
	returnTree->SetLeft(new Cosinus);
	returnTree->GetLeft()->SetRight(this->right->Clone());
	returnTree->SetRight(this->right->Derivative());
	return returnTree;
}

Operand* Tangent::Derivative() {
	Multiply* returnTree = new Multiply;
	//tg'(f(x)) = 1/cos(x)^2 * f'(x)
	returnTree->SetLeft(new Divide);
	returnTree->GetLeft()->SetLeft(new Number("1"));
	returnTree->GetLeft()->SetRight(new Power);
	returnTree->GetLeft()->GetRight()->SetLeft(new Cosinus);
	returnTree->GetLeft()->GetRight()->GetLeft()->SetRight(this->right->Clone());
	returnTree->GetLeft()->GetRight()->SetRight(new Number("2"));
	//f'(x)
	returnTree->SetRight(this->right->Derivative());

	return returnTree;
}

Operand* Variable::Derivative() {
	Number* returnTree = new Number("1");
	return returnTree;
}