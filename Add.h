#pragma once
#include "Operation.h"
class Add : public Operation {
public:
	Add();
	~Add();
	void destroy();
	double func(double rightOperand, double leftOperand);
	std::string getName();
	bool is_binary();
	bool is_postfix();
	int getPriority();
private:
	std::string name;

};

