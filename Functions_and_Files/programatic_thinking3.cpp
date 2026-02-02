#include <iostream>

// Preferred version
int main()
{
  std::cout << "Enter an integer: ";

  int num { };
  std::cin >> num;

  std::cout << "Double that number is: " << num * 2 << '\n';
  
  return 0;
}

/*
The reason why this is the preferred solution is becuase when std::cout executes,
num*2 will get evaluated. The value of num itself will not be altered so we can use 
it later again.

The first and primary goal of programming is make your program work. A program
that doesnt work isnt useful, regardless of how well its written.

"You have to write a program once to know how you should have written it the first time"


*/
