#include "bakr/predicates_vertex.h"

#include "bakr/predicates.h"


namespace bakr {

namespace predicate {

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

bool is_ear(const EmptyVertex* a) {
  return is_diagonal(a->previous, a->next);
}

} // namespace predicate

} // namespace bakr
