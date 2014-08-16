#ifndef terminal_hpp_20140728_1023_53
#define terminal_hpp_20140728_1023_53

#include "metrics.hpp"
#include <memory>

class Window;

class Terminal {
public:
  /*! Default constructor. */
  Terminal() { }
  /*! Destructor. */
  virtual ~Terminal() { 
  }
  /* Terminal modes. */
  enum class Mode {
    Raw,
    Processed
  };
  /*! Change the terminal mode. */
  Terminal& mode(const Mode& m) {
    v_set_mode(m);
    return *this;
  }
  /*! Get the terminal (screen) rect. */
  Rect rect() const {
    return v_get_rect();
  }

  template<class window_type, class...Args>
  std::unique_ptr<Window> create(Args&&...args) {
    std::unique_ptr<Window> wnd(new window_type(*this, std::forward<Args>(args)...));
    return std::move(wnd);
  }

private:
  virtual void v_set_mode(const Mode& m) = 0;
  virtual Rect v_get_rect() const = 0;
};


inline bool operator<(const std::unique_ptr<Window>& lhs, const std::unique_ptr<Window>& rhs) {
  return lhs.get() < rhs.get();
}
#endif//terminal_hpp_20140728_1023_53
