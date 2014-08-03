#include "linux_window.hpp"
#include "linux_cursor.hpp"
#include "linux_termcode.hpp"
#include "terminal.hpp"
#include <iostream>

//==============================================================================
// public operations 
//==============================================================================

LinuxWindow::LinuxWindow(const Terminal& owner) : LinuxWindow(owner, owner.rect()) {
}

LinuxWindow::LinuxWindow(const Terminal& o, const Rect& r) 
: Window(o, r), owner_(o), rect_(r), cursor_(*this), buffer_(r.width(), r.height()) {
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
  // figure out clipping rectangle
  Rect clip(
    rect().left(),
    rect().top(),
    terminal.rect().right() - rect().left();
    
  );
}

void LinuxWindow::v_fill(const char& c) {
  buffer_.fill(c);
}
