#include "bakr/transformation.h"
#include "gtest/gtest.h"

using namespace bakr;

TEST(TRANSFORMATION, SHIFT) {
  std::vector<IntPoint> polygon {{1, -3}, {2, -3}, {0, 7}};

  auto result = shift(1, -5, polygon);

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0].X, 2);
  EXPECT_EQ(result[0].Y, -8);
  EXPECT_EQ(result[1].X, 3);
  EXPECT_EQ(result[1].Y, -8);
  EXPECT_EQ(result[2].X, 1);
  EXPECT_EQ(result[2].Y, 2);
}

TEST(TRANSFORMATION, SCALE) {
  std::vector<IntPoint> polygon {{1, -3}, {2, -3}, {0, 7}};

  auto result = scale(-1, 4, polygon);

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0].X, -1);
  EXPECT_EQ(result[0].Y, -12);
  EXPECT_EQ(result[1].X, -2);
  EXPECT_EQ(result[1].Y, -12);
  EXPECT_EQ(result[2].X, 0);
  EXPECT_EQ(result[2].Y, 28);
}

TEST(TRANSFORMATION, ROTATE90) {
  std::vector<IntPoint> polygon {{1, -3}, {2, -3}, {0, 7}};

  auto result = rotate90(polygon);

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0].X, 3);
  EXPECT_EQ(result[0].Y, 1);
  EXPECT_EQ(result[1].X, 3);
  EXPECT_EQ(result[1].Y, 2);
  EXPECT_EQ(result[2].X, -7);
  EXPECT_EQ(result[2].Y, 0);
}

TEST(TRANSFORMATION, ROTATE180) {
  std::vector<IntPoint> polygon {{1, -3}, {2, -3}, {0, 7}};

  auto result = rotate180(polygon);

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0].X, -1);
  EXPECT_EQ(result[0].Y, 3);
  EXPECT_EQ(result[1].X, -2);
  EXPECT_EQ(result[1].Y, 3);
  EXPECT_EQ(result[2].X, 0);
  EXPECT_EQ(result[2].Y, -7);
}

TEST(TRANSFORMATION, ROTATE270) {
  std::vector<IntPoint> polygon {{1, -3}, {2, -3}, {0, 7}};

  auto result = rotate270(polygon);

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0].X, -3);
  EXPECT_EQ(result[0].Y, -1);
  EXPECT_EQ(result[1].X, -3);
  EXPECT_EQ(result[1].Y, -2);
  EXPECT_EQ(result[2].X, 7);
  EXPECT_EQ(result[2].Y, 0);
}
