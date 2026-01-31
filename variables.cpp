/* 
Testing IDE configurations and compiler argument settings to ensure 
everything properly displayed and working
*/

#include <iostream>

int main()
{
  int a;        // Default initialization (no initializer)


                        // Traditional initialization
  int b = 5;    // Copy initialization
  /* 
  Copy initialization is used when values are implicitly copied like when passing
  arguments to a function by value, returning from a function by value, or
  catching exceptions by value. C++17 fixed many of the previous efficiency issues
  */
  int c ( 6 );  // Direct initialization 
  /*
  Used to initialize complex objects like classes. Also used when values are
  explicitly cast to another type via static_cast
  */



                    // Modern initialization (Preferred) C++11 and greater
  int d { 7 };  // Direct-List initialization
  int e {};     // Value initialization

  // Other forms of initialization

    // Default initialization <-- undefined behavior 
    // Aggregate inititalization
    // List initialization
    // Value initialization
    // Static initialization
    // Dynamic initialization
    // Early-Dynamic initialization
    // Deferred-Dynamic initialization 
    // Reference initialization
    // Constant initialization
    // Struct initialization
    // Union initialization
    // Copy-List initialization
    // Explicit initialization
    // Implicit initialization
    // std::initializer_list


  /*
  The Reasons why modern initialization is preferred is becasue
  1) Prevents Narrowing Conversions
  2) Eliminates compiler ambiguity between inititalizing an object param vs declaring a function while specifiying return type (Most Vexing Parse)
  3) Guarantees initialization of members before the constructor body runs
  */

                  // Narrow Conversion Example
  /*
  In this example an integer can only hold non-fractional values
  Initializing an int with a fractional value requires the compiler to conver it into
  something that it can hold.
  This is a narrowing because the fractional part of the value will be lost
  */
  
  int w1 { 4.5 }; // compile error: "list-init does not allow narrowing conversion" (-Wnarrowing)
  int w2 = 4.5;   // this compiles: w2 copy-initialized to value 4
  int w3 ( 4.5 ); // this compiles: w3 direct-initalized to 4

  // It is preffered that we do not silently drop the .5. We want the compiler
  // to enforce this and not just provide a compiler warning

  w1 = 4.5;       // this compiles because copy assignment allows narrowing conversion


                        // Value-initialization and Zero initialization
  /*
  When a variable is initialized using an empty set of braces, a value initialization occurs.
  In most cases value initilaiztion will implicitly initialize the variable to zero or
  whatever value is closest to zero for a given type. 
  
  When Zeroing occurs it is referred to as zero-initialization
  */
  int x {};     // value initialization / zero-initialization to a value of zero

  // Use direct-list initialization when youre going to use the initial value of 0
  int y { 0 }; 
  std::cout << y; // using the value of 0

  // Use value initialization when the object's value is temporary and will be replaced
  int z {};
  std::cin >> z; // immediately replacing that value

  // Its best practice to just initialize all variables on its own line


  // C++ 17 introduced the "maybe unused attribute"
  /*
  There are times where we want to create programs where we might not use all values,
  but we want those variables present. The compiler provides warnings. We can tell the 
  compiler that its ok we are not using them.
  */

  [[maybe_unused]] constexpr double PI { 3.14159 }; 
  [[maybe_unused]] constexpr double GRAVITY {9.8};
  // constexpr because we might require this value to be guaranteed to be known during compilation

  // Initialization gives a variable an inital value
  // Assignment gives a variable a value after the variable is created
  

  return 0;
}
