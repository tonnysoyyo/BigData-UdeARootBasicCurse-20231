/*
We know we can break out of loops using the built-in break function in C++. 
Similarly, we can also break out of a whole C++ program using the exit() function.
*/

#include<iostream>
using namespace std;

int main()
{
  
  int i;
  cout<<"Enter a non-zero value: ";  //user input
  cin>>i;
  if(i)    // checks whether the user input is non-zero or not
    {
      cout<<"Valid input.\n";
    }
  else
    {
      cout<<"ERROR!" << endl;  //the program exists if the value is 0
      exit(0);
    }
  cout<<"The input was : "<<i << endl;
  
  //prime number!
  /*
  int i,num;
  cout<<"Enter the number : ";
  cin>>num;
  for(i=2;i<=num/2;i++)
    {
      if(num%i==0)
	{
	  cout<<"\nNot a prime number! \n";
	  exit(0);
	}
    }
  cout<<"\nIt is a prime number! \n";
  */
  return 0; 
}
 
