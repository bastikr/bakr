#pragma once

#include "bakr/intpoint.h"
#include "bakr/vertex.h"


namespace bakr {

namespace predicate {

bool is_visible(const IntPoint* a, const IntPoint* b, const std::vector<const IntPoint*> obstacle);
bool is_visible(const EmptyVertex* a, const EmptyVertex* b);
bool is_visible(const EmptyVertex* a, const EmptyVertex* b, const EmptyVertex* obstacle);
bool is_diagonal(const EmptyVertex* a, const EmptyVertex* b);
bool is_ear(const EmptyVertex* a);

} // namespace predicate

} // namespace bakr
