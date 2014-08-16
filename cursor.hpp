#ifndef cursor_hpp_20140728_1859_03
#define cursor_hpp_20140728_1859_03


#include "window.hpp"

class Cursor {
public:
  Cursor(const Window& owner) {};
  virtual ~Cursor() {}
  Cursor& move(const Point& p);
  Cursor& hide();
  Cursor& show();
  const Window& owner() const { return vconst_owner(); }
private:
  virtual void v_move(const Point& p) = 0;
  virtual void v_hide() = 0;
  virtual void v_show() = 0;
  virtual const Window& vconst_owner() const = 0;
};

#endif//cursor_hpp_20140728_1859_03
