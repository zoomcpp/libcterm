#include <cstdlib>
#include <iostream>
#include "linux_terminal.hpp"
#include "linux_window.hpp"
#include "linux_termcode.hpp"

int main() {
  using namespace std;
  LinuxTerminal term;
  term.mode(Terminal::Mode::Raw);
  Rect r = term.rect();
  cout << "Width:\t" << r.width() << endl
       << "Height:\t" << r.height() << endl
       << endl;
  auto window = term.create<LinuxWindow>(Rect(10, 10, 20, 20)).lock();
  window->fill('.');
  cout << window->render();
   window->write(0, 0, "\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", xterm::color(Colors::Bold) + xterm::color(Colors::fgGreen));
  cout << window->render();

  window->scroll_up();
  cout << window->render();
  return EXIT_SUCCESS;
};
