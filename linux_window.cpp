#include "linux_window.hpp"
#include "linux_cursor.hpp"
#include "linux_termcode.hpp"
#include "debug.hpp"
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

const Terminal& LinuxWindow::v_get_owner() {
  return owner_;
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
  auto clip_rect = clip(); 
  auto current_attr_ptr = attr_buf()[0];
  auto prev_attr_ptr = current_attr_ptr;
  str += (current_attr_ptr ? *current_attr_ptr : "");
  for(int row = 0; row < clip_rect.height(); ++row) {
    str += xterm::cursor_move(rect().top() + row, rect().left());
    for(int col = 0; col < clip_rect.width(); ++col) {
      int pos = row * rect().width() + col;
      current_attr_ptr = attr_buf()[pos];
      if(current_attr_ptr != prev_attr_ptr) {
        prev_attr_ptr = current_attr_ptr;
        str += *current_attr_ptr;
      }
      str += text_buf()[pos];
    }    
  }
  str += xterm::refresh();
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
  // get a reference to the text buffer
  text_buf_type& text_buf = *text_buf_ptr_;
  // calculate the initial write position in the text buffer
  int write_pos = row * rect().width() + col;
  // bounds check
  if(write_pos < text_buf.size()) {
    // process each char in 'msg'
    for(int msg_pos = 0; 
        (msg_pos < msg.size()) && (write_pos < text_buf.size());
        ++msg_pos) 
    {
      char ch = msg[msg_pos];
      bool printable = true;
      // process special chars
      switch(ch) {
      case 0x0A:
        // <CR>
        // TODO: fix \n processing
        printable = false;
        break;
      };
      text_buf[write_pos] = ch;
      if(printable)
        ++write_pos;
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
    for(int msg_pos = 0; 
        (msg_pos < msg.size()) && ((msg_pos + buf_pos) < attr_buf.size()); 
        ++msg_pos) 
    {
      attr_buf[msg_pos + buf_pos] = attr_ptr; 
    }
  }
}

void LinuxWindow::v_scroll_up(const int& lines) {
  int segment_size = lines * rect().width();
  if(segment_size > text_buf().size()) {
    segment_size = text_buf().size();
  }
  auto begin = text_buf().begin();
  auto end = text_buf().end() - segment_size;
  auto dest = text_buf().end() + segment_size;
  std::move_backward(begin, end, dest);
}

void LinuxWindow::v_scroll_down(const int& lines) {
  int segment_size = lines * rect().width();
  if(segment_size > text_buf().size()) {
    segment_size = text_buf().size();
  }
  auto begin = text_buf().begin() + segment_size;
  auto end = text_buf().end();
  auto dest = text_buf().begin();
  std::move(begin, end, dest);
}
