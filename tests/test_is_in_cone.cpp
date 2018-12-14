#include "bakr/predicates.h"
#include "gtest/gtest.h"

using namespace bakr::predicate;


TEST(PREDICATES, IN_CONE) {
  EXPECT_TRUE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {4, -4}));
  EXPECT_TRUE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {10000, -4}));
  EXPECT_TRUE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {4, 10000}));

  EXPECT_FALSE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {2, 10000}));
  EXPECT_FALSE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {10000, -6}));
  EXPECT_FALSE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {2, -6}));

  // Reverse order
  EXPECT_FALSE(is_in_cone({4, -5}, {3, -5}, {3, -4}, {4, -4}));
  EXPECT_FALSE(is_in_cone({4, -5}, {3, -5}, {3, -4}, {10000, -4}));
  EXPECT_FALSE(is_in_cone({4, -5}, {3, -5}, {3, -4}, {4, 10000}));

  EXPECT_TRUE(is_in_cone({4, -5}, {3, -5}, {3, -4}, {2, 10000}));
  EXPECT_TRUE(is_in_cone({4, -5}, {3, -5}, {3, -4}, {10000, -6}));
  EXPECT_TRUE(is_in_cone({4, -5}, {3, -5}, {3, -4}, {2, -6}));

  // Edge cases
  EXPECT_FALSE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {3, -4}));
  EXPECT_FALSE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {3, -5}));
  EXPECT_FALSE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {4, -5}));
  EXPECT_FALSE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {3, 10000}));
  EXPECT_FALSE(is_in_cone({3, -4}, {3, -5}, {4, -5}, {10000, -5}));
}
