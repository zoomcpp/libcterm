#include <cstdlib>
#include <iostream>
#include "linux_terminal.hpp"
#include "linux_window.hpp"

int main() {
  using namespace std;
  LinuxTerminal term;
  Rect r = term.rect();
  cout << "Width:\t" << r.width() << endl
       << "Height:\t" << r.height() << endl;

  auto window = term.create<LinuxWindow>().lock();
  window->fill('x');
  window->refresh();
  return EXIT_SUCCESS;
};
