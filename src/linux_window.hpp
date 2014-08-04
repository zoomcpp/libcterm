#ifndef linux_window_hpp_20140728_1553_20
#define linux_window_hpp_20140728_1553_20

#include "window.hpp"
#include "linux_cursor.hpp"
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
  typedef std::vector<char> text_buf_type;
  typedef std::vector<std::shared_ptr<std::string>> attr_buf_type;
  std::unique_ptr<text_buf_type> text_buf_ptr_;
  std::unique_ptr<attr_buf_type> attr_buf_ptr_;
  Rect rect_;
  const Terminal& owner_;
  LinuxCursor cursor_;
  const Terminal& vconst_get_owner() const override;
  Rect& v_get_rect() override;
  const Rect& vconst_get_rect() const override;
  Cursor& v_get_cursor() override; 
  std::string v_render() const override;
  void v_fill(const char&) override;
  void v_fill(const char&, const std::string&) override;
  void v_write(const int&, const int&, const std::string&) override;
  void v_write(const int&, const int&, const std::string&, const std::string&) override;
  void v_scroll_up(const int&) override; 
  void v_clear() override;
};

#endif//linux_window_hpp_20140728_1553_20
