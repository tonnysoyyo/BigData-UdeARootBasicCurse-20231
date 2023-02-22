#include <iostream>
#include <climits>  // For INT_MIN, INT_MAX, etc.

int main() {
   std::cout << "Size of char: " << sizeof(char) << " byte" << std::endl;
   std::cout << "Size of short int: " << sizeof(short int) << " bytes" << std::endl;
   std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
   std::cout << "Size of long int: " << sizeof(long int) << " bytes" << std::endl;
   std::cout << "Size of long long int: " << sizeof(long long int) << " bytes" << std::endl;
   std::cout << "Size of float: " << sizeof(float) << " bytes" << std::endl;
   std::cout << "Size of double: " << sizeof(double) << " bytes" << std::endl;
   std::cout << "Size of long double: " << sizeof(long double) << " bytes" << std::endl;
   std::cout << "Size of bool: " << sizeof(bool) << " byte" << std::endl;
   std::cout << "Size of wchar_t: " << sizeof(wchar_t) << " bytes" << std::endl;
   std::cout << "Size of nullptr_t: " << sizeof(nullptr_t) << " bytes" << std::endl;

   return 0;
}
