#include<iostream>

int main()
{
    int num = 10;
    std::string output = (num > 5) ? "num is greater than 5" : "num is less than or equal to 5";
    std::cout << output << std::endl;
}

