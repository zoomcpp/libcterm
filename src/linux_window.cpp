#include "linux_window.hpp"
#include "terminal.hpp"

//==============================================================================
// pimpl
//==============================================================================

struct LinuxWindow::P {
  P(Terminal& t, const Rect& r);
  Terminal& terminal;
  Rect rect;
};

//==============================================================================
// public operations 
//==============================================================================

LinuxWindow::LinuxWindow(Terminal& t) : LinuxWindow(t, t.rect()) {
}

LinuxWindow::LinuxWindow(Terminal& t, const Rect& r) : p(t, r) {
}

LinuxWindow::~LinuxWindow() {
}

//==============================================================================
// virtual operations
//==============================================================================

//==============================================================================
// private implementation
//==============================================================================

LinuxWindow::P::P(Terminal& t, const Rect& r) : terminal(t), rect(r) {
}
