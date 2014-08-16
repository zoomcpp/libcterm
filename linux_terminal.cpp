#include "linux_terminal.hpp"
#include "window.hpp"
#include <iostream>

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
  system("stty raw");
/*
  current_termio_.c_lflag &= ~ICANON;
  if(ioctl(STDIN_FILENO, TCSETA, &current_termio_) == -1) {
    throw std::runtime_error("could not set TTY mode to 'raw'");
  }
  cfmakeraw(&current_termios_);
  std::cout.sync_with_stdio(true); 
*/
}

void LinuxTerminal::set_processed_mode() {
  system("stty cooked");
/*
  current_termio_.c_lflag |= ICANON;
  if(ioctl(STDIN_FILENO, TCSETA, &current_termio_) == -1) {
    throw std::runtime_error("could not set TTY mode to 'processed'");
  }
*/
}

//==============================================================================
// virtual operations
//==============================================================================
Rect LinuxTerminal::v_get_rect() const {
  winsize sz;
  if(ioctl(STDIN_FILENO, TIOCGWINSZ, &sz) == -1) {
    throw std::runtime_error("could not get screen size; ioctl failed TIOCGWINSZ");
  }
  Rect rect;
  rect.right(static_cast<int>(sz.ws_col) - 1);
  rect.bottom(static_cast<int>(sz.ws_row) - 1);

  return rect;
}

//==============================================================================
// PRIVATE IMPLEMENTATION
//==============================================================================
void LinuxTerminal::terminal_params_save() {
  if((ioctl(STDIN_FILENO, TCGETA, &saved_termio_) == -1) ||
     (tcgetattr(STDIN_FILENO, &saved_termios_) == -1))
  {
    throw std::runtime_error("could not save TTY state");
  }
  current_termio_ = saved_termio_;
  current_termios_ = saved_termios_;
}

void LinuxTerminal::terminal_params_restore() {
  if((ioctl(STDIN_FILENO, TCSETA, &saved_termio_) == -1) ||
     (tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios_) == -1)) {
    throw std::runtime_error("could not restore TTY state");
  }
}

