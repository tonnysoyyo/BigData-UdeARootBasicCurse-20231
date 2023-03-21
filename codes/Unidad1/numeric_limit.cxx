// numeric_limits example
#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

int main () {
  std::cout << std::boolalpha;
  std::cout << "Minimum value for int: " << std::numeric_limits<int>::min() << '\n';
  std::cout << "Maximum value for int: " << std::numeric_limits<int>::max() << '\n';
  std::cout << "Minimum value for long int: " << std::numeric_limits<long int>::min() << '\n';
  std::cout << "Maximum value for long int: " << std::numeric_limits<long int>::max() << '\n';
  return 0;
}
