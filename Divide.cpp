#include "Divide.h"

Divide::Divide() : name("/") {}

Divide::~Divide() {}

void Divide::destroy() {}

double Divide::func(double rightOperand, double leftOperand) {
	return leftOperand / rightOperand;
}

std::string Divide::getName() {
	return name;
}

bool Divide::is_binary() {
	return true;
}

bool Divide::is_postfix() {
	return false;
}

int Divide::getPriority() {
	return 4;
}

