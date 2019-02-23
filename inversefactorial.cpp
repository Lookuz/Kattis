#include <math.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <string>

int main() {
	std::map<int, int> preprocess;
	preprocess[1] = 1;
	preprocess[2] = 2;
	preprocess[6] = 3;
	preprocess[24] = 4;
	preprocess[120] = 5;
	preprocess[720] = 6;

	std::string input;
	int result;
	std::cin >> input;
	std::string::size_type digits = input.length();

	if (digits < 4) {
		result = preprocess[std::stoi(input)];
	} else {
		double sum = log10(720);
		for (int i = 7;; i++) {
			sum += log10(i);
			if (sum > digits) {
				result = i - 1;
				break;
			}
		}
	}

	std::cout << result << std::endl;

	return 0;
}
