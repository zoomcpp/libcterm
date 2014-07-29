#include <cstdlib>
#include <iostream>
#include "linux_terminal.hpp"


int main() {
  using namespace std;
  LinuxTerminal term;
  Rect r = term.rect();
  cout << "Width:\t" << r.width() << endl
       << "Height:\t" << r.height() << endl;
  return EXIT_SUCCESS;
};
