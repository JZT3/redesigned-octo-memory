#include <iostream>

int main()
{
  std::cout << "Hello World!" << '\n';
  std::cout << 6;
  
  int x { 7 };
  std::cout << x << '\n'; // we use single quotes to represent single linefeed charcters (with ASCII value 10)

  std::cout << "Hello" << " world!" << '\n';
  std::cout << "'/n'" << " is not the same as:" << "'\n'";
  std::cout << "'/n'" << " is equal to: " << "/n";
  std::cout << "x is equal to: " << x << '\n';

  /* "std::cout" is buffered. data is stored in memory and queued collecting other requests.
  when a buffer is flushed all the queud data is sent to its destination.
  We should not use "std::endl" when do not require an immediate flush of the output buffer.
  "std::endl" calls "std::flush" which forces the stream's buffer to be written immediately to 
  its destination (console, file, network socket

  The opposite of a buffered output is unbuffered output. Each inidvidual request is sent directly
  to the output. writing to a buffer is typically fast. Transferring a batch of data to an output
  is comparatively slow.
  */

  std::ostream& os = std::cout;
  os << "thanks a lot" << std::endl;
  // cout is an instance of the class ostream

  std::cout << "Enter two numbers:";
  int y {}; // define variable to hold user input and value-initialize it
  int z {}; // define variable to hold user input and value-initialize it
  std::cin >> y >> z;

  std::cout << "You entered: " << y << "and " << z << std::endl;

  /*
  "std::cin" is buffered because it allow us to separate the entering of input
  from the extract of input. 


  std::istream       = general purpose input stream class
  std::ostream       = general purpose output stream class
  std::ifstream      = Specialized file input inheriting from istream
  std::ofstream      = Specialized file output inheriting from ostream
  std::istringstream = class for input to strings in memory
  std::ostringstream = class for output to strings in memory

  Use std::istream/std::ostream primarily in function parameters.
  in the case that a function takes "std::ostream&" it can print to 
  the console "cout", a file "ofstream", or a string "ostringstream"

  Avoid using std::cout directly inside of classes or logic-heavy functions.
  Pass a stream reference instead. This allows you to redirect output to a logfile
  or test buffer without chaning logic.

  "std::istringstream" treats a "std::string" as if it were an input source like
  a file or keyboard input.

  */

  return 0;
}
