/*
Header Guards!

Header guards prevent code files from receiving more than one copy.
They do not prevent a given header file from being included once.

Pragma directives can be compiler specific except pragma once.
one pragma that works on a specific compiler may not work on another.
*/

#pragma once

int add(int x, int y); //Funtion prototype
                       
/*
 DONT DO THIS (adding function definition in headerfile

 int add(int x, int y)
 {
  return x+y;
 }
 */



/*
  Headers can include other headers.

  Transitive Includes:
    when sourcing cpp files a header file could be implicitly included. (DO NOT RELY ON THIS)
    
    It is better to explicity name all the header files youll need to compile.
   
 */



/*
 HEADER FILE BEST PRACTICE

 Always include header guards (we’ll cover these next lesson).
 Do not define variables and functions in header files (for now).
 Give a header file the same name as the source file it’s associated with
 Each header file should have a specific job, and be as independent as possible
 Be mindful of which headers you need to explicitly include for the functionality that you are using in your code files, 
   (avoid transitive includes when possible.)
 A header file should #include any other headers containing functionality it needs. 
   (Such a header should compile successfully when #included into a .cpp file by itself.)
Only #include what you need,
Do not #include *.cpp files
Put documentation in the header, or how to properly use it in the header.

 */
