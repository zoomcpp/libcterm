#ifndef window_hpp_20140728_1420_22
#define window_hpp_20140728_1420_22

#include "metrics.hpp"

class Terminal;

class Window {
public:
  Window() {}
  virtual ~Window() {}
  const Rect& rect() const { return v_get_rect(); }
  const Terminal& terminal() const { return v_get_terminal(); }
private:
  virtual Rect& v_get_rect() const = 0;
  virtual Terminal& v_get_terminal() const = 0;
};

#endif//window_hpp_20140728_1420_22
