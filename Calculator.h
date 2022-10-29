#pragma once
#include<iostream>
#include<stack>
#include<string>
#include<sstream>
#include <cmath>
#include <vector>
#include <windows.h>
#include <filesystem>
#include "Operation.h"
#include "Add.h"
#include "Divide.h"
#include "Multiply.h"
#include "Subtract.h"
#include "Unary_subtract.h"

typedef Operation* (__cdecl* Operation_factory)();
class Calculator {
public:
	Calculator();
	void solve();
	~Calculator();
private:
	void loadLibrary();
	std::string getExpression();
	void parseString(std::string& expression);
	void replaceAll(std::string& str, const std::string& from, const std::string& to);
	int getOperationPriority(std::string& operation);
	void deleteFirstLeftParenthesisAndModifyString(std::stack <std::string>& stack, std::string& polishNotationString);
	void pushOperationAndModifyString(std::stack <std::string>& stack, std::string& word, std::string& polishNotationString);
	std::string polishNotation(std::string& exp);
	double calculateOperation(double rightOperand, double leftOperand, std::string& operation);
	void pushBinaryOperation(std::stack <std::string>& stack, std::string& word);
	void pushPrefixUnaryOperation(std::stack <std::string>& stack, std::string& word);
	void pushPostfixUnaryOperation(std::stack <std::string>& stack, std::string& word);
	double calculate(std::string& exp);
	std::vector<HINSTANCE> libraries;
	std::vector<Operation*> operations;
};

