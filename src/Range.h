#ifndef OCGL_RANGE_H
#define OCGL_RANGE_H

#include <iterator>
#include <vector>

/**
 * @file Range.h
 * @brief Iterator range.
 */

namespace ocgl {

  /**
   * @brief Iterator range.
   */
  template<typename Iterator>
  class Range
  {
    public:
      /**
       * @brief Constructor.
       *
       * @param begin The begin iterator.
       * @param end The end iterator.
       */
      Range(Iterator begin, Iterator end)
        : m_begin(begin), m_end(end)
      {
      }

      /**
       * @brief Get the begin iterator.
       */
      const Iterator& begin() const
      {
        return m_begin;
      }

      /**
       * @brief Get the begin iterator.
       */
      Iterator& begin()
      {
        return m_begin;
      }

      /**
       * @brief Get the end iterator.
       */
      const Iterator& end() const
      {
        return m_end;
      }

      /**
       * @brief Get the end iterator.
       */
      Iterator& end()
      {
        return m_end;
      }

      std::size_t size() const
      {
        return std::distance(m_begin, m_end);
      }

      /**
       * @brief Construct a std::vector from the range.
       */
      std::vector<typename std::iterator_traits<Iterator>::value_type> toVector() const
      {
        return std::vector<typename std::iterator_traits<Iterator>::value_type>(m_begin, m_end);
      }

    private:
      Iterator m_begin; //!< The begin iterator.
      Iterator m_end; //!< The end iterator.
  };

  /**
   * @brief Helper function to create iterator range.
   *
   * @param begin The begin iterator.
   * @param end The end iterator.
   */
  template<typename Iterator>
  Range<Iterator> makeRange(const Iterator &begin,
      const Iterator &end)
  {
    return Range<Iterator>(begin, end);
  }

} // namespace ocgl

#endif // OCGL_ITER_PAIR_H
