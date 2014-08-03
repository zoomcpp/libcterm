#ifndef linux_window_buffer_hpp_20140803_0051_34
#define linux_window_buffer_hpp_20140803_0051_34

#include "window_buffer.hpp"
#include <vector>
#include <memory>

class LinuxWindowBuffer : public virtual WindowBuffer {
public:
  LinuxWindowBuffer(const int& w, const int& h): 
    WindowBuffer(w, h), width_(w), height_(h), text_(w * h), attributes_(w * h) {}

  void write_text(const int& row, const int& col, const std::string& msg);
  void write_attr(const int& row, const int& col, const std::string& attr, const std::string::size_type msg_size);
  std::string row_text(const int& row) const;
  std::string get_row_text(const int& row);
  std::string get_row_text(const int& row, const int& clip);
private:
  unsigned int width_;
  unsigned int height_;
  std::vector<char> text_;
  std::vector<std::shared_ptr<std::string>> attributes_;
  void v_write(const int& row, const int& col, const std::string& msg, const std::string& attr) override;
  const unsigned int& v_width() const override;
  const unsigned int& v_height() const override;
  void v_fill(const Rect&, const char&) override;
  void v_set_width(const unsigned int&) override;
  void v_set_height(const unsigned int&) override;
};

#endif//linux_window_buffer_hpp_20140803_0051_34
