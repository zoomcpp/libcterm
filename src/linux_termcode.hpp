#ifndef linux_termcode_hpp_20140803_1102_44
#define linux_termcode_hpp_20140803_1102_44

#include <sstream>

namespace xterm {

  const char* esc() {
    return "\x1b";
  }

  const char* csi() {
    static const std::string s(std::string(esc()) + std::string("["));
    return s.c_str();
  }
  std::string move(const int& row, const int& col) {
    using namespace std;
    stringstream s;
    s << csi() << row << ";" << col << "H";
    return s.str();
  }

};

#endif//linux_termcode_hpp_20140803_1102_44
