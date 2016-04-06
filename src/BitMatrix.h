#ifndef OCGL_BIT_MATRIX_H
#define OCGL_BIT_MATRIX_H

#include <ocgl/Contract.h>

#include <initializer_list>
#include <iostream>
#include <vector>
#include <limits>

/**
 * @file BitMatrix.h
 * @brief A bit matrix.
 */

namespace ocgl {

  /**
   * @class BitMatrix BitMatrix.h <ocgl/BitMatrix.h>
   * @brief Matrix over GF(2).
   */
  class BitMatrix
  {
    public:
      /**
       * @brief The block type.
       */
      using Block = unsigned long;

      /**
       * @brief The number of bits per block.
       */
      static constexpr int BitsPerBlock = std::numeric_limits<Block>::digits;

      /**
       * @brief Constructor.
       *
       * This constructor creates a matrix with 0 rows.
       *
       * @param cols The number of columns.
       */
      BitMatrix(int cols) : m_rows(0), m_cols(cols)
      {
      }

      /**
       * @brief Constructor.
       *
       * @param rows The number of rows.
       * @param cols The number of columns.
       */
      BitMatrix(int rows, int cols) : m_rows(rows), m_cols(cols)
      {
        m_data.resize(rows * blocksPerRow());
      }

      /**
       * @brief Constructor.
       *
       * @param rows The number of rows.
       * @param cols The number of columns.
       * @param data The initial data.
       *
       * @pre data.size() == rows * cols
       */
      BitMatrix(int rows, int cols, std::initializer_list<bool> data)
        : m_rows(rows), m_cols(cols)
      {
        PRE_EQ(rows * cols, data.size());

        m_data.resize(rows * blocksPerRow());

        int row = 0;
        int col = 0;
        for (auto bit : data) {
          if (col == m_cols) {
            ++row;
            col = 0;
          }

          if (bit)
            set(row, col);

          ++col;
        }
      }

      /**
       * @brief Get bit in position (row,col).
       *
       * @pre row < rows()
       * @pre col < cols()
       */
      bool get(int row, int col) const
      {
        PRE_LT(row, rows());
        PRE_LT(col, cols());

        auto idx = index(row, col);
        auto block = block_index(idx);
        auto mask = block_mask(idx);
        return m_data[block] & mask;
      }

      /**
       * @brief Set the bit in position (row,col) to 1.
       *
       * @pre row < rows()
       * @pre col < cols()
       */
      void set(int row, int col)
      {
        PRE_LT(row, rows());
        PRE_LT(col, cols());

        auto idx = index(row, col);
        auto block = block_index(idx);
        auto mask = block_mask(idx);
        m_data[block] |= mask;
      }

      /**
       * @brief Set the bit in position (row,col) to 0.
       *
       * @pre row < rows()
       * @pre col < cols()
       */
      void reset(int row, int col)
      {
        PRE_LT(row, rows());
        PRE_LT(col, cols());

        auto idx = index(row, col);
        auto block = block_index(idx);
        auto mask = block_mask(idx);
        m_data[block] &= ~mask;
      }

      /**
       * @brief Add a row to the matrix.
       *
       * The row will be added below the last row.
       */
      void addRow()
      {
        ++m_rows;
        m_data.resize(m_data.size() + blocksPerRow());
      }

      /**
       * @brief Remove the last row.
       *
       * @pre rows() > 0
       */
      void popRow()
      {
        PRE_GT(rows(), 0);

        --m_rows;
        m_data.resize(m_data.size() - blocksPerRow());
      }

      /**
       * @brief Get the number of rows.
       */
      int rows() const
      {
        return m_rows;
      }

      /**
       * @brief Get the number of rows.
       */
      int cols() const
      {
        return m_cols;
      }

      /**
       * @brief Swap rows i and j.
       *
       * @param i Row index for one of the rows.
       * @param j Row index for one of the rows.
       *
       * @pre i < rows()
       * @pre j < rows()
       */
      void swapRows(int i, int j)
      {
        PRE_LT(i, rows());
        PRE_LT(j, rows());

        std::vector<Block> tmp(blocksPerRow());
        // i -> tmp
        std::copy(m_data.begin() + i * blocksPerRow(),
                  m_data.begin() + (i + 1) * blocksPerRow(),
                  tmp.begin());
        // j -> i
        std::copy(m_data.begin() + j * blocksPerRow(),
                  m_data.begin() + (j + 1) * blocksPerRow(),
                  m_data.begin() + i * blocksPerRow());
        // tmp -> j
        std::copy(tmp.begin(), tmp.end(),
                   m_data.begin() + j * blocksPerRow());
      }

      /**
       * @brief Perform XOR operation on two rows.
       *
       * <tt>row_i = row_i ^ row_j</tt>
       *
       * @param i The index for the row that will be modified.
       * @param j The row index for other row.
       */
      void xorRows(int i, int j)
      {
        auto iBlock = i * blocksPerRow();
        auto jBlock = j * blocksPerRow();
        for (auto k = 0; k < blocksPerRow(); ++k)
          m_data[iBlock + k] ^= m_data[jBlock + k];
      }

      /**
       * @brief Perform Gaussian elimination.
       *
       * @return The rank of the matrix.
       */
      int eliminate()
      {
        int x = 0;
        int y = 0;

        while (x < m_cols && y < m_rows) {
          // find the next row with a 1 in column x
          int pivot = -1;
          for (int i = y; i < m_rows; ++i)
            if (get(i, x)) {
              pivot = i;
              break;
            }

          // this column is done, continue with next column
          if (pivot < 0) {
            ++x;
            continue;
          }

          // swap rows if needed
          if (pivot != y)
            swapRows(pivot, y);

          // xor all rows below with pivot row
          for (int j = y + 1; j < m_rows; ++j)
            if (get(j, x))
              xorRows(j, y);

          // next row
          ++y;
        }

        // y is now the rank of the matrix
        return y;
      }

      /**
       * @brief Get the column index for the leading bit of a row.
       */
      int leadingBit(int row) const
      {
        auto j = 0;
        for (; j < m_cols; ++j)
          if (get(row, j))
            return j;
        return j;
      }

      /**
       * @brief Eliminate the last row of the matrix.
       *
       * Exluding the last row, the matrix is expected to be in row echelon
       * form. Additionally, the last row may not have 1 bits in columns that
       * do not have 1 bits in rows above.
       *
       * @return The rank of the matrix.
       */
      int eliminateLastRow()
      {
        for (int y = 0; y < m_rows - 1; ++y) {
          // find leading bit on current row
          int x = leadingBit(y);

          if (get(m_rows - 1, x))
            xorRows(m_rows - 1, y);
        }

        if (leadingBit(m_rows - 1) == m_cols)
          return m_rows - 1;

        return m_rows;
      }

    private:
      /**
       * @brief Get the number of blocks for a single row.
       */
      std::size_t blocksPerRow() const
      {
        std::size_t result = m_cols / BitsPerBlock;
        if (m_cols % BitsPerBlock != 0)
          ++result;
        return result;
      }

      /**
       * @brief Get the bit index in row-major orer.
       */
      std::size_t index(int row, int col) const
      {
        return  row * BitsPerBlock * blocksPerRow() + col;
      }

      /**
       * @brief Get the block index.
       *
       * @param index The bit index.
       */
      std::size_t block_index(std::size_t index) const
      {
        return index / BitsPerBlock;
      }

      /**
       * @brief Get the block mask.
       *
       * @param index The bit index.
       */
      unsigned long block_mask(std::size_t index) const
      {
        auto mod = index % BitsPerBlock;
        unsigned long result = 1;
        result <<= (BitsPerBlock - mod - 1);
        return result;
      }

      /**
       * @brief The data.
       */
      std::vector<Block> m_data;
      /**
       * @brief The number of rows.
       */
      int m_rows;
      /**
       * @brief The number of columns.
       */
      int m_cols;
  };

  /**
   * @brief STL output stream operator for BitMatrix.
   *
   * @param os The STL output stream.
   * @param m The bit matrix.
   */
  inline std::ostream& operator<<(std::ostream &os, const BitMatrix &m)
  {
    for (int i = 0; i < m.rows(); ++i) {
      os << "[ ";
      for (int j = 0; j < m.cols(); ++j)
        os << m.get(i, j) << " ";
      os << "]" << std::endl;
    }
    return os;
  }

} // namespace ocgl

#endif // OCGL_BIT_MATRIX_H
