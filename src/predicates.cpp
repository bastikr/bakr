#include "bakr/predicates.h"

namespace bakr {

namespace predicate {

bool is_collinear(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  return (b.X - a.X) * (c.Y - a.Y) == (c.X - a.X) * (b.Y - a.Y);
}

bool is_left(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  return (b.X - a.X) * (c.Y - a.Y) > (c.X - a.X) * (b.Y - a.Y);
}

bool is_left_or_on(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  return (b.X - a.X) * (c.Y - a.Y) >= (c.X - a.X) * (b.Y - a.Y);
}

bool is_right(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  return (b.X - a.X) * (c.Y - a.Y) < (c.X - a.X) * (b.Y - a.Y);
}


bool is_in_cone(const IntPoint& a0, const IntPoint& a1, const IntPoint& a2, const IntPoint& b) {
  return ((int)is_left(a1, a2, b) + (int)is_left(a1, b, a0) + (int)is_left(a1, a0, a2)) > 1;
}

bool is_between(const IntPoint& a, const IntPoint& b, const IntPoint& c) {
  if (!is_collinear(a, b, c)) {
    return false;
  }
  if (a.X != b.X) {
    return ((a.X <= c.X) && (c.X <= b.X)) || ((b.X <= c.X) && (c.X <= a.X));
  } else {
    return ((a.Y <= c.Y) && (c.Y <= b.Y)) || ((b.Y <= c.Y) && (c.Y <= a.Y));
  }
}


bool is_intersecting_properly(const IntPoint& a, const IntPoint& b, const IntPoint& c, const IntPoint& d) {
  if (is_collinear(a, b, c) || is_collinear(a, b, d) || is_collinear(c, d, a) || is_collinear(c, d, b)) {
    return false;
  }
  return (is_left(a, b, c) ^ is_left(a, b, d)) && (is_left(c, d, a) ^ is_left(c, d, b));
}

bool is_intersecting(const IntPoint& a, const IntPoint& b, const IntPoint& c, const IntPoint& d) {
  if (is_intersecting_properly(a, b, c, d)) {
    return true;
  }
  return is_between(a, b, c) || is_between(a, b, d) || is_between(c, d, a) || is_between(c, d, b);
}

} // namespace predicate

} // namespace bakr
