#pragma once

#include <iostream>

using namespace std;
#pragma once
#include <string>
#include <Windows.h>
#include <stdlib.h>

using namespace std;




#define IS_SYMBOL(i) (expr[i]=='+' || expr[i]=='-' || expr[i] == '*' || expr[i] == '/')

#define IS_HOOK(i) (expr[i] == '(' || expr[i] == ')')

#define IS_SIGN(i) (IS_SYMBOL(i) || IS_HOOK(i))

#define IS_DIGIT(i) (expr[i]>='0' && expr[i]<='9')

#define IS_LETTER(i) ((expr[i] > 'a' && expr[i]<'z') ||\
						(expr[i]>'A' && expr[i] < 'Z'))

#define FOR_EACH(bla) for(int i = 0; i < expr.size(); ++i){bla}

#define MAX_UINT "4294967295"

struct Borders {
	int left, right;
	string expr;
	Borders(int left, int right) : left(left), right(right) {}
	Borders() :left(0), right(0) {}

};


class Parser
{
public:



	bool checkBrackets(string& strng);

	void deleteSpaces(string& expr);

	int findNextHook(const int& pos,const string& expr);
	int findPrevHook(const int& pos, const string& expr);
	int findNextSymbol (const int& pos, const string& expr);
	int findPrevSymbol(const int& pos, const string& expr);
	int findPrimaryExpression(string expr);

	void exceptions(string& expr);


	string binaryCalculation(string& expr);


	Borders findBinaryExpression(string expr);

	void replaceBinaryExpression(string *expr, Borders binary);



	char text[50];



	int calculate(string expr);


	Parser();
	~Parser();
};


