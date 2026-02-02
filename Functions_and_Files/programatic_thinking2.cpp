#include <iostream>

// Mediocre version
int main()
{
  std::cout << "Enter an integer: ";

  int num { };
  std::cin >> num;

  int doublenum { num * 2};

  std::cout << "Double that number is: " << doublenum << '\n';
  
  return 0;
}

/*
This manner resolves both the problems encountered in the worst solution.

The primary downside here is that we are defining a new variable which adds complexity
to store a value we only use once. 

We can do better...
*/
