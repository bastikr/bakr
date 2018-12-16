#include "bakr/intpoint.h"


namespace bakr {

bool operator==(const IntPoint& a, const IntPoint& b) {
  return a.X==b.X && a.Y==b.Y;
}

bool operator!=(const IntPoint& a, const IntPoint& b) {
  return a.X!=b.X || a.Y!=b.Y;
}

}
