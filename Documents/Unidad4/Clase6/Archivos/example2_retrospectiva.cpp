#include <iostream>

using namespace std;

int main() 
{
  //C++ overloaded ‘=’ operator
  char arr[] = { 'J', 'O', 'U', 'R', 'N', 'A', 'L', 'D', 'E', 'V' }; 
  string str = ""; 
  str = arr;
  cout<<"Converted char array to string:\n";
  cout << str << endl;
  cout << " "<< endl;

  //C++ String inbuilt constructor
  string str2(arr);
  cout<<"Converted char array to string:\n";
  cout <<str2<< endl; 
  
  return 0; 
} 
