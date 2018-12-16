#include "bakr/predicates.h"
#include "gtest/gtest.h"

using namespace bakr::predicate;


TEST(PREDICATES, IS_BETWEEN) {
  EXPECT_TRUE(is_between({2, -3}, {10, 9}, {2, -3}));
  EXPECT_TRUE(is_between({2, -3}, {10, 9}, {4, 0}));
  EXPECT_TRUE(is_between({2, -3}, {10, 9}, {6, 3}));
  EXPECT_TRUE(is_between({2, -3}, {10, 9}, {8, 6}));
  EXPECT_TRUE(is_between({2, -3}, {10, 9}, {10, 9}));

  EXPECT_FALSE(is_between({2, -3}, {10, 9}, {0, -6}));
  EXPECT_FALSE(is_between({2, -3}, {10, 9}, {4, 3}));
  EXPECT_FALSE(is_between({2, -3}, {10, 9}, {6, 0}));
  EXPECT_FALSE(is_between({2, -3}, {10, 9}, {12, 12}));
}
