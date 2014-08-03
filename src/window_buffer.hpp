#ifndef window_buffer_hpp_20140803_0057_13
#define window_buffer_hpp_20140803_0057_13

#include "metrics.hpp"
#include <string>

class WindowBuffer {
public:
  WindowBuffer(const int& w, const int& h) {}
  virtual ~WindowBuffer() {}

  const unsigned int& width() const { return v_width(); }
  WindowBuffer& width(const unsigned int& w) {
    v_set_width(w);
    return *this;
  }

  const unsigned int& height() const { return v_height(); }
  WindowBuffer& height(const unsigned int& h) {
    v_set_height(h);
    return *this;
  }

  WindowBuffer& write(const int& row, const int& col, const std::string& msg, const std::string& attr) {
    v_write(row, col, msg, attr);
    return *this;
  }

  WindowBuffer& fill(const char& c) { return fill(Rect(0, 0, width(), height()), c); }

  WindowBuffer& fill(const Rect& r, const char& c) { 
    v_fill(r, c); 
    return *this;
  }

private:
  virtual void v_write(const int& row, const int& col, const std::string& msg, const std::string& attr) = 0;
  virtual const unsigned int& v_width() const = 0;
  virtual const unsigned int& v_height() const = 0;
  virtual void v_set_width(const unsigned int&) = 0;
  virtual void v_set_height(const unsigned int&) = 0;
  virtual void v_fill(const Rect&, const char&) = 0;
};
#endif//window_buffer_hpp_20140803_0057_13
