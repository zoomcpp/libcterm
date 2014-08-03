#include "linux_cursor.hpp"
#include "linux_window.hpp"

LinuxCursor::LinuxCursor(const LinuxWindow& o) : Cursor(o), owner_(o) {
  
}

void LinuxCursor::v_move(const Point& p) {
  throw;
}

void LinuxCursor::v_hide() { 
  throw;
}

void LinuxCursor::v_show() {
  throw;
}

const Window& LinuxCursor::vconst_owner() const {
  return owner_;
}
