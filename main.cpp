#pragma once
#include "Calculator.h"
int main() {
	Calculator calculator;
	try {
		calculator.solve();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}