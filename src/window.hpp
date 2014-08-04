#ifndef window_hpp_20140728_1420_22
#define window_hpp_20140728_1420_22

#include "metrics.hpp"
#include "terminal.hpp"

class Cursor;


class Window {
public:
  Window(const Terminal&, const Rect&) {}
  virtual ~Window() {}
  const Rect& rect() const { return vconst_get_rect(); }
  Rect clip() const { return v_clip(); }
  const Terminal& owner() const { return vconst_get_owner(); }
  const Terminal& terminal() const { return vconst_get_owner(); }
  Cursor& cursor() { return v_get_cursor(); }
  std::string render() { return v_render(); }
  
  Window& fill(const char& c) {
    v_fill(c);
    return *this;
  }

  Window& fill(const char& c, const std::string& attr) {
    v_fill(c, attr);
    return *this;
  }

  Window& write(const Point& p, const std::string& msg) {
    v_write(p.y(), p.x(), msg);
    return *this;
  }

  Window& write(const Point& p, const std::string& msg, const std::string& attr) {
    v_write(p.y(), p.x(), msg, attr);
    return *this;
  }
  Window& write(const int& row, const int& col, const std::string& msg) {
    v_write(row, col, msg);
    return *this;
  }

  Window& write(const int& row, const int& col, const std::string& msg, const std::string& attr) {
    v_write(row, col, msg, attr);
    return *this;
  }

  Window& scroll_up() {
    return scroll_up(1);
  }

  Window& scroll_up(const int& n) {
    v_scroll_up(n);
    return *this;
  }

  Window& clear() {
    v_clear();
    return *this;
  }
private:
  virtual void v_clear() = 0;
  virtual Cursor& v_get_cursor() = 0;
  virtual Rect& v_get_rect() = 0;
  virtual const Rect& vconst_get_rect() const = 0;
  virtual const Terminal& vconst_get_owner() const = 0;
  virtual std::string v_render() const = 0;
  virtual void v_fill(const char& c) = 0;
  virtual void v_fill(const char& c, const std::string& attr) = 0;
  virtual void v_write(const int&, const int&, const std::string&) = 0;
  virtual void v_write(const int&, const int&, const std::string&, const std::string&) = 0; 
  virtual void v_scroll_up(const int& n) = 0;
  Rect v_clip() const {    
    return Rect(
      rect().left() > terminal().rect().left() ? rect().left() : terminal().rect().left(),
      rect().top() > terminal().rect().top() ? rect().top() : terminal().rect().top(),
      rect().right() < terminal().rect().right() ? rect().right() : terminal().rect().right(),
      rect().bottom() < terminal().rect().bottom() ? rect().bottom() : terminal().rect().bottom()
    );
  }
};

#endif//window_hpp_20140728_1420_22
