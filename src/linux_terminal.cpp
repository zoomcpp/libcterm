#include "linux_terminal.hpp"

//==============================================================================
// public operations
//==============================================================================

LinuxTerminal::LinuxTerminal() {
  // save current terminal params
  terminal_params_save();
}

LinuxTerminal::~LinuxTerminal() {
  // restore terminal params
  terminal_params_restore();
}

void LinuxTerminal::v_set_mode(const Mode& m) {
  // set the current mode 
  switch(m) {
  case Mode::Raw:
    set_raw_mode();
    break;
  case Mode::Processed:
    set_processed_mode();
    break;
  };
}

void LinuxTerminal::set_raw_mode() {
  current_term_params_.c_lflag &= ~ICANON;
  if(ioctl(STDIN_FILENO, TCSETA, &current_term_params_) == -1) {
    throw std::runtime_error("could not set TTY mode to 'raw'");
  }
}

void LinuxTerminal::set_processed_mode() {
  current_term_params_.c_lflag |= ICANON;
  if(ioctl(STDIN_FILENO, TCSETA, &current_term_params_) == -1) {
    throw std::runtime_error("could not set TTY mode to 'raw'");
  }
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
              static_cast<int>(sz.ws_row) - 1
  );
}

LinuxTerminal::window_set_type& LinuxTerminal::v_window_set() {
  return window_set_;
}

const LinuxTerminal::window_set_type& LinuxTerminal::vconst_window_set() const {
  return window_set_;
}
//==============================================================================
// PRIVATE IMPLEMENTATION
//==============================================================================
void LinuxTerminal::terminal_params_save() {
  if(ioctl(STDIN_FILENO, TCGETA, &saved_term_params_) == -1) {
    throw std::runtime_error("could not save TTY state");
  }
}

void LinuxTerminal::terminal_params_restore() {
  if(ioctl(STDIN_FILENO, TCSETA, &saved_term_params_) == -1) {
    throw std::runtime_error("could not restore TTY state");
  }
}
