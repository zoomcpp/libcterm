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
: Window(o, r), owner_(o), rect_(r), cursor_(*this), 
text_buf_ptr_(new text_buf_type(r.width() * r.height())),
attr_buf_ptr_(new attr_buf_type(r.width() * r.height())) {
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

std::string LinuxWindow::v_render() const {
  using namespace std;
  string str;
  auto text_buf = *text_buf_ptr_;
  auto attr_buf = *attr_buf_ptr_;
  auto clip_rect = clip(); 
  auto current_attr_ptr = attr_buf[0];
  auto prev_attr_ptr = current_attr_ptr;
  str += current_attr_ptr ? *current_attr_ptr : "";
  for(int row = 0; row < clip_rect.height(); ++row) {
    str += xterm::cursor_move(clip_rect.top() + row, clip_rect.left());
    for(int col = 0; col < clip_rect.width(); ++col) {
      int pos = row * rect().width() + col;
      current_attr_ptr = attr_buf[pos];
      if(current_attr_ptr != prev_attr_ptr) {
        prev_attr_ptr = current_attr_ptr;
        str += *current_attr_ptr;
      }
      str += text_buf[pos];
    }    
  }
  return str;
}

void LinuxWindow::v_fill(const char& c) {
  for(auto& bufc : *text_buf_ptr_) {
    bufc = c;
  }
}

void LinuxWindow::v_fill(const char& c, const std::string& attr) {
  using namespace std;
  // fill the text buffer with 'c'
  v_fill(c);
  // fill the attribute buffer with attr_shared
  auto attr_shared = make_shared<string>(attr);
  for(auto& bufattr : *attr_buf_ptr_) {
    bufattr = attr_shared;
  }
}

void LinuxWindow::v_write(const int& row, const int& col, const std::string& msg) {
  text_buf_type& text_buf = *text_buf_ptr_;
  int buf_pos = row * rect().width() + col;
  if(buf_pos < text_buf.size()) {
    for(int msg_pos = 0; (msg_pos < msg.size()) && ((msg_pos + buf_pos) < text_buf.size()); ++msg_pos) {
      text_buf[msg_pos + buf_pos] = msg[msg_pos]; 
    }
  }
}

void LinuxWindow::v_write(const int& row, const int& col, 
const std::string& msg, const std::string& attr) {
  v_write(row, col, msg);
  auto attr_ptr = std::make_shared<std::string>(attr);
  attr_buf_type& attr_buf = *attr_buf_ptr_;
  int buf_pos = row * rect().width() + col;
  if(buf_pos < attr_buf.size()) {
    for(int msg_pos = 0; (msg_pos < msg.size()) && ((msg_pos + buf_pos) < attr_buf.size()); ++msg_pos) {
      attr_buf[msg_pos + buf_pos] = attr_ptr; 
    }
  }
}

void LinuxWindow::v_clear() {
  for(auto& c : *text_buf_ptr_) {
    c = 0;
  }
}

void LinuxWindow::v_scroll_up(const int& lines) {
  auto text_buf = *text_buf_ptr_;
  auto attr_buf = *attr_buf_ptr_;
  if(lines >= rect().height()) {
    clear();
  } else {
    auto distance = lines * rect().width();
    auto d_last = text_buf.end();
    auto first = text_buf.begin();
    auto last = d_last - distance;
    copy_backward(first, last, d_last);
  }
}
