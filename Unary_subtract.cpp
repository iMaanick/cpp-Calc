#include "Unary_subtract.h"

Unary_subtract::Unary_subtract() : name("~") {}

Unary_subtract::~Unary_subtract() {}

void Unary_subtract::destroy() {}
double Unary_subtract::func(double rightOperand, double leftOperand) {
	return -rightOperand;
}

std::string Unary_subtract::getName() {
	return name;
}

bool Unary_subtract::is_binary() {
	return false;
}

bool Unary_subtract::is_postfix() {
	return false;
}

int Unary_subtract::getPriority() {
	return 3;
}