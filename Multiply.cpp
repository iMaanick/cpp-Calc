#include "Multiply.h"

Multiply::Multiply() : name("*") {}

Multiply::~Multiply() {}

void Multiply::destroy() {}
double Multiply::func(double rightOperand, double leftOperand) {
	return rightOperand * leftOperand;
}

std::string Multiply::getName() {
	return name;
}

bool Multiply::is_binary() {
	return true;
}

bool Multiply::is_postfix() {
	return false;
}

int Multiply::getPriority() {
	return 4;
}
