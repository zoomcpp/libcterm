#include "linux_window_buffer.hpp"

#include <cstring>

void LinuxWindowBuffer::v_write
(const int& row, const int& col, const std::string& msg, const std::string& attr)
{
  write_text(row, col, msg);
  write_attr(row, col, attr, msg.size());
}

const unsigned int& LinuxWindowBuffer::v_width() const {
  return this->width_;
}

const unsigned int& LinuxWindowBuffer::v_height() const {
  return this->height_;
}

void LinuxWindowBuffer::write_text
(const int& row, const int& col, const std::string& msg) 
{
  auto cell_pos = row * width() + col;
  auto bufsize = text_.size();
  if(cell_pos < bufsize) {
    auto cells_remaining = bufsize - cell_pos;
    auto msg_size = msg.size();
    auto copy_length = cells_remaining < msg_size ? cells_remaining : msg_size;
    const char* start = msg.c_str() + cell_pos;
    std::memcpy(text_.data() + cell_pos, start, copy_length);
  }
}

void LinuxWindowBuffer::write_attr
(const int& row, const int& col, const std::string& attr, 
const std::string::size_type msg_size) 
{
  auto attr_ptr = std::make_shared<std::string>(attr);
  auto cell_pos = row * width() + col;
  auto bufsize = attributes_.size();
  auto chars_remaining = bufsize - cell_pos;
  for(auto i = cell_pos; (i < bufsize) && (i < cell_pos + msg_size); ++i) {
    attributes_[i] = attr_ptr;
  }
}

void LinuxWindowBuffer::v_fill(const Rect& r, const char& c) {
  for(auto row = r.top(); (row < r.bottom()) && (row < height()); ++row) {
    for(auto col = r.left(); (col < r.right()) && (col < width()); ++col) {
      text_[row * width() + col] = c;
    }
  }
};

std::string LinuxWindowBuffer::get_row_text(const int& row) {
  return get_row_text(row, width());
}
std::string LinuxWindowBuffer::get_row_text(const int& row, const int& clip) {
  using namespace std;
  string strbuf;
  int start_pos = row * width();
  int end_pos = clip < width() ? clip : width();
  auto current_attr = attributes_[start_pos];
  auto previous_attr = current_attr;
  strbuf += *current_attr;
  for(int current_pos = start_pos; current_pos < end_pos; ++current_pos) {
    current_attr = attributes_[current_pos];
    if(current_attr != previous_attr) {
      previous_attr = current_attr;
      strbuf += *current_attr;
    }
    strbuf += text_[current_pos];
  }
  return strbuf;
}

void LinuxWindowBuffer::v_set_width(const unsigned int& w) {
  width_ = w;
  auto size = width_ * height_;
  text_.resize(size);
  attributes_.resize(size);
}

void LinuxWindowBuffer::v_set_height(const unsigned int& h) {
  height_ = h;
  auto size = width_ * height_;
  text_.resize(size);
  attributes_.resize(size);
}


