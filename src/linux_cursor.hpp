#ifndef linux_cursor_hpp_20140728_1932_35
#define linux_cursor_hpp_20140728_1932_35

#include "cursor.hpp"
#include "pimpl.hpp"

class LinuxWindow;

class LinuxCursor : public virtual Cursor {
public:
  LinuxCursor(const LinuxWindow& owner);

private:
  typedef char* charbuf_type;
  std::unique_ptr<charbuf_type> charbuf_;
  const LinuxWindow& owner_;
  void v_move(const Point& p) override;
  void v_hide() override;
  void v_show() override;
  const Window& vconst_owner() const override;
};

#endif//linux_cursor_hpp_20140728_1932_35
