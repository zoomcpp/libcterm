#ifndef window_hpp_20140728_1420_22
#define window_hpp_20140728_1420_22

#include "metrics.hpp"

class Terminal;
class Cursor;


class Window {
public:
  Window(const Terminal&) {}
  Window(const Terminal&, const Rect&) {}
  virtual ~Window() {}
  const Rect& rect() const { return vconst_get_rect(); }
  const Terminal& owner() const { return vconst_get_owner(); }
  const Terminal& terminal() const { return vconst_get_owner(); }
  Cursor& cursor() { return v_get_cursor(); }
  void refresh() { return v_refresh(); }
  
  Window& fill(const char& c) {
    v_fill(c);
    return *this;
  }

private:
  virtual Cursor& v_get_cursor() = 0;
  virtual Rect& v_get_rect() = 0;
  virtual const Rect& vconst_get_rect() const = 0;
  virtual const Terminal& vconst_get_owner() const = 0;
  virtual void v_refresh() = 0;
  virtual void v_fill(const char& c) = 0;
};

#endif//window_hpp_20140728_1420_22
