#ifndef linux_terminal_hpp_20140728_1024_29
#define linux_terminal_hpp_20140728_1024_29

#include "terminal.hpp"
#include "pimpl.hpp"

class LinuxTerminal : public virtual Terminal {
public:
  LinuxTerminal();
  ~LinuxTerminal();
private:
  virtual Rect v_get_rect() const override;
  virtual void v_set_mode(const Mode&) override;
  struct P;
  pimpl<struct P> p;
};


#endif//linux_terminal_hpp_20140728_1024_29
