#ifndef terminal_hpp_20140728_1023_53
#define terminal_hpp_20140728_1023_53

#include "metrics.hpp"

class Terminal {
public:
  Terminal() {
  }
  virtual ~Terminal() {
  }
  enum class Mode {
    Raw,
    Processed
  };
  Terminal& mode(const Mode& m) {
    v_set_mode(m);
    return *this;
  }
  Rect rect() const {
    return v_get_rect();
  }
private:
  virtual void v_set_mode(const Mode& m) = 0;
  virtual Rect v_get_rect() const = 0;
};


#endif//terminal_hpp_20140728_1023_53
