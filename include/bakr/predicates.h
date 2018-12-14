#pragma once

#include "bakr/typedefs.h"


namespace bakr {

namespace predicate {

bool is_collinear(const IntPoint& a, const IntPoint& b, const IntPoint& c);
bool is_left(const IntPoint& a, const IntPoint& b, const IntPoint& c);
bool is_left_or_on(const IntPoint& a, const IntPoint& b, const IntPoint& c);
bool is_right(const IntPoint& a, const IntPoint& b, const IntPoint& c);
bool is_right_or_on(const IntPoint& a, const IntPoint& b, const IntPoint& c);

bool is_in_cone(const IntPoint& a0, const IntPoint& a1, const IntPoint& a2, const IntPoint& b);
bool is_between(const IntPoint& a, const IntPoint& b, const IntPoint& c);

bool is_intersecting_properly(const IntPoint& a, const IntPoint& b, const IntPoint& c, const IntPoint& d);
bool is_intersecting(const IntPoint& a, const IntPoint& b, const IntPoint& c, const IntPoint& d);

} // namespace predicate

} // namespace bakr
