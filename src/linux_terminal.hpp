#ifndef linux_terminal_hpp_20140728_1024_29
#define linux_terminal_hpp_20140728_1024_29

#include "terminal.hpp"
#include "pimpl.hpp"
#include <termio.h>
#include <unistd.h>
#include <cstring>

class LinuxTerminal : public virtual Terminal {
public:
  LinuxTerminal();
  ~LinuxTerminal();
  void set_raw_mode();
  void set_processed_mode();
protected:
private:
  termio saved_term_params_;
  termio current_term_params_;
  typedef Terminal::window_set_type window_set_type;
  window_set_type window_set_;
  
  Rect v_get_rect() const override;
  void v_set_mode(const Mode&) override;
  const window_set_type& vconst_window_set() const override;
  window_set_type& v_window_set() override;
  void terminal_params_save();
  void terminal_params_restore();
};


#endif//linux_terminal_hpp_20140728_1024_29
