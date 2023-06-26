#pragma once
#ifndef _BOOLLIB_H_
#define _BOOLLIB_H_

#include <cmath>
#include <regex>
#include <vector>
#include <string>
#include <algorithm>

class Boolean {
public:
	static std::string polynom(const std::string);
	static std::string simplify(const std::string str);
	static std::vector <bool> result(const std::string str);
	static std::vector <std::vector<bool>> truth_table(const std::string str);
	static std::vector <std::vector<std::string>> karnaugh(const std::string str);

private:
#define MATRIX_X sorted_table.size() / 2 + 1
#define MATRIX_Y pdnf_sorted_table.size() + 1

	static bool is_x(std::string str);
	static std::string fix_input(std::string& str);
	static std::string fix_output(std::string str);
	static std::string check_order(std::string& str);
	static bool checking_expression(std::string& str);

	static std::string solving_expression(std::string str);
	static std::string searching_bracket(std::string str, std::vector <int>& value);
	static std::vector <std::vector<bool>> build_table(std::string str, std::string sorting);

	static std::vector <std::string> sort_table(std::vector <std::vector<std::string>> table);
	static std::vector <std::vector<std::string>> build_simply_table(std::string& str, std::string sorting);
	static std::string simplifing(std::vector <std::string> sorted_table, std::string sorting, std::string str);

	static std::string zhegalkin(std::string& str);

	static std::vector <std::string> gray_code(int& size);
	static std::vector <std::vector<std::string>> build_karnaugh(std::string& str, std::string& other_order, std::string original_str);
};


bool Boolean::is_x(std::string str) {

	// Содержит ли строка x-переменные
	// Does the string contain x-variables

	if (str.find("x0") == -1)
		return false;

	return true;
}

std::string Boolean::fix_input(std::string& str) {

	std::string other_order = check_order(str);

	// Remove ' ' from str
	// Исключение ' ' из str

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			str.erase(str.begin() + i);
			i = 0;
		}
	}

	for (int i = 0; i < str.length() - 1; i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z' && str[i + 1] >= 'A' && str[i + 1] <= 'Z') || (str[i] >= 'A' && str[i] <= 'Z' && str[i + 1] == '!') || (str[i] >= '0' && str[i] <= '9' && str[i + 1] == 'x') || (str[i] >= '0' && str[i] <= '9' && str[i + 1] == '!')) {
			str.insert(str.begin() + i + 1, '*');
			i = 0;
		}
	}

	int sort = 0;
	int max = -1;

	// Conversion from x0 in A, x1 in B and etc...
	// Преобразование из x0 в A, x1 в B и т.д.

	if (!is_x(str)) {
		for (int i = 0; i < other_order.length(); i++) {
			for (int j = 0; j < str.length(); j++) {
				if (str[j] == other_order[i])
					str[j] = char(65 + i);
			}
		}
		return str;
	}

	str.push_back(' ');

	for (int i = 0; i < str.length(); i++) {

		if (str[i] >= '0' && str[i] <= '9') {
			sort = str[i] - '0';
		}
		if (str[i] >= '0' && str[i] <= '9' && str[i + 1] >= '0' && str[i + 1] <= '9') {
			sort = (str[i] - '0') * 10 + str[i + 1] - '0';
		}

		if (sort > max)
			max = sort;
	}

	std::string temp = "";

	for (int i = max; i >= 0; i--) {

		temp.push_back('A' + i);

		str = std::regex_replace(str, std::regex("x" + std::to_string(i)), temp);

		temp.pop_back();

	}

	str.pop_back();

	// Fixing AB in A*B
	// Исправление AB в A*B

	for (int i = 0; i < str.length() - 1; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z' && str[i + 1] >= 'A' && str[i + 1] <= 'Z') {
			str.insert(str.begin() + i + 1, '*');
			i = 0;
		}
	}

	return str;
}

std::string Boolean::fix_output(std::string str) {

	// Conversion from A in x0, B in x1 and etc...
	// Преобразование из A в x0, B в x1 и т.д.

	int sort = 0;
	int max = -1;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			sort = str[i] - 'A';
		}

		if (sort > max)
			max = sort;
	}

	std::string temp = "";

	for (int i = max; i >= 0; i--) {

		temp.push_back('A' + i);

		str = std::regex_replace(str, std::regex(temp), "x" + std::to_string(i));

		temp.pop_back();

	}

	return str;

}

std::string Boolean::check_order(std::string& str) {

	// Checking an expression for an alphabetical sequence.
	// Проверка выражения на наличие алфавитной последовательности.

	std::string sorting;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			if (sorting.length() == 0) {
				sorting = str[i];
				continue;
			}
			for (int j = 0; j < sorting.length(); j++) {
				if (str[i] == sorting[j])
					break;

				if (j == sorting.length() - 1)
					sorting = sorting + str[i];

			}
		}
	}

	std::sort(sorting.begin(), sorting.end());

	return sorting;
}

bool Boolean::checking_expression(std::string& str) {

	// Checking correctness of expression
	// Проверка выражения на корректность

	int count = 0;

	std::string sort_str = Boolean::check_order(str);

	for (int i = 0; i < sort_str.length() - 1; i++) {
		if (sort_str[i] + 1 != sort_str[i + 1])
			return false;
	}

	for (int i = 0; i < str.length(); i++)
		if (str[i] != '1' && str[i] != '0' && str[i] != '+' && str[i] != '*' && str[i] != '#' && str[i] != '|' && str[i] != '>' && str[i] != '^' && str[i] != '=' && str[i] != '!' && str[i] != '(' && str[i] != ')' && !(str[i] >= 'A' && str[i] <= 'Z'))
			return false;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(')
			count++;
		if (str[i] == ')')
			count--;

		if (i == 0 && (str[i] != '(' && str[i] != '!' && !(str[i] >= 'A' && str[i] < 'Z' || str[i] == '1' || str[i] == '0')))
			return false;
		if (i == str.length() - 1 && (str[i] != ')' && !(str[i] >= 'A' && str[i] < 'Z' || str[i] == '1' || str[i] == '0')))
			return false;
	}


	if (count != 0)
		return false;

	for (int i = 1; i < str.length(); i++) {
		if (((str[i] >= 'A' && str[i] < 'Z' || str[i] == '1' || str[i] == '0')) && (str[i - 1] != '+' && str[i - 1] != '*' && str[i - 1] != '|' && str[i - 1] != '#' && str[i - 1] != '=' && str[i - 1] != '>' && str[i - 1] != '^' && str[i - 1] != '!' && str[i - 1] != '('))
			return false;
		if (str[i] == '(' && ((str[i - 1] >= 'A' && str[i - 1] <= 'Z' || str[i - 1] == '1' || str[i - 1] == '0')))
			return false;
		if ((!(str[i] >= 'A' && str[i] <= 'Z' || str[i] == '1' || str[i] == '0') && str[i] != '(' && str[i] != ')' && str[i] != '!') && (!(str[i - 1] >= 'A' && str[i - 1] <= 'Z' || str[i - 1] == '1' || str[i - 1] == '0') && str[i - 1] != '(' && str[i - 1] != ')' && str[i - 1] != '!'))
			return false;
	}

	for (int i = 0; i < str.length() - 1; i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z' || str[i] == '0' || str[i] == '1') && ((str[i + 1] != '+' && str[i + 1] != '|' && str[i + 1] != '*' && str[i + 1] != '#' && str[i + 1] != '=' && str[i + 1] != '>' && str[i + 1] != '^' && str[i + 1] != ')'))) {
			return false;
		}
		if (str[i] == '(' && (!(str[i + 1] >= 'A' && str[i + 1] <= 'Z' || str[i + 1] == '0' || str[i + 1] == '1') && str[i + 1] != '!' && str[i + 1] != '(')) {
			return false;
		}

		if ((!(str[i] >= 'A' && str[i] <= 'Z' || str[i] == '1' || str[i] == '0') && str[i] != '(' && str[i] != ')' && str[i] != '!') && (!(str[i + 1] >= 'A' && str[i + 1] <= 'Z' || str[i + 1] == '1' || str[i + 1] == '0') && str[i + 1] != '(' && str[i + 1] != ')' && str[i + 1] != '!')) {
			return false;
		}
	}

	return true;
}

std::string Boolean::solving_expression(std::string str) {

	// Solving An Expression.
	// Решение Выражения.

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(')
			str.erase(i, 1);
		if (str[i] == ')')
			str.erase(i, 1);
	}

	while (str.find("!") != -1) {

		// NOT

		for (int j = 0; j < str.length(); j++) {
			if (str[j] == '!' && str[j + 1] == '0')
				str.replace(str.find("!0"), 2, "1");

			if (str[j] == '!' && str[j + 1] == '1')
				str.replace(str.find("!1"), 2, "0");
		}
	}

	while (str.find("*") != -1) {
		for (int j = 0; j < str.length(); j++) {

			// AND

			if (str[j] == '0' && str[j + 1] == '*' && str[j + 2] == '1')
				str.replace(str.find("0*1"), 3, "0");


			if (str[j] == '1' && str[j + 1] == '*' && str[j + 2] == '0')
				str.replace(str.find("1*0"), 3, "0");


			if (str[j] == '1' && str[j + 1] == '*' && str[j + 2] == '1')
				str.replace(str.find("1*1"), 3, "1");


			if (str[j] == '0' && str[j + 1] == '*' && str[j + 2] == '0')
				str.replace(str.find("0*0"), 3, "0");

		}
	}

	while (str.find("+") != -1) {
		for (int j = 0; j < str.length(); j++) {

			// OR

			if (str[j] == '0' && str[j + 1] == '+' && str[j + 2] == '1')
				str.replace(str.find("0+1"), 3, "1");


			if (str[j] == '1' && str[j + 1] == '+' && str[j + 2] == '0')
				str.replace(str.find("1+0"), 3, "1");


			if (str[j] == '1' && str[j + 1] == '+' && str[j + 2] == '1')
				str.replace(str.find("1+1"), 3, "1");


			if (str[j] == '0' && str[j + 1] == '+' && str[j + 2] == '0')
				str.replace(str.find("0+0"), 3, "0");
		}
	}

	// Logical operations without a certain order.
	// Логические операции без определённой последовательности

	while (str.find("|") != -1 || str.find("^") != -1 || str.find("#") != -1 || str.find(">") != -1 || str.find("=") != -1) {

		for (int j = 0; j < str.length(); j++) {
			// NAND

			if (str[j] == '0' && str[j + 1] == '|' && str[j + 2] == '1') {
				str.replace(str.find("0|1"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '|' && str[j + 2] == '0') {
				str.replace(str.find("1|0"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '|' && str[j + 2] == '1') {
				str.replace(str.find("1|1"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '0' && str[j + 1] == '|' && str[j + 2] == '0') {
				str.replace(str.find("0|0"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			// XOR

			if (str[j] == '0' && str[j + 1] == '^' && str[j + 2] == '1') {
				str.replace(str.find("0^1"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '^' && str[j + 2] == '0') {
				str.replace(str.find("1^0"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '^' && str[j + 2] == '1') {
				str.replace(str.find("1^1"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '0' && str[j + 1] == '^' && str[j + 2] == '0') {
				str.replace(str.find("0^0"), 3, "0");
				str = Boolean::solving_expression(str);
			}

			// NOR

			if (str[j] == '0' && str[j + 1] == '#' && str[j + 2] == '1') {
				str.replace(str.find("0#1"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '#' && str[j + 2] == '0') {
				str.replace(str.find("1#0"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '#' && str[j + 2] == '1') {
				str.replace(str.find("1#1"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '0' && str[j + 1] == '#' && str[j + 2] == '0') {
				str.replace(str.find("0#0"), 3, "1");
				str = Boolean::solving_expression(str);
			}

			// IMPLY

			if (str[j] == '0' && str[j + 1] == '>' && str[j + 2] == '1') {
				str.replace(str.find("0>1"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '>' && str[j + 2] == '0') {
				str.replace(str.find("1>0"), 3, "0");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '1' && str[j + 1] == '>' && str[j + 2] == '1') {
				str.replace(str.find("1>1"), 3, "1");
				str = Boolean::solving_expression(str);
			}


			if (str[j] == '0' && str[j + 1] == '>' && str[j + 2] == '0') {
				str.replace(str.find("0>0"), 3, "1");
				str = Boolean::solving_expression(str);
			}

			// XNOR

			if (str[j] == '0' && str[j + 1] == '=' && str[j + 2] == '1') {
				str.replace(str.find("0=1"), 3, "0");
				str = Boolean::solving_expression(str);
			}

			if (str[j] == '1' && str[j + 1] == '=' && str[j + 2] == '0') {
				str.replace(str.find("1=0"), 3, "0");
				str = Boolean::solving_expression(str);
			}

			if (str[j] == '1' && str[j + 1] == '=' && str[j + 2] == '1') {
				str.replace(str.find("1=1"), 3, "1");
				str = Boolean::solving_expression(str);
			}

			if (str[j] == '0' && str[j + 1] == '=' && str[j + 2] == '0') {
				str.replace(str.find("0=0"), 3, "1");
				str = Boolean::solving_expression(str);
			}
		}
	}

	return str;
}

std::string Boolean::searching_bracket(std::string str, std::vector <int>& value) {

	// Search for parentheses, and solve them.
	// Поиск скобок, и их решение.
	std::string help;
	std::string brackets;
	bool first = true;
	bool brackets_exist = false;
	int end = 0;
	int start = 0;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 65 && str[i] <= 90) {
			help = std::to_string(value[str[i] - 'A']);
			str[i] = help[0];
		}
		if (str[i] == '(')
			brackets_exist = true;
	}

	while (brackets_exist) {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == '(') {
				if (!first)
					break;

				start = i;
			}
			if (str[i] == ')') {
				if (first) {
					end = i;
					first = false;
				}
			}
		}

		brackets = str[start];

		for (int j = start + 1; j <= end; j++)
			brackets = brackets + str[j];

		help = brackets;

		str.replace(str.find(brackets), brackets.length(), solving_expression(help));


		first = true;

		for (int i = 0; i < str.length(); i++) {
			if (str[i] == ')')
				break;

			if (i == str.length() - 1)
				brackets_exist = false;

		}
	}

	help = str;

	str = solving_expression(help);

	return str;
}

std::vector <std::vector<bool>> Boolean::build_table(std::string str, std::string sorting) {

	// Building a truth table by int
	// Строит таблицу истинности из целочисленных переменных

	int x;
	int y;
	int count;

	x = sorting.length();

	y = pow(2, x);

	std::vector <int> value(x);

	x = x + 1;

	std::vector < std::vector <bool>> table(y);

	for (int i = 0; i < y; i++)
		table[i].resize(x);

	for (int i = 0; i < y; i++) {
		count = i;
		for (int j = x - 2; j >= 0; j--) {
			if (count % 2 == 0) {
				table[i][j] = 0;
				value[j] = 0;
			}
			else {
				table[i][j] = 1;
				value[j] = 1;
			}
			count = count / 2;
		}
		// "Sending" the values of the truth table fields for the solution
		// "Отправка" значений полей таблицы истинности для решения
		table[i][x - 1] = atoi(searching_bracket(str, value).c_str());
	}

	return table;
}

std::vector <std::vector<std::string>> Boolean::build_simply_table(std::string& str, std::string sorting) {

	// Building a truth table from string
	// Построение таблицы истинности из string

	int x;
	int y;
	int count;
	char current_symb;
	std::string exp = "";

	x = sorting.length();

	y = pow(2, x);


	std::vector <int> value(x);

	std::vector < std::vector <std::string>> table(y);

	for (int i = 0; i < y; i++)
		table[i].resize(2);

	for (int i = 0; i < y; i++) {
		count = i;
		for (int j = x - 1; j >= 0; j--) {
			if (count % 2 == 0) {
				current_symb = char('a' + j);
				exp = exp + current_symb;
				value[j] = 0;
			}
			else {
				current_symb = char('A' + j);
				exp = exp + current_symb;
				value[j] = 1;
			}
			count = count / 2;
		}
		std::reverse(exp.begin(), exp.end());
		table[i][0] = exp;
		table[i][1] = Boolean::searching_bracket(str, value);
		exp = "";
	}

	return table;
}

std::string Boolean::simplifing(std::vector <std::string> sorted_table, std::string sorting, std::string str) {

	// Simplifying the expression Quine's method.
	// Упрощение выражение методом Куайна

	int end = sorted_table.size();
	int begin = 0;
	int unic = 0;
	int unic_y = 0;
	int last_end = 0;

	std::string first_str = "";
	std::string second_str;
	std::string first_compare;
	std::string second_compare;
	std::string combo = "";


	std::vector <std::string> pdnf_sorted_table;
	std::vector <std::string> simplify_sorted_table = sorted_table;

	if (simplify_sorted_table.size() == 0)
		return "";
	if (simplify_sorted_table.size() == pow(2, sorting.length() + 1))
		return "1";

	// A pairwise comparison of equivalents (terms) in neighboring groups is performed.
	// Проводится попарное сравнение эквивалентов (терминов) в соседних группах.

	for (int i = 0; i < end; i = i + 2) {
		for (int j = begin; j < end; j = j + 2) {

			if (i == j)
				continue;

			combo = "";
			last_end = end;
			first_str = simplify_sorted_table[i];
			second_str = simplify_sorted_table[j];
			first_compare = first_str;
			second_compare = second_str;

			for (int i = 0; i < first_compare.length(); i++) {
				if (first_compare[i] >= 'a')
					first_compare[i] = first_compare[i] - 32; // -32 make a -> A
			}
			for (int i = 0; i < second_compare.length(); i++) {
				if (second_compare[i] >= 'a')
					second_compare[i] = second_compare[i] - 32;
			}

			for (int y = 0; y < first_str.length(); y++) {
				if (second_compare != first_compare)
					break;
				for (int x = 0; x < second_str.length(); x++) {
					if (first_str[y] == second_str[x])
						combo = combo + first_str[y];
				}
			}

			if (combo.length() >= first_str.length() - 1 && first_str.length() != 1) {
				simplify_sorted_table[i + 1] = "1";
				simplify_sorted_table[j + 1] = "1";
			}

			for (int n = 0; n < simplify_sorted_table.size(); n++) {
				if (combo == simplify_sorted_table[n])
					combo = "";
			}

			if (combo.length() >= first_str.length() - 1 && first_str.length() != 1) {
				simplify_sorted_table[i + 1] = "1";
				simplify_sorted_table[j + 1] = "1";
				simplify_sorted_table.push_back(combo);
				simplify_sorted_table.push_back("0");
			}
		}
		if (i == end - 2) {
			end = simplify_sorted_table.size();
			begin = last_end;
		}
	}


	// Construction of the implicant matrix
	// Построение импликантной матрицы

	for (int i = 0; i < simplify_sorted_table.size(); i++) {
		if (simplify_sorted_table[i] == "0")
			pdnf_sorted_table.push_back(simplify_sorted_table[i - 1]);
	}

	std::vector <std::vector<std::string>> impl_matrix(MATRIX_Y);

	for (int i = 0; i < MATRIX_Y; i++)
		impl_matrix[i].resize(MATRIX_X);

	for (int i = 0; i < MATRIX_Y; i++) {
		for (int j = 0; j < MATRIX_X; j++)
			impl_matrix[i][j] = "0";
	}

	for (int i = 0; i < MATRIX_Y - 1; i++)
		impl_matrix[i + 1][0] = pdnf_sorted_table[i];

	for (int i = 0; i < MATRIX_X - 1; i++)
		impl_matrix[0][i + 1] = simplify_sorted_table[i * 2];

	for (int i = 1; i < MATRIX_Y; i++) {
		for (int j = 1; j < MATRIX_X; j++) {
			unic = 0;
			first_str = impl_matrix[0][j];
			second_str = impl_matrix[i][0];
			for (int x = 0; x < first_str.length(); x++) {
				for (int y = 0; y < second_str.length(); y++) {
					if (first_str[x] == second_str[y])
						unic++;

					if (unic == second_str.length())
						impl_matrix[i][j] = "1";

				}
			}
		}
	}

	first_str = "";

	// Filling in the implicant matrix and including the expression core.
	// Заполнение импликантной матрицы и включение ядра выражения.

	std::vector <int> null_pos;

	for (int i = 1; i < MATRIX_X; i++) {
		unic = 0;
		unic_y = 0;
		for (int j = 1; j < MATRIX_Y; j++) {
			if (impl_matrix[j][i] == "1") {
				unic_y = j;
				unic++;
			}
			if (unic == 1 && j == MATRIX_Y - 1) {
				if (impl_matrix[unic_y][0] == "NULL")
					break;
				null_pos.push_back(unic_y);
				first_str = first_str + impl_matrix[unic_y][0] + "+";
				impl_matrix[unic_y][0] = "NULL";
			}
		}
	}

	int max_unic = -1;

	bool full = false;

	// Filling the expression with additional terms that close the maximum number of matrix cells.
	// Заполнение выражения дополнительными членами, которые закрывают максимальное количество ячеек матрицы.

	while (!full) {

		max_unic = -1;

		for (int i = 1; i < MATRIX_Y; i++) {

			unic = 0;

			for (int j = 1; j < MATRIX_X; j++) {
				for (int k = 0; k < null_pos.size(); k++) {

					if (null_pos[k] == i)
						break;

					if (impl_matrix[i][j] == "1" && impl_matrix[null_pos[k]][j] == "0")
						unic++;
				}
			}

			if (max_unic < unic && impl_matrix[i][0] <= impl_matrix[unic_y][0]) {
				max_unic = unic;
				unic_y = i;
			}

		}

		null_pos.push_back(unic_y);

		if(impl_matrix[unic_y][0] != "NULL")
			first_str = first_str + impl_matrix[unic_y][0] + "+";

		impl_matrix[unic_y][0] = "NULL";

		full = true;

		// Проверка целостности упрощенного выражения.
		// Checking the integrity of a simplified expression.

		for (int j = 1; j < MATRIX_X; j++) {
			for (int i = 0; i < null_pos.size(); i++)
				unic = unic + (impl_matrix[null_pos[i]][j][0] - '0');

			if (unic == 0) 
				full = false;

			unic = 0;
		}

	}

	// Transformation of expression into a normal form.
	// Трансофрмация выражения в нормальную форму.


	for (int i = 0; i < first_str.length(); i++) {
		if (first_str[i] >= 'a') {
			combo = (first_str[i] - 32);
			second_str = "!";
			first_str.replace(first_str.find(first_str[i]), 1, second_str + combo);
		}
	}

	first_str.erase(first_str.length() - 1);

	return first_str;
}

std::vector <std::string> Boolean::sort_table(std::vector <std::vector<std::string>> table) {

	// Sorts a table to get a table from truthful expressions.
	// Сортировка таблицы для получение только верных выражений

	std::vector<std::string> sorted_table(0);

	for (int i = 0; i < table.size(); i++) {
		if (table[i][1] == "1") {
			sorted_table.push_back(table[i][0]);
			sorted_table.push_back("0");
		}
	}

	return sorted_table;
}

std::string Boolean::zhegalkin(std::string& str) {

	// Creating the Zhegalkin polynomial by the triangle method
	// Создание полинома Жегалкина методом треугольника

	std::vector <bool> res = Boolean::result(str);

	int size_of_result = res.size();


	// Initializing and filling pascal's triangle
	// Инициализация и заполнение треугольника Паскаля

	bool** triangle = new bool* [size_of_result];

	for (int i = 0; i < size_of_result; i++) {
		triangle[i] = new bool[size_of_result - i];

		triangle[0][i] = res[i];
	}

	for (int i = 0; i < size_of_result; i++) {
		for (int j = 0; j < size_of_result - 1 - i; j++) {
			triangle[i + 1][j] = triangle[i][j] xor triangle[i][j + 1];
		}
	}


	std::vector <std::vector<bool>> table = Boolean::build_table(str, check_order(str));

	for (int i = 0; i < table.size(); i++) {
		table[i][table[i].size() - 1] = triangle[i][0];
	}

	for (int i = 0; i < size_of_result; i++)
		delete[] triangle[i];

	delete[] triangle;


	// Finding correspondences of terms of a polynomial and a binary notation of a number 
	// Поиск соответствий членов полинома и двоичной записи

	std::string pol = "";

	for (int i = 0; i < table.size(); i++) {


		for (int j = 0; j < table[i].size() - 1; j++) {

			if (i == 0 && table[i][table[i].size() - 1] == 1) {
				pol = pol + "1";
				break;
			}

			if (table[i][table[i].size() - 1] == 1) {

				if (table[i][j] == 1)
					pol = pol + char('A' + j);
			}

		}

		if (table[i][table[i].size() - 1] == 1)
			pol = pol + '^';

	}

	if(pol.size() > 0)
		pol.pop_back();

	return pol;

}

std::vector<std::string> Boolean::gray_code(int& size) {

	// Построение кода Грея для создания порядка двоичных кодов с единичным расстоянием Хэмминга
	// Construction of a Gray code to create an order of binary codes with a one Hamming distance

	std::vector <std::string> gray;

	gray.push_back("0");
	gray.push_back("1");

	for (int i = 2; i < (1 << size); i = i << 1) {

		for (int j = i - 1; j >= 0; j--)
			gray.push_back(gray[j]);

		for (int j = 0; j < i; j++)
			gray[j] = "0" + gray[j];

		for (int j = i; j < 2 * i; j++)
			gray[j] = "1" + gray[j];
	}

	return gray;

}

std::vector<std::vector<std::string>> Boolean::build_karnaugh(std::string& str, std::string& other_order, std::string original_str) {

	// Building a karnaugh map using Gray's code.
	// Построение карты Карно с помощью кода Грея.

	std::vector <std::vector<bool>> table = truth_table(str);

	int y_size = check_order(str).size() / 2;
	int x_size = check_order(str).size() - y_size;

	std::vector <std::vector<std::string>> table_karnaugh(pow(2, x_size) + 1);

	std::vector <std::string> x_gray = gray_code(x_size);

	std::vector <std::string> y_gray = gray_code(y_size);

	for (int i = 0; i < pow(2, x_size) + 1; i++)
		table_karnaugh[i].resize(pow(2, y_size) + 1);

	for (int i = 0; i < table_karnaugh.size() - 1; i++)
		table_karnaugh[i + 1][0] = x_gray[i];

	for (int i = 0; i < table_karnaugh[0].size() - 1; i++) {
		table_karnaugh[0][i + 1] = y_gray[i];
	}

	for (int i = check_order(str).size() / 2; i < check_order(str).size(); i++)
		table_karnaugh[0][0].push_back(check_order(str)[i]);

	table_karnaugh[0][0].push_back('\\');

	for (int i = 0; i < check_order(str).size() / 2; i++)
		table_karnaugh[0][0].push_back(check_order(str)[i]);

	if (is_x(original_str)) {
		table_karnaugh[0][0] = fix_output(table_karnaugh[0][0]);
	}
	else {
		for (int i = 0; i < other_order.length(); i++) {
			for (int j = 0; j < table_karnaugh[0][0].length(); j++) {
				if (table_karnaugh[0][0][j] == char(65 + i))
					table_karnaugh[0][0][j] = char(other_order[i] + 32);
			}
		}

		for (int i = 0; i < table_karnaugh[0][0].length(); i++) {
			if (table_karnaugh[0][0][i] >= 'a' && table_karnaugh[0][0][i] <= 'z')
				table_karnaugh[0][0][i] = char(table_karnaugh[0][0][i] - 32);
		}
	}

	std::string temp;
	int pos_in_truth = 0;

	for (int i = 1; i < table_karnaugh.size(); i++) {
		for (int j = 1; j < table_karnaugh[0].size(); j++) {

			temp = temp + table_karnaugh[0][j];

			temp = temp + table_karnaugh[i][0];

			for (int k = 0; k < temp.size(); k++)
				pos_in_truth = pos_in_truth + (temp[k] - '0') * pow(2, temp.size() - k - 1);

			if (table[pos_in_truth][table[0].size() - 1] == 0)
				table_karnaugh[i][j] = '0';
			else
				table_karnaugh[i][j] = '1';

			temp = "";
			pos_in_truth = 0;
		}
	}

	return table_karnaugh;
}

// Visible method.
// Видимые методы.

std::string Boolean::polynom(const std::string str) {

	// Creating the Zhegalkin polynomial by the triangle method
	// Создание полинома Жегалкина методом треугольника

	std::string input = str;
	std::string other_order = check_order(input);

	input = fix_input(input);

	if (!checking_expression(input))
		throw std::exception("Error in the expression");

	// Error in the expression
	// Ошибка в выражении

	if (!is_x(str)) {

		input = zhegalkin(input);

		for (int i = 0; i < other_order.length(); i++) {
			for (int j = 0; j < input.length(); j++) {
				if (input[j] == char(65 + i))
					input[j] = char(other_order[i] + 32);
			}
		}

		for (int i = 0; i < input.length(); i++) {
			if (input[i] >= 'a' && input[i] <= 'z')
				input[i] = char(input[i] - 32);
		}

		return input;

	}
	else {
		return fix_output(zhegalkin(input));
	}

}

std::string Boolean::simplify(const std::string str) {

	// Return simplified expression
	// Возврат упрощенного выражения 

	std::string input = str;
	std::string other_order = check_order(input);

	input = fix_input(input);

	if (!checking_expression(input))
		throw std::exception("Error in the expression");

	// Error in the expression
	// Ошибка в выражении

	if (!is_x(str)) {
		input = simplifing(sort_table(build_simply_table(input, check_order(input))), check_order(input), input);

		for (int i = 0; i < other_order.length(); i++) {
			for (int j = 0; j < input.length(); j++) {
				if (input[j] == char(65 + i))
					input[j] = char(other_order[i] + 32);
			}
		}

		for (int i = 0; i < input.length(); i++) {
			if (input[i] >= 'a' && input[i] <= 'z')
				input[i] = char(input[i] - 32);
		}

		return input;
	}
	else {
		return fix_output(simplifing(sort_table(build_simply_table(input, check_order(input))), check_order(input), input));
	}
}

std::vector <bool> Boolean::result(const std::string str) {

	// Return only result of logical expression
	// Возврат только результата логического выражения

	std::string input = str;
	std::string other_order = check_order(input);

	input = fix_input(input);

	if (!checking_expression(input))
		throw std::exception("Error in the expression");

	// Error in the expression
	// Ошибка в выражении

	std::vector <std::vector<bool>> table = Boolean::truth_table(input);

	std::vector <bool> table_result;

	for (int i = 0; i < table.size(); i++)
		table_result.push_back(table[i][table[1].size() - 1]);

	return table_result;
}

std::vector <std::vector<bool>> Boolean::truth_table(const std::string str) {

	// Return the truth table in the vector type
	// Возврат таблицы истинности в типе vector

	std::string input = str;

	input = fix_input(input);

	if (!checking_expression(input)) {
		throw std::exception("Error in the expression");
	}

	// Error in the expression
	// Ошибка в выражении

	return Boolean::build_table(input, Boolean::check_order(input));
}

std::vector <std::vector<std::string>> Boolean::karnaugh(const std::string str) {

	// Создание карты Карно
	// Creating a karnaugh Map

	std::string input = str;
	std::string other_order = check_order(input);

	input = fix_input(input);

	if (!checking_expression(input))
		throw std::exception("Error in the expression");


	return Boolean::build_karnaugh(input, other_order, str);
	
}

#endif;
