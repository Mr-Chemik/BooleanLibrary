#include <iostream>
#include <string>
#include <vector>
#include "boolean.h"

int main() {

	std::string input = "!((!A*B)>!(C+B))";

	std::vector <std::vector<bool>> vec = Boolean::truth_table(input);

	std::cout << "A B C F" << std::endl;

	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[0].size(); j++)
			std::cout << vec[i][j] << " ";
		std::cout << std::endl;
	}

	// Return the truth table in the vector type

	std::cout << std::endl << Boolean::simplify(input);

	// Return simplified expression

}
