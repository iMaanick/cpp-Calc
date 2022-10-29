#include "Add.h"

Add::Add() : name("+") {}

Add::~Add() {}

void Add::destroy() {}
double Add::func(double rightOperand, double leftOperand) {
	return rightOperand + leftOperand;
}

std::string Add::getName() {
	return name;
}

bool Add::is_binary() {
	return true;
}

bool Add::is_postfix() {
	return false;
}

int Add::getPriority() {
	return 2;
}

