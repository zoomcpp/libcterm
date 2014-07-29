#ifndef metrics_hpp_20140728_1451_10
#define metrics_hpp_20140728_1451_10

class Point {
public:
  Point(const Point& p)
  : x_(p.x()), y_(p.y()) {
  }

  Point(const int& x, const int& y)
  : x_(x), y_(y) {
  }
  const int& x() const { return x_; }
  const int& y() const { return y_; }
private:
  int x_;
  int y_;
};

class Rect {
public:
  Rect(const Point& p1, const Point& p2)
  : x1_(p1.x()), x2_(p2.x()), y1_(p1.y()), y2_(p2.y()) {
  }

  Rect(const int& x1, const int& y1, const int& x2, const int& y2)
  : x1_(x1), x2_(x2), y1_(y1), y2_(y2) {    
  }

  const int& top() const {
    return y1_ < y2_ ? y1_ : y2_;
  }

  const int& bottom() const {
    return y1_ > y2_ ? y1_ : y2_;
  }

  const int& left() const {
    return x1_ < x2_ ? x1_ : x2_;
  }

  const int& right() const {
    return x1_ > x2_ ? x1_ : x2_;
  }

  Point top_left() const {
    return Point(top(), left());
  }

  Point bottom_right() const {
    return Point(bottom(), right());
  }

  int width() const {
    return right() - left() + 1;
  }
  int height() const {
    return bottom() - top() + 1;
  }
private:
  int x1_;
  int x2_;
  int y1_;
  int y2_;
 
};

#endif//metrics_hpp_20140728_1451_10