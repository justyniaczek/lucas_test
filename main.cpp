#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <map>
#include <iomanip>

int decToBinSize(int dec);
std::vector<bool> decToBin(int dec);
int modulo(int a, const int b, int c);

std::vector<int> getDividers(int d);
std::vector<int> fermatAlgorithm(int a);

std::map<int, int> count(const std::vector<int>& vec);

//----------------------------------------------------

int main(int argc, char* argv[])
{
	// const int a = 1897;
	// const int b = 50498;
	// const int c = 16112;

	// int result = modulo(a, b, c);

	//------------------------------

	// std::map<int, int> numbers = count(fermatAlgorithm(78));

	// std::cout << "--------------\n";
	// for (auto i : numbers) {
	// 	std::cout << i.first << " " << i.second << "\n";
	// }

	//------------------------------

	int n = 23321;
	int q = 223;

	std::cout << "n = " << n << " i q = " << q;
	
	std::map<int, int> numbers = count(fermatAlgorithm(n - 1));

	std::cout << ", wtedy n - 1 = ";

	bool multiplySymbol = false;
	for (auto i : numbers) {
		if (multiplySymbol) {
			std::cout << " * ";
		}

		std::cout << i.first << "^" << i.second;
		multiplySymbol = true;
	}
	std::cout << " oraz:\n\n";

	bool primeNumber = true;

	int mod = modulo(q, (n - 1), n);
	std::cout << "                    " << q << "^(" << n - 1 << "   ) = " << modulo(q, (n - 1), n) << " (mod " << n << ")\n";
	if (mod != 1) {
		primeNumber = false;
	}
	
	for (auto& number : numbers) {
		int mod = modulo(q, (n - 1) / number.first, n);

		std::cout << "                    " << q << "^(" << n - 1 << "/" << std::left << std::setw(2) << number.first << ") = " << mod;
		if (mod != 1) {
			std::cout << " =/= 1 (mod " << n << ")\n";
		} else {
			std::cout << " (mod " << n << ")\n";
		}
		
		if (mod == 1) {
			primeNumber = false;
		}
	}

	if (primeNumber) {
		std::cout << "\nliczba " << n << " jest pierwsza!\n\n";
	} else {
		std::cout << "\ntest nie rozstrzyga, czy liczba " << n << " jest pierwsza.\n\n";
	}

	system("PAUSE");
	return 0;
}

//----------------------------------------------------

int decToBinSize(int dec)
{
	for (int i = 0; ; i++) {
		if (pow(2, i) > dec) {
			return i;
		}
	}
}

std::vector<bool> decToBin(int dec)
{
	int size = decToBinSize(dec);
	std::vector<bool> bin;

	for (int i = size - 1; i >= 0; i--) {
		if (pow(2, i) <= dec) {
			dec -= pow(2, i);
			bin.push_back(1);
		} else {
			bin.push_back(0);
		}
	}

	return bin;
}

int modulo(int a, const int b, int c)
{
	std::vector<bool> binB = decToBin(b);
	int binSize = decToBinSize(b);
	
	unsigned int currentNumber = a; // pow(a, 1)
	currentNumber %= c;

	unsigned int result = 1;

	if (binB[binSize - 1] == 1) {  // binb to potega zapisana w formie binarnej
		result *= currentNumber;
		result %= c;
	}

	for (int i = 1; i < binSize; i++) {
		currentNumber = pow(currentNumber, 2);
		currentNumber %= c;

		if (binB[binSize - 1 - i] == 1) {
			result *= currentNumber;
			result %= c;
		}
	}

	return result;
}

std::vector<int> getDividers(int d)
{
	// 2.
	int x = std::floor(std::sqrt(d));

	//std::cout << "2. floor(sqrt(" << d << ")) = " << x;

	if (x == std::sqrt(d)) {
		//std::cout << " = sqrt(" << d << ")\n";
	} else {
		//std::cout << " =/= sqrt(" << d << ") => x = " << x << " + 1\n";
		x++;
	}

	// 3.
	std::vector<int> dividers;

	while (x < (d + 1) / 2) {
		float powY = std::pow(x, 2) - d;
		float y = std::sqrt(powY);

		if (powY > 0 && std::floor(y) == y) {
			dividers.push_back(x + y);
			dividers.push_back(x - y);
			break;
		} else {
			x++;
		}
	}

	//if (dividers.size() > 0) {
	//	std::cout << "d = " << d << " - dividers: " << dividers[0] << " " << dividers[1] << "\n";
	//} else {
	//	std::cout << "d = " << d << " - no dividers (Prime Number)\n";
	//}

	return dividers;
}

std::vector<int> fermatAlgorithm(int a)
{
	// 1.
	int d, k;

	for (k = 0; ; k++) {
		float multiplier = a / float(pow(2, k));
		d = int(multiplier);
		
		if (multiplier == d && d % 2 == 1) {
			break;
		}
	}

	//std::cout << "1. " << a << " = " << "2^" << k << " * " << d << "\n";

	// 2. 3. 4.
	std::vector<int> primeDividers;
	for (int i = 0; i < k; i++) {
		primeDividers.push_back(2);
	}

	std::vector<int> dividers = { d };

	for (int i = 0; i < dividers.size(); i++) {
		std::vector<int> newDividers = getDividers(dividers[i]);

		if (newDividers.size() == 0) {	// jeżeli się nie dodały to jest to dzielnik pierwszy
			primeDividers.push_back(dividers[i]);
		} else {	// w przeciwnyym razie dodaje 2 nowe dzielniki do wektora dividers
			dividers.insert(dividers.end(), newDividers.begin(), newDividers.end());
		}
	}

	//std::cout << "DIVIDERS: ";
	//for (auto& divider : primeDividers) {
	//	std::cout << divider << " ";
	//}
	//std::cout << "\n";

	return primeDividers;
}

std::map<int, int> count(const std::vector<int>& vec)
{
	std::map<int, int> numbers;

	for (int i = 0; i < vec.size(); i++) {
		if (numbers.find(vec[i]) == numbers.end()) {
			numbers[vec[i]] = std::count(vec.begin(), vec.end(), vec[i]);
		}
	}

	return numbers;
}
