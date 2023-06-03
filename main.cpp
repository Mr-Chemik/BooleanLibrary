#include <iostream>
#include <string>
#include <vector>
#include "boolean.h"

int main() {

	std::string input = "A>(B*C+D^E*(A+E))";

	std::vector <std::vector<bool>> vec = Boolean::truth_table(input);

	std::cout << "A B C F" << std::endl;

	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[0].size(); j++)
			std::cout << vec[i][j] << " ";
		std::cout << std::endl;
	}

	// Return the truth table in the vector type

	std::cout << std::endl << "Simplify: " << Boolean::simplify(input) << std::endl;

	// Return simplified expression

	std::cout << std::endl << "Zhegalkin polynomial: " << Boolean::polynom(input);

	// Return Zhegalkin polynomial
}
