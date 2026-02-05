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


/*
 How To Design A Program

 1) Define your goal in a sentence or 2. express it as a user facing outcome.
 2) Think about your requirements/restraints and capabilities the program must exhibit to meet user needs (focus on what not how)
 3) Define tools/targets/tests
 4) Break down problem into smaller subproblems
 5) Sequence the completion 
 6) Implementation
    a) Outline main function
    b) Implement each individual function
        1) Define function prototype
        2) Write the function
        3) Test the function
    c) Test the program 

Keep the program simple to start
Add features over time
Focus on one area at a time
Test each piece of code 
Dont need to perfect early code
Optimize for maintainability not performance (generally)


*/
