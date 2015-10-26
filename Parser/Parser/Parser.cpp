#include "Parser.h"



int Parser::findNextHook(const int& pos, const string& expr) {

	for (int i = pos + 1; i < expr.size(); i++)
		if (IS_HOOK(i))
			return i;

	return 0;
}

int Parser::findPrevHook(const int& pos, const string& expr) {

	for (int i = pos - 1; i > 0; i--)
		if (IS_HOOK(i))
			return i;

	return 0;
}

int Parser::findNextSymbol(const int& pos, const string& expr) {

	for (int i = pos + 1; i < expr.size(); i++)
		if (IS_SYMBOL(i))
			return i;

	return expr.size();
}

int Parser::findPrevSymbol(const int& pos, const string& expr) {

	for (int i = pos - 1; i > 0; i--)
		if (IS_SYMBOL(i))
			return i;

	return -1;
}

int Parser::findPrimaryExpression(string expr) {
	for (int i = 1; i < expr.size(); i++) {
		if ((expr[i] == 'x' || expr[i] == '*' || expr[i] == '/') &&
			expr[i + 1] != '(' && expr[i - 1] != ')'
			) return i;
	}
	return 0;
}

string Parser::binaryCalculation(string& expr) {

	FOR_EACH(// removing tramp brackets
		if (expr[i] == '(' || expr[i] == ')')
			expr.erase(i, 1);
	)

	int res;
	unsigned int a, b, signPos;
	string str_a, str_b, str_res;

	for (int i = 0; i < expr.size(); i++) {

		if (IS_SIGN(i))
		{
			signPos = i;

			for (int j = 0; j < signPos; j++) 
				str_a.push_back(expr[j]);
			
			for (int j = signPos + 1; j < expr.size(); j++) 
				str_b.push_back(expr[j]);
		}
	}

	if (str_a.size()>9 || str_b.size()>9)
		throw ("One of the numbers is too big"); // will do better solution
	

	a = stoi(str_a);
	b = stoi(str_b);


	switch (expr[signPos])
	{
	case '+':
		res = a + b;
		break;
	case '-':
		res = a - b;
		break;
	case 'x':case'*':
		res = a * b;
		break;
	case '/':
		if (!b) throw "Divided by zero!";
		res = a / b;
		break;
	default:
		break;
	}

	str_res = to_string(res);
	return str_res;
}

Borders Parser::findBinaryExpression(string expr) {

	Borders borders;


	for (int i = 0; i < expr.size(); i++)
	{
		if (IS_SYMBOL(i))
		{
			if (IS_HOOK(i + 1))
			{
				borders.left = i + 2;
				borders.right = findNextHook(i + 1, expr) - 1;//2
				break;
			}
			else if (IS_HOOK(i - 1))
			{
				borders.right = i - 2;
				borders.left = findPrevHook(i - 1, expr) + 1;//2
				break;
			}
			else if (expr[i] == 'x' || expr[i] == '*' || expr[i] == '/')
			{
				borders.left = findPrevSymbol(i, expr) + 1;
				borders.right = findNextSymbol(i, expr) - 1;
				break;
			}
			else if (expr[i] == '+' || expr[i] == '-')
			{
				if (findPrimaryExpression(expr)) continue;
				borders.left = findPrevSymbol(i, expr) + 1;
				borders.right = findNextSymbol(i, expr) - 1;

				break;
			}
		}
	}



	for (int i = borders.left; i <= borders.right; i++) {
		borders.expr.push_back(expr[i]);
	}

	return borders;

}

void Parser::replaceBinaryExpression(string *expr, Borders binary) {

	int hooksDeleted = 0;




	if (binary.left == 0)
	{
		expr->erase(binary.left, binary.right - binary.left + 1);
	}
	else
	{
		expr->erase(binary.left, binary.right - binary.left + 1);
	}



	if (binary.left != 0) {
		if (expr->at(binary.left - 1) == '(') {
			expr->erase(binary.left - 1, 2);
			hooksDeleted++;
		}
	}


	expr->insert(binary.left - hooksDeleted, binaryCalculation(binary.expr));


}

void Parser::deleteSpaces(string& expr) {

	for (int i = 0; i < expr.size(); ++i) 
		if (expr[i] == ' ') expr.erase(i--, 1);

}


void Parser::exceptions(string& expr)
{
	deleteSpaces(expr);

	if (!expr.size()) throw("Write something");


	for (int i = 0; i < expr.size(); ++i)
		if (IS_LETTER(i)) throw ("Invalid expression");


	if ((expr.back() < '0' || expr.back() > '9') &&
		expr.back() != '(' && expr.back() != ')')
		throw("Enter last value");


	for (int i = 0; i < expr.size(); i++)
		if ((IS_SYMBOL(i) && IS_SYMBOL(i + 1)) ||
			IS_SYMBOL(0))
			throw ("Missing argument");


	if (!checkBrackets(expr)) throw ("Check brackets");

}



int Parser::calculate(string expr) {

	exceptions(expr);

	int result = 0;

	int signCount = 0;
	for (int i = 0; i < expr.size(); i++) {
		if (IS_SIGN(i)) signCount++;
	}

	if (!signCount) return stoi(expr);

	if (signCount == 1) {
		expr = binaryCalculation(expr);
		return stoi(expr);
	}


	Borders binary = findBinaryExpression(expr);

	replaceBinaryExpression(&expr, binary);




	return calculate(expr);

}




bool Parser::checkBrackets(string& strng) {
	char openHook = '(';
	char closeHook = ')';



	int open = 0;
	int close = 0;
	char firstHook = 0;
	char lastHook = 0;

	for (int i = 0; i <= strng.size(); i++) {




		if (strng[i] == openHook) {

			if (!firstHook) {
				firstHook = openHook;
			}

			lastHook = openHook;

			open++;
		}


		if (strng[i] == closeHook) {

			if (!firstHook) {
				firstHook = closeHook;
			}

			lastHook = closeHook;

			close++;
		}

	}


	if (open == close &&
		firstHook != closeHook   &&
		lastHook != openHook)
		return true;

	return false;
}

Parser::Parser()
{
}


Parser::~Parser()
{
}
