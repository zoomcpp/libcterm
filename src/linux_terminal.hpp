#ifndef linux_terminal_hpp_20140728_1024_29
#define linux_terminal_hpp_20140728_1024_29

#include "terminal.hpp"
#include "pimpl.hpp"

class LinuxTerminal : public virtual Terminal {
public:
  LinuxTerminal();
  ~LinuxTerminal();
private:
  typedef Terminal::window_set_type window_set_type;
  
  Rect v_get_rect() const override;
  void v_set_mode(const Mode&) override;
  const window_set_type& vconst_window_set() const override;
  window_set_type& v_window_set() override;
  struct Self;
  std::unique_ptr<Self> self;
};


#endif//linux_terminal_hpp_20140728_1024_29
