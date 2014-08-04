#ifndef terminal_hpp_20140728_1023_53
#define terminal_hpp_20140728_1023_53

#include "metrics.hpp"
#include <memory>
#include <set>

class Window;

class Terminal {
public:
  /*! Default constructor. */
  Terminal() { }
  /*! Destructor. */
  virtual ~Terminal() { }
  /*! Terminal modes. */
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
  std::weak_ptr<Window> create(Args&&...args) {
    auto newwin = std::make_shared<window_type>(*this, args...);
    v_window_set().insert(newwin);
    return std::weak_ptr<Window>(newwin);
  }

  typedef std::set<std::shared_ptr<Window>> window_set_type;
  const window_set_type& window_set() const {
    return vconst_window_set();
  }

private:
  virtual void v_set_mode(const Mode& m) = 0;
  virtual Rect v_get_rect() const = 0;
  virtual const window_set_type& vconst_window_set() const = 0;
  virtual window_set_type& v_window_set() = 0;
};


inline bool operator<(const std::shared_ptr<Window>& lhs, const std::shared_ptr<Window>& rhs) {
  return lhs.get() < rhs.get();
}
#endif//terminal_hpp_20140728_1023_53
