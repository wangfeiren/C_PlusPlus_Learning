#include <iostream>

class Calculator
{
private:

public:
	Calculator() {}
	~Calculator() {}
	int Calculate(int, int, char);
	void PrimeGenerator(int, int);
};

int main()
{
	std::cout << "Hello! I'm calculator!" << std::endl;
	std::cout << "Please enter number 1 operator number 2: " << std::endl;
	int x, y, result;
	char oper;
	std::cin >> x >> oper >> y;
	Calculator c;
	result = c.Calculate(x, y, oper);

	//c.PrimeGenerator(x, y);
	std::cout << "The result is: " << result << std::endl;
	std::cin.ignore();
	std::cin.get();

	return 0;
}

int Calculator::Calculate(int x, int y, char oper)
{
	switch (oper)
	{
	case '+': return x + y;
	case '-': return x - y;
	case '*': return x * y;
	case '/': if (y != 0) return x / y; else return 0;
	default:
		return 0;
	}
}
void Calculator::PrimeGenerator(int x, int y)
{
	for (int i = 0; i < y; i++) {
		bool prime = true;
		for (int j = 2; j * j <= i; j++) {
			if (i % j == 0) {
				prime = false;
				break;
			}
		}

		if (prime == true) {
			std::cout << i << " ";
		}
	}
}
