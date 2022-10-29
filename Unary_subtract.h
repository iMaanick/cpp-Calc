#pragma once
#include "Operation.h"
class Unary_subtract : public Operation {
public:
	Unary_subtract();
	~Unary_subtract();
	void destroy();
	double func(double rightOperand, double leftOperand);
	std::string getName();
	bool is_binary();
	bool is_postfix();
	int getPriority();
private:
	std::string name;
};

