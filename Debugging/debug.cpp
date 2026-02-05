/*
 A bug is something you thought was correct, but isn't (bad assumptions.


 To fix it 
    1) Find the root cause (the line of code not correct)
    2) Understand why the issue is occuring
    3) Determine how youll fix it
    4) Repair the issue
    5) Retest to see if you correctly solved the issue
    6) Retest to see if you did not create new errors

If you cannnot find the the bug by manually inspecting the code
  1) Try to reproduce the error:
  2) Re-run the program to gather information and narrow scope
  3) Repeat


Reproducing a problem is important. Make the problem appear in a consistent manner
you cant find an issue unless youre obseving it.

 */


/*
Debugging Tactics

  1) Comment out code
  2) Validate code flow
       Use temporary debug statements std::err (unbuffered)
       Print values
  3) Conditionalize using preprocessor directives 
       #define ENABLE_DEBUG

       #ifdef ENABLE_DEBUG
       ...
       #endif 

  4) Use a logger
      std::clog or plog.h
*/


/*
Using a Debugger

The previous simple albiet effective tactics physically alter your codem
    which can introduce new bugs,
    clutter existing code
    They also assume we can run our code to completion.
    
Vim Termdebug + gdb

*/

