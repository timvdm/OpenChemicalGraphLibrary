#ifndef OCGL_FILTER_ITERATOR_H
#define OCGL_FILTER_ITERATOR_H

#include <iterator>

/**
 * @file FilterIterator.h
 * @brief Iterator adaptor to filter vertices or edges based on a predicate.
 */

namespace ocgl {

  /**
   * @class FilterIterator FilterIterator.h <ocgl/FilterIterator.h>
   * @brief Iterator adaptor to filter vertices or edges based on a predicate.
   *
   * The FilterIterator is a wrapper around other graph iterators to filter
   * vertices or edges based on a predicate.
   */
  template<typename Graph, typename Iterator, typename Predicate>
  class FilterIterator : public std::iterator<std::forward_iterator_tag,
      typename std::iterator_traits<Iterator>::value_type>
  {
    public:
      /**
       * @brief Constructor.
       *
       * @param g The graph.
       * @param begin The begin iterator.
       * @param end The end iterator.
       * @param predicate The predicate.
       */
      FilterIterator(const Graph &g, Iterator begin, Iterator end,
          const Predicate &predicate)
        : m_graph(g), m_iter(begin), m_end(end), m_predicate(predicate)
      {
        // skip elements at the beginning for which predicate is false
        while (m_iter != m_end && !m_predicate(m_graph, *m_iter))
          ++m_iter;
      }

      /**
       * @brief Dereference operator to get adjacent vertex.
       */
      typename std::iterator_traits<Iterator>::value_type operator*() const
      {
        return *m_iter;
      }

      /**
       * @brief Pre-increment.
       */
      FilterIterator<Graph, Iterator, Predicate>& operator++()
      {
        do {
          ++m_iter;
        } while (m_iter != m_end && !m_predicate(m_graph, *m_iter));

        return *this;
      }

      /**
       * @brief Post-increment.
       */
      FilterIterator<Graph, Iterator, Predicate> operator++(int)
      {
        FilterIterator<Graph, Iterator, Predicate> tmp = *this;

        do {
          ++m_iter;
        } while (m_iter != m_end && !m_predicate(*m_iter));

        return tmp;
      }

      /**
       * @brief Compare for equality.
       */
      bool operator==(const FilterIterator<Graph, Iterator, Predicate> &other) const
      {
        return m_iter == other.m_iter;
      }

      /**
       * @brief Compare for inequality.
       */
      bool operator!=(const FilterIterator<Graph, Iterator, Predicate> &other) const
      {
        return m_iter != other.m_iter;
      }

    private:
      /**
       * @brief The graph.
       */
      const Graph &m_graph;
      /**
       * @brief The begin iterator.
       */
      Iterator m_iter;
      /**
       * @brief The end iterator.
       */
      Iterator m_end;
      /**
       * @brief The predicate.
       */
      Predicate m_predicate;
  };

  /**
   * @brief Create a filter iterator.
   *
   * @param g The graph.
   * @param begin The begin iterator.
   * @param end The end iterator.
   * @param predicate The predicate.
   */
  template<typename Graph, typename Iterator, typename Predicate>
  FilterIterator<Graph, Iterator, Predicate> makeFilterIterator(const Graph &g,
      Iterator begin, Iterator end, const Predicate &predicate)
  {
    return FilterIterator<Graph, Iterator, Predicate>(g, begin, end, predicate);
  }

} // namespace ocgl

#endif // OCGL_FILTER_ITERATOR_H
