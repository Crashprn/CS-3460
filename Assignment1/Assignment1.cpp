#include <iostream>

/// <summary>
/// Recursive function for computing the nth value of the Nbonacci sequence
/// </summary>
/// <param name="series"></param>
/// <param name="n"></param>
/// <returns>nth value of the the Nbonacci sequence</returns>
long nbonacci(unsigned int series, unsigned int n) 
{
	// if n is less than or equal to series return 1
	if (n <= series) 
	{
		return 1;
	}

	long nthNum = 0;

	// Loop for series times computing n - i Nbonacci number and add to nthNum
	for (unsigned int i = 1; i <= series; i++) 
	{
		nthNum += nbonacci(series, n - i);
	}

	return nthNum;

}

/// <summary>
/// Function that computes the ratio approached by the nth/(n-1) terms of the Nbonacci sequence
/// </summary>
/// <param name="title"></param>
/// <param name="series"></param>
void computeNbonacciRatio(std::string title, unsigned int series) 
{
	double oldRatio = 0;
	double remainder = 0;
	unsigned int count = series - 1;

	do 
	{
		double Ratio = static_cast<double>(nbonacci(series, count + 2))/ nbonacci(series, count + 1);
		remainder = std::abs(oldRatio - Ratio);
		oldRatio = Ratio;
		count++;
	} while (remainder > 0.000001);

	std::cout << title << " ratio approaches " << oldRatio << " after " << count << " iterations\n";
}



int main()
{
	// Fibonacci
	std::cout << "--- Fibonacci Sequence ---\n";
	for (int i = 1; i <= 20; i++) 
	{
		std::cout << nbonacci(2, i) << " ";
	}
	std::cout << "\n";

	// Tribonacci
	std::cout << "--- Tribinacci Sequence ---\n";
	for (int i = 1; i <= 20; i++) 
	{
		std::cout << nbonacci(3, i) << " ";
	}
	std::cout << "\n";

	// Fourbonacci
	std::cout << "--- Fourbinacci Sequence ---\n";
	for (int i = 1; i <= 20; i++) 
	{
		std::cout << nbonacci(4, i) << " ";
	}
	std::cout << "\n";

	// Fivebonacci
	std::cout << "--- Fivebinacci Sequence ---\n";
	for (int i = 1; i <= 20; i++) 
	{
		std::cout << nbonacci(5, i) << " ";
	}
	std::cout << "\n\n";

	// Compute ratios
	computeNbonacciRatio("Fibonacci", 2);
	computeNbonacciRatio("Tribonacci", 3);
	computeNbonacciRatio("Fourbonacci", 4);
	computeNbonacciRatio("Fivebonacci", 5);

	return 0;
}

