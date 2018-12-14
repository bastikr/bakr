#include "bakr/predicates.h"
#include "gtest/gtest.h"

using namespace bakr::predicate;


TEST(PREDICATES, IS_LEFT) {
  EXPECT_TRUE(is_left({1, -3}, {5, 2}, {1, -2}));
  EXPECT_TRUE(is_left({1, -3}, {5, 2}, {40001, 49998}));

  EXPECT_FALSE(is_left({1, -3}, {5, 2}, {1, -3}));
  EXPECT_FALSE(is_left({1, -3}, {5, 2}, {5, 2}));
  EXPECT_FALSE(is_left({1, -3}, {5, 2}, {-3, -8}));

  EXPECT_FALSE(is_left({1, -3}, {5, 2}, {1, -4}));
  EXPECT_FALSE(is_left({1, -3}, {5, 2}, {40001, 49996}));
}

TEST(PREDICATES, IS_LEFT_OR_ON) {
  EXPECT_TRUE(is_left_or_on({1, -3}, {5, 2}, {1, -2}));
  EXPECT_TRUE(is_left_or_on({1, -3}, {5, 2}, {40001, 49998}));

  EXPECT_TRUE(is_left_or_on({1, -3}, {5, 2}, {1, -3}));
  EXPECT_TRUE(is_left_or_on({1, -3}, {5, 2}, {5, 2}));
  EXPECT_TRUE(is_left_or_on({1, -3}, {5, 2}, {-3, -8}));

  EXPECT_FALSE(is_left_or_on({1, -3}, {5, 2}, {1, -4}));
  EXPECT_FALSE(is_left_or_on({1, -3}, {5, 2}, {40001, 49996}));
}

TEST(PREDICATES, IS_RIGHT) {
  EXPECT_FALSE(is_right({1, -3}, {5, 2}, {1, -2}));
  EXPECT_FALSE(is_right({1, -3}, {5, 2}, {40001, 49998}));

  EXPECT_FALSE(is_right({1, -3}, {5, 2}, {1, -3}));
  EXPECT_FALSE(is_right({1, -3}, {5, 2}, {5, 2}));
  EXPECT_FALSE(is_right({1, -3}, {5, 2}, {-3, -8}));

  EXPECT_TRUE(is_right({1, -3}, {5, 2}, {1, -4}));
  EXPECT_TRUE(is_right({1, -3}, {5, 2}, {40001, 49996}));
}

TEST(PREDICATES, IS_RIGHT_OR_ON) {
  EXPECT_FALSE(is_right_or_on({1, -3}, {5, 2}, {1, -2}));
  EXPECT_FALSE(is_right_or_on({1, -3}, {5, 2}, {40001, 49998}));

  EXPECT_TRUE(is_right_or_on({1, -3}, {5, 2}, {1, -3}));
  EXPECT_TRUE(is_right_or_on({1, -3}, {5, 2}, {5, 2}));
  EXPECT_TRUE(is_right_or_on({1, -3}, {5, 2}, {-3, -8}));

  EXPECT_TRUE(is_right_or_on({1, -3}, {5, 2}, {1, -4}));
  EXPECT_TRUE(is_right_or_on({1, -3}, {5, 2}, {40001, 49996}));
}
