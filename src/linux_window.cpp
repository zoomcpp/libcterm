#include "linux_window.hpp"
#include "linux_cursor.hpp"
#include "terminal.hpp"
#include <iostream>

//==============================================================================
// public operations 
//==============================================================================

LinuxWindow::LinuxWindow(const Terminal& owner) : LinuxWindow(owner, owner.rect()) {
}

LinuxWindow::LinuxWindow(const Terminal& o, const Rect& r) 
: Window(o, r), owner_(o), rect_(r), cursor_(*this) {
}

LinuxWindow::~LinuxWindow() {
}

//==============================================================================
// virtual operations
//==============================================================================

//==============================================================================
// private implementation
//==============================================================================

Rect& LinuxWindow::v_get_rect() {
  return rect_;
}

const Rect& LinuxWindow::vconst_get_rect() const {
  return rect_;
}

const Terminal& LinuxWindow::vconst_get_owner() const {
  return owner_;
}

Cursor& LinuxWindow::v_get_cursor() {
  return cursor_;
}

void LinuxWindow::v_refresh() {
  using namespace std;
  Rect target = rect();
  if(target.top() < terminal().rect().top()) {
    target.top(terminal().rect().top());
  }
  if(target.left() < terminal().rect().left()) {
    target.left(terminal().rect().left());
  }
  if(target.bottom() > terminal().rect().bottom()) {
    target.bottom(terminal().rect().bottom());
  }
  if(target.right() > terminal().rect().right()) {
    target.right(terminal().rect().right());
  }
  for(int row = target.top(); row <= target.bottom(); ++row) {
    for(int col = target.left(); col <= target.right(); ++col) {
      cout << '.';
    }
  }
}

void LinuxWindow::v_fill(const char& c) {
  buffer_.fill(c);
}
