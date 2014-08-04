#ifndef linux_termcode_hpp_20140803_1102_44
#define linux_termcode_hpp_20140803_1102_44

#include <sstream>

#include "colors.hpp"

namespace xterm {

  inline const char* esc() {
    return "\x1b";
  }

  inline const char* csi() {
    static const std::string s(std::string(esc()) + std::string("["));
    return s.c_str();
  }

  inline std::string cursor_move(const int& row, const int& col) {
    using namespace std;
    stringstream s;
    s << csi() << row << ";" << col << "H";
    return s.str();
  }

  inline std::string color(const int& c) {
    using namespace std;
    stringstream s;
    s << csi() << c << "m";
    return s.str();
  }

  inline std::string color(const Colors& color_enum) {
    return color(static_cast<int>(color_enum)); 
  }
};

#endif//linux_termcode_hpp_20140803_1102_44
