#include "Subtract.h"

Subtract::Subtract() : name("-") {}

Subtract::~Subtract() {}

void Subtract::destroy() {}
double Subtract::func(double rightOperand, double leftOperand) {
	return leftOperand - rightOperand;
}

std::string Subtract::getName() {
	return name;
}

bool Subtract::is_binary() {
	return true;
}

bool Subtract::is_postfix() {
	return false;
}

int Subtract::getPriority() {
	return 2;
}