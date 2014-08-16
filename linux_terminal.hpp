#ifndef linux_terminal_hpp_20140728_1024_29
#define linux_terminal_hpp_20140728_1024_29

#include "terminal.hpp"
#include <termio.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <set>

class LinuxTerminal : public virtual Terminal {
public:
  LinuxTerminal();
  ~LinuxTerminal();
protected:
private:
  void set_raw_mode();
  void set_processed_mode();

  termio saved_termio_;
  termios saved_termios_;
  termio current_termio_;
  termios current_termios_;
  
  Rect v_get_rect() const override;
  void v_set_mode(const Mode&) override;
  void terminal_params_save();
  void terminal_params_restore();

  std::set<std::unique_ptr<Window>> window_set_;
};


#endif//linux_terminal_hpp_20140728_1024_29
