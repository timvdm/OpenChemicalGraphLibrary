#include <ocgl/BitMatrix.h>

#include <gtest/gtest.h>

TEST(BitMatrixTest, Constructor1)
{
  ocgl::BitMatrix m(5);

  EXPECT_EQ(0, m.rows());
  EXPECT_EQ(5, m.cols());
}

TEST(BitMatrixTest, Constructor2)
{
  ocgl::BitMatrix m(4, 5);

  EXPECT_EQ(4, m.rows());
  EXPECT_EQ(5, m.cols());
}

TEST(BitMatrixTest, Constructor3)
{
  ocgl::BitMatrix m(3, 4, {
      1, 0, 1, 0,
      0, 1, 1, 0,
      1, 1, 0, 1 });

  EXPECT_EQ(3, m.rows());
  EXPECT_EQ(4, m.cols());

  EXPECT_EQ(1, m.get(0, 0)); EXPECT_EQ(0, m.get(0, 1)); EXPECT_EQ(1, m.get(0, 2)); EXPECT_EQ(0, m.get(0, 3));
  EXPECT_EQ(0, m.get(1, 0)); EXPECT_EQ(1, m.get(1, 1)); EXPECT_EQ(1, m.get(1, 2)); EXPECT_EQ(0, m.get(1, 3));
  EXPECT_EQ(1, m.get(2, 0)); EXPECT_EQ(1, m.get(2, 1)); EXPECT_EQ(0, m.get(2, 2)); EXPECT_EQ(1, m.get(2, 3));
}

int count_bits(const ocgl::BitMatrix &m)
{
  int result = 0;
  for (int i = 0; i < m.rows(); ++i)
    for (int j = 0; j < m.cols(); ++j)
      if (m.get(i, j))
        ++result;
  return result;
}

TEST(BitMatrixTest, SetReset)
{
  ocgl::BitMatrix m(4, 5);

  for (int i = 0; i < m.rows(); ++i)
    for (int j = 0; j < m.cols(); ++j) {
      EXPECT_EQ(0, count_bits(m));
      m.set(i, j);
      EXPECT_EQ(1, count_bits(m));
      m.reset(i, j);
      EXPECT_EQ(0, count_bits(m));
    }
}

TEST(BitMatrixTest, AddRow)
{
  ocgl::BitMatrix m(4, 5);

  EXPECT_EQ(4, m.rows());
  EXPECT_EQ(5, m.cols());

  m.addRow();
  EXPECT_EQ(5, m.rows());
  EXPECT_EQ(5, m.cols());

  m.addRow();
  EXPECT_EQ(6, m.rows());
  EXPECT_EQ(5, m.cols());
}

TEST(BitMatrixTest, PopRow)
{
  ocgl::BitMatrix m(4, 5);

  EXPECT_EQ(4, m.rows());
  EXPECT_EQ(5, m.cols());

  m.popRow();
  EXPECT_EQ(3, m.rows());
  EXPECT_EQ(5, m.cols());

  m.popRow();
  EXPECT_EQ(2, m.rows());
  EXPECT_EQ(5, m.cols());
}

bool row_has_even_bits_set(const ocgl::BitMatrix &m, int row)
{
  for (int i = 0; i < m.cols(); ++i)
    if ((i % 2 == 0) != m.get(row, i))
      return false;
  return true;
}

bool row_has_odd_bits_set(const ocgl::BitMatrix &m, int row)
{
  for (int i = 0; i < m.cols(); ++i)
    if ((i % 2 == 1) != m.get(row, i))
      return false;
  return true;
}

bool row_has_no_bits_set(const ocgl::BitMatrix &m, int row)
{
  for (int i = 0; i < m.cols(); ++i)
    if (m.get(row, i))
      return false;
  return true;
}

bool row_has_all_bits_set(const ocgl::BitMatrix &m, int row)
{
  for (int i = 0; i < m.cols(); ++i)
    if (!m.get(row, i))
      return false;
  return true;
}

// # bits < 1 block
TEST(BitMatrixTest, SwapRows1)
{
  ocgl::BitMatrix m(3, 50);

  // set even bits on row 0
  for (int i = 0; i < m.cols(); i += 2)
    m.set(0, i);
  // set odd bits on row 2
  for (int i = 1; i < m.cols(); i += 2)
    m.set(2, i);

  EXPECT_TRUE(row_has_even_bits_set(m, 0));
  EXPECT_TRUE(row_has_no_bits_set(m, 1));
  EXPECT_TRUE(row_has_odd_bits_set(m, 2));

  // swap 0 <-> 2
  m.swapRows(0, 2);

  EXPECT_TRUE(row_has_odd_bits_set(m, 0));
  EXPECT_TRUE(row_has_no_bits_set(m, 1));
  EXPECT_TRUE(row_has_even_bits_set(m, 2));
}

// # bits > 1 block
TEST(BitMatrixTest, SwapRows2)
{
  ocgl::BitMatrix m(3, 80);

  // set even bits on row 0
  for (int i = 0; i < m.cols(); i += 2)
    m.set(0, i);
  // set odd bits on row 2
  for (int i = 1; i < m.cols(); i += 2)
    m.set(2, i);

  EXPECT_TRUE(row_has_even_bits_set(m, 0));
  EXPECT_TRUE(row_has_no_bits_set(m, 1));
  EXPECT_TRUE(row_has_odd_bits_set(m, 2));

  // swap 0 <-> 2
  m.swapRows(0, 2);

  EXPECT_TRUE(row_has_odd_bits_set(m, 0));
  EXPECT_TRUE(row_has_no_bits_set(m, 1));
  EXPECT_TRUE(row_has_even_bits_set(m, 2));
}

// # bits == 1 block
TEST(BitMatrixTest, SwapRows3)
{
  ocgl::BitMatrix m(3, sizeof(ocgl::BitMatrix::Block) * ocgl::BitMatrix::BitsPerBlock);

  // set even bits on row 0
  for (int i = 0; i < m.cols(); i += 2)
    m.set(0, i);
  // set odd bits on row 2
  for (int i = 1; i < m.cols(); i += 2)
    m.set(2, i);

  EXPECT_TRUE(row_has_even_bits_set(m, 0));
  EXPECT_TRUE(row_has_no_bits_set(m, 1));
  EXPECT_TRUE(row_has_odd_bits_set(m, 2));

  // swap 0 <-> 2
  m.swapRows(0, 2);

  EXPECT_TRUE(row_has_odd_bits_set(m, 0));
  EXPECT_TRUE(row_has_no_bits_set(m, 1));
  EXPECT_TRUE(row_has_even_bits_set(m, 2));
}

TEST(BitMatrixTest, Eliminate1)
{
  ocgl::BitMatrix m(3, 4, {
      1, 1, 0, 0,
      0, 0, 1, 1,
      1, 1, 1, 1 });

  EXPECT_EQ(2, m.eliminate());
}

TEST(BitMatrixTest, Eliminate2)
{
  ocgl::BitMatrix m(4, 4, {
      1, 1, 1, 1,
      1, 1, 0, 0,
      0, 0, 1, 1 });

  EXPECT_EQ(2, m.eliminate());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

