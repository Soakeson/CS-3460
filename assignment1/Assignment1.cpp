#include <iostream>
#include <string>
#include <format>
/* @series: takes an unsigned int; 2 = fibonacchi, 3 = tribonacchi, etc.
 * @n takes an unsigned int n; The nbonacchi number to be calculated.
 * Calculates a nbonacci number from a given n using the specified series.
 * Returns the n nbonacci number.
 */
long nbonacci(unsigned int series, unsigned int n)
{
  int x = 0;
  for (unsigned int i = 1; i <= series; i++) {
    if (i >= n) {
      return 1;
    }
    x += nbonacci(series, n - i);
  }

  return x;
}

/* @title: takes a string that is the title of the nbonacci series.
 * @series: takes an unsigned int; 2 = fibonacchi, 3 = tribonacchi, etc.
 * Calculates the ratio (F(n) / F(n-1)) of given nbonacci series. 
 */
void computeNbonacciRatio(std::string title, unsigned int series)
{  
  double diff = 1;
  double prev = 0;
  int i = 1;
  while (diff > 0.00001) {
    double curr = static_cast<double>(nbonacci(series, i + 1)) / nbonacci(series, i);
    if (curr > 1) {
      diff = std::abs(prev - curr);
    }
    prev = curr;
    i++;
  }
std::cout << std::format("{} ratio approaches {} after {} iterations \n", title, prev, i);
}

/* @title: takes a string that is the title of the nbonacci series.
 * @series: takes an unsigned int; 2 = fibonacchi, 3 = tribonacchi, etc.
 * Uses nbonacci to calculate the first 20 nbonnachi numbers in a given series.
 */
void listNbonacci(std::string title, unsigned int series) {
std::cout << std::format("--- {} Sequence  ---\n", title);
  for (unsigned int i = 1; i <= 20; i++) {
    std::cout << std::format("{} ", nbonacci(series, i)); 
  }
  std::cout << "\n";
}

int main()
{
  listNbonacci("Fibonacci", 2);
  listNbonacci("Tribonacci", 3);
  listNbonacci("Fourbonacci", 4);
  listNbonacci("Fivebonacci", 5);

  std::cout << "\n";

  computeNbonacciRatio("Fibonacci", 2);
  computeNbonacciRatio("Tribonacci", 3);
  computeNbonacciRatio("Fourbonacci", 4);
  computeNbonacciRatio("Fivebonacci", 5);
  return 0;
}
