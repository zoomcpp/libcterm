#include "linux_terminal.hpp"
#include <termio.h>
#include <unistd.h>
#include <cstring>

//==============================================================================
// PIMPL
//==============================================================================
struct LinuxTerminal::Self {
  //*** construction
  Self(LinuxTerminal& o) : owner(o) {
  }
  //*** private data 
  LinuxTerminal& owner;
  termio saved_term_params;
  termio current_term_params;
  LinuxTerminal::window_set_type window_set;
  //*** private operations
  void terminal_params_save();
  void terminal_params_restore();
};

//==============================================================================
// public operations
//==============================================================================

LinuxTerminal::LinuxTerminal() : self(new Self(*this)) {
  // save current terminal params
  self->terminal_params_save();
}

LinuxTerminal::~LinuxTerminal() {
  // restore terminal params
  self->terminal_params_restore();
}

void LinuxTerminal::v_set_mode(const Mode& m) {
  // set the current mode 
  switch(m) {
  case Mode::Raw:
//    set_raw_mode();
    break;
  case Mode::Processed:
//    set_processed_mode();
    break;
  };
}

//==============================================================================
// virtual operations
//==============================================================================
Rect LinuxTerminal::v_get_rect() const {
  winsize sz;
  if(ioctl(STDIN_FILENO, TIOCGWINSZ, &sz) == -1) {
    throw std::runtime_error("could not get screen size; ioctl failed TIOCGWINSZ");
  }
  return Rect(0, 
              0, 
              static_cast<int>(sz.ws_col) - 1,
              static_cast<int>(sz.ws_row) - 1);
}

LinuxTerminal::window_set_type& LinuxTerminal::v_window_set() {
  return self->window_set;
}

const LinuxTerminal::window_set_type& LinuxTerminal::vconst_window_set() const {
  return self->window_set;
}
//==============================================================================
// PRIVATE IMPLEMENTATION
//==============================================================================
void LinuxTerminal::Self::terminal_params_save() {
  if(ioctl(STDIN_FILENO, TCGETA, &(saved_term_params)) == -1) {
    throw std::runtime_error("could not save TTY state");
  }
}

void LinuxTerminal::Self::terminal_params_restore() {
  if(ioctl(STDIN_FILENO, TCSETA, &(saved_term_params)) == -1) {
    throw std::runtime_error("could not restore TTY state");
  }
}
