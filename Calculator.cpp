#include "Calculator.h"

Calculator::Calculator() {
	operations.push_back(new Add);
	operations.push_back(new Divide);
	operations.push_back(new Multiply);
	operations.push_back(new Subtract);
	operations.push_back(new Unary_subtract);
	loadLibrary();
};

void Calculator::solve() {
	std::string expression = getExpression();
	while (expression != "q") {
		parseString(expression);
		std::string result = polishNotation(expression);
		double calc = calculate(result);
		std::cout << "Result: " << calc << std::endl;
		expression = getExpression();
	}
}
Calculator::~Calculator() {
	for (auto& op : operations) {
		op->destroy();
	}
	for (auto& lib : libraries) {
		FreeLibrary(lib);
	}
}
void Calculator::loadLibrary() {
	const std::string pluginsDir = "plugins";
	const std::filesystem::path plugins{ pluginsDir };
	std::cout << "Loaded operations:" << std::endl;
	if (std::filesystem::is_directory(plugins)) {
		for (auto const& file : std::filesystem::directory_iterator{ plugins }) {
			HINSTANCE dll_handle = ::LoadLibraryA(file.path().generic_string().c_str());
			if (!dll_handle) {
				std::cout << "Unable to load DLL!\n";
				return;
			}
			Operation_factory factory_func = reinterpret_cast<Operation_factory>(
				::GetProcAddress(dll_handle, "create_operation"));
			if (!factory_func) {
				std::cout << "Unable to load create_operation from DLL!\n";
				::FreeLibrary(dll_handle);
				return;
			}
			Operation* instance = factory_func();
			std::cout << instance->getName() << std::endl;
			operations.push_back(instance);
			libraries.push_back(dll_handle);
		}
	}
}
std::string Calculator::getExpression() {
	std::string expression;
	std::cout << "Input expression: ";
	std::getline(std::cin, expression);
	return expression;
}
void Calculator::parseString(std::string& expression) {
	for (auto& op : operations) {
		replaceAll(expression, op->getName(), " " + op->getName() + " ");
	}
	replaceAll(expression, "(", " ( ");
	replaceAll(expression, ")", " ) ");
}
void Calculator::replaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}
int Calculator::getOperationPriority(std::string& operation) {
	if (operation == "(") return 1;
	for (auto& op : operations) {
		if (op->getName() == operation) {
			return op->getPriority();
		}
	}
}
void Calculator::deleteFirstLeftParenthesisAndModifyString(std::stack <std::string>& stack, std::string& polishNotationString) {
	if (stack.empty()) {
		throw std::exception("error: no matching left parenthesis");
	}
	while (stack.top() != "(") {
		polishNotationString += ' ' + stack.top();
		stack.pop();
		if (stack.empty()) {
			throw std::exception("error: no matching left parenthesis");
		}
	}
	stack.pop();
}
void Calculator::pushOperationAndModifyString(std::stack <std::string>& stack, std::string& word, std::string& polishNotationString) {
	if (stack.empty()) {
		stack.push(word);
	}
	else {
		while (!stack.empty() && getOperationPriority(stack.top()) >= getOperationPriority(word)) {
			polishNotationString += ' ' + stack.top();
			stack.pop();
		}
		stack.push(word);
	}
}
std::string Calculator::polishNotation(std::string& exp) {
	std::string polishNotation = "";
	std::stack <std::string> stack;
	std::stringstream expStream(exp);
	std::string word;
	while (expStream >> word) {
		if (std::count_if(operations.begin(), operations.end(), [&](Operation* element) { return word == element->getName(); })) {
			pushOperationAndModifyString(stack, word, polishNotation);
		}
		else if (word == ")") {
			deleteFirstLeftParenthesisAndModifyString(stack, polishNotation);
		}
		else if (word == "(") {
			stack.push(word);
		}
		else {
			polishNotation += ' ' + word;
		}
	}
	while (!stack.empty()) {
		polishNotation += ' ' + stack.top();
		stack.pop();
	}
	return polishNotation;
}
double Calculator::calculateOperation(double rightOperand, double leftOperand, std::string& operation) {
	for (auto& op : operations) {
		if (op->getName() == operation) {
			return op->func(rightOperand, leftOperand);
		}
	}
}
void Calculator::pushBinaryOperation(std::stack <std::string>& stack, std::string& word) {
	if (stack.empty()) {
		throw std::exception("error: Input Error");
	}
	double rightOperand = stod(stack.top());
	stack.pop();
	if (stack.empty()) {
		throw std::exception("error: Input Error");
	}
	double leftOperand = stod(stack.top());
	stack.pop();
	stack.push(std::to_string(calculateOperation(rightOperand, leftOperand, word)));
}
void Calculator::pushPrefixUnaryOperation(std::stack <std::string>& stack, std::string& word) {
	if (stack.empty()) {
		throw std::exception("error: Input Error");
	}
	double rightOperand = stod(stack.top());
	stack.pop();
	stack.push(std::to_string(calculateOperation(rightOperand, 0, word)));
}
void Calculator::pushPostfixUnaryOperation(std::stack <std::string>& stack, std::string& word) {
	if (stack.empty()) {
		throw std::exception("error: Input Error");
	}
	double leftOperand = stod(stack.top());
	stack.pop();
	stack.push(std::to_string(calculateOperation(0, leftOperand, word)));
}
double Calculator::calculate(std::string& exp) {
	std::stack <std::string> stack;
	std::stringstream expStream(exp);
	std::string word;
	while (expStream >> word) {
		if (std::count_if(operations.begin(), operations.end(), [&](Operation* element) {
			if (element->is_binary() == true) {
				return word == element->getName();
			}
			else {
				return false;
			}}))
		{
			pushBinaryOperation(stack, word);
		}
		else if (std::count_if(operations.begin(), operations.end(), [&](Operation* element) {
			if (element->is_binary() == false && element->is_postfix() == false) {
				return word == element->getName();
			}
			else {
				return false;
			}
			}))
		{
			pushPrefixUnaryOperation(stack, word);
		}
		else if (std::count_if(operations.begin(), operations.end(), [&](Operation* element) {
			if (element->is_binary() == false && element->is_postfix() == true) {
				return word == element->getName();
			}
			else {
				return false;
			}
			}))
		{
			pushPostfixUnaryOperation(stack, word);
		}
		else {
			stack.push(word);
		}
	}
	if (!stack.empty()) {
		return stod(stack.top());
	}
	else {
		throw std::exception("error: empty string was entered");
	}
}