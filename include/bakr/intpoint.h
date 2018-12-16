#pragma once

namespace bakr {

using IntType = int;

struct IntPoint {
  IntType X;
  IntType Y;
};

bool operator==(const IntPoint&, const IntPoint&);
bool operator!=(const IntPoint&, const IntPoint&);

} // namespace bakr
