#ifndef linux_window_hpp_20140728_1553_20
#define linux_window_hpp_20140728_1553_20

#include "window.hpp"
#include "linux_cursor.hpp"
#include "linux_window_buffer.hpp"
#include "pimpl.hpp"
#include <string>
#include <vector>

class Terminal;


class LinuxWindow : public virtual Window {
public:
  explicit LinuxWindow(const Terminal& t);
  LinuxWindow(const Terminal& t, const Rect& r);
  virtual ~LinuxWindow();
private:
  LinuxWindowBuffer buffer_;
  Rect rect_;
  const Terminal& owner_;
  LinuxCursor cursor_;
  const Terminal& vconst_get_owner() const override;
  Rect& v_get_rect() override;
  const Rect& vconst_get_rect() const override;
  Cursor& v_get_cursor() override; 
  void v_refresh() override;
  void v_fill(const char& c) override;
};

#endif//linux_window_hpp_20140728_1553_20
