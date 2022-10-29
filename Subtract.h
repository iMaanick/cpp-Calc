#pragma once
#include "Operation.h"
class Subtract : public Operation {
public:
	Subtract();
	~Subtract();
	void destroy();
	double func(double rightOperand, double leftOperand);
	std::string getName();
	bool is_binary();
	bool is_postfix();
	int getPriority();
private:
	std::string name;
};

