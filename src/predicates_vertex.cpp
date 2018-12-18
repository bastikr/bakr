#include "bakr/predicates_vertex.h"

#include "bakr/predicates.h"


namespace bakr {

namespace predicate {

bool is_visible(const EmptyVertex* a, const EmptyVertex* b, const EmptyVertex* obstacle) {
  EmptyVertex const* i0 = obstacle;
  EmptyVertex const* i1 = i0->next;
  while (i1!=obstacle) {
    if (i0!=a && i0!=b && i1!=a && i1!=b && is_intersecting(*a->point, *b->point, *i0->point, *i1->point)) {
      return false;
    }
    i0 = i1;
    i1 = i1->next;
  }
  return true;
}

bool is_visible(const EmptyVertex* a, const EmptyVertex* b) {
  EmptyVertex* i0 = a->next;
  EmptyVertex* i1 = i0->next;
  while (i1!=a) {
    if (i0!=a && i0!=b && i1!=a && i1!=b && is_intersecting(*a->point, *b->point, *i0->point, *i1->point)) {
      return false;
    }
    i0 = i1;
    i1 = i1->next;
  }
  return true;
}

bool is_diagonal(const EmptyVertex* a, const EmptyVertex* b) {
  return is_in_cone(*a->previous->point, *a->point, *a->next->point, *b->point)
      && is_in_cone(*b->previous->point, *b->point, *b->next->point, *a->point)
      && is_visible(a, b);
}

// bool is_ear(const EmptyVertex* a) {
//   return is_diagonal(a->previous, a->next);
// }

bool is_outside(const IntPoint& p0, const IntPoint& p1, const IntPoint& p2, const IntPoint& a) {
  return !(is_left_or_on(p0, p1, a) && is_left_or_on(p1, p2, a) && is_left_or_on(p2, p0, a));
}

bool is_ear(const EmptyVertex* a) {
  if (!is_in_cone(*a->previous->previous->point, *a->previous->point, *a->point, *a->next->point)) {
    return false;
  }
  const IntPoint p0 = *a->previous->point;
  const IntPoint p1 = *a->point;
  const IntPoint p2 = *a->next->point;
  EmptyVertex* v = a->next->next;
  while (v!=a->previous) {
    if (!is_outside(p0, p1, p2, *v->point) && &p0!=v->point && &p1!=v->point && &p2!=v->point) {
      return false;
    }
    v = v->next;
  }
  return true;
}

} // namespace predicate

} // namespace bakr
