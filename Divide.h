#pragma once
#include "Operation.h"
class Divide : public Operation {
public:
	Divide();
	~Divide();
	void destroy();
	double func(double rightOperand, double leftOperand);
	std::string getName();
	bool is_binary();
	bool is_postfix();
	int getPriority();
private:
	std::string name;
};

