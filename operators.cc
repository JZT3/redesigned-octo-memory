/*          
Arithmetic Operators
  addition                  +
  subtraction               -
  multiplication            *
  division                  /
  modulus                   %

Relational and Eqaulity Operators  
  less than                 <
  greater than              >
  lt eq                     <=
  gt eq                     >=
  equality                  ==
  not equal                 !=

Logical Operators
  logical and               &&
  logical or                ||

Bitwise Operators 
  bitwise and                &
  bitwise inclusive or       |
  bitwise exclusive or (XOR) ^
  bitshift left             <<
  bitshift right            >>

Assignment operators
  assignment                =
  addition assignment       +=
  multiplication assignment *=
  division assignment       /=
  modulus assignment        %=
  insertion                 <<
  extraction                >>

Other operators
  comma operator             , (left to right associativity)
                            .*
  pointer to member        ->* 

  new             new
  delete          delete
  throw           throw

  Operand is an input value that produces a new value.
  The operation performed is denoted by the operator 

  Unary operators act on one operand. 
    increment     ++ (prefix and postfix, increase the value of numeric operand by 1)
    decrement     -- (prefix and postfix, decrease the value of numeric operand by 1)
    unary plus     + (explicitly specifiy a literal or variable as positive)
    unary minus    - (explicitly specifiy a literal or variable as negative)
    logical not    ! (negating the value of boolean expression, returns true or false)
    bitwise not    ~ (bitwise negation of integral datatypes, inverts each bit of operand)
    address of     & (return the memory address of a variable)
    dereference    * (access the value at a specific memory address)
    sizeof operator  (returns the size of operand in bytes)

    Precedence and Associativity.
    Unary has the second highest precedence after postfix operators 
    Unary are evaluated right to left

  Binary operators act on two operands (+, std::cout, std::cin, ect...)
    most of everything.

  Ternary operators act on three operands 
    conditional operator

  Nullary operators act on zero operands (throw)
*/

#include <iostream>


int main()
{
  int a {5};
  int b = -++a;  // unary precedence and associativty example
  std::cout << b << '\n';
//---------------------------
  int x {10};
  int y {20};
  int z {30};

  x = y,z; // comma operator
  std::cout << x << '\n';

  x = (y,z);
  std::cout << x << '\n';
//------------------------------



  return 0;
}
