#ifndef linux_window_hpp_20140728_1553_20
#define linux_window_hpp_20140728_1553_20

#include "window.hpp"
#include "pimpl.hpp"

class Terminal;

class LinuxWindow : public virtual Window {
public:
  LinuxWindow(Terminal& t);
  LinuxWindow(Terminal& t, const Rect& r);
  virtual ~LinuxWindow();
private:
  struct P;
  pimpl<P> p;
  Terminal& v_get_terminal();
  Rect& v_get_rect();
};

#endif//linux_window_hpp_20140728_1553_20
