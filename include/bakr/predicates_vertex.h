#pragma once

#include "bakr/typedefs.h"
#include "bakr/vertex.h"


namespace bakr {

namespace predicate {

bool is_visible(const EmptyVertex* a, const EmptyVertex* b);
bool is_diagonal(const EmptyVertex* a, const EmptyVertex* b);
bool is_ear(const EmptyVertex* a);

} // namespace predicate

} // namespace bakr
