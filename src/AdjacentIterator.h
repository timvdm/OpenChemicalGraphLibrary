#ifndef OCGL_ADJACENT_ITERATOR_H
#define OCGL_ADJACENT_ITERATOR_H

#include <ocgl/GraphTraits.h>

#include <iterator>

/**
 * @file AdjacentIterator.h
 * @brief Iterator adaptor to make adjacent iterator from incident iterator.
 */

namespace ocgl {

  /**
   * @class AdjacentIterator AdjacentIterator.h <ocgl/AdjacentIterator.h>
   * @brief Iterator adaptor to make adjacent iterator from incident iterator.
   *
   * The AdjacentIterator is a wrapper around an incident iterator to create
   * and adjacent iterator. This is done using the incident edges range,
   * central vertex and the getOther() function.
   *
   * Example:
   * @code
   * using IncidentIter = ...;
   *
   * ocgl::Range<IncidentIter> get_incident(const MyGraph &g, MyVertex v)
   * {
   *   // ...
   * }
   *
   * using AdjacentIter = ocgl::AdjacentIterator<IncidentIter>;
   *
   * ocgl::Range<AdjacentIterator> get_adjacent(const MyGraph &g, MyVertex v)
   * {
   *   auto incident = get_incident(g, v);
   *   auto begin = ocgl::AdjacentIterator<MyGraph>(g, v, incident.begin());
   *   auto end = ocgl::AdjacentIterator<MyGraph>(g, v, incident.end());
   *   return ocgl::makeRange(begin, end);
   * }
   * @endcode
   */
  template<typename Graph>
  class AdjacentIterator : public std::iterator<std::forward_iterator_tag,
      typename GraphTraits<Graph>::Vertex>
  {
    public:
      /**
       * @brief The vertex type.
       */
      using Vertex = typename GraphTraits<Graph>::Vertex;
      /**
       * @brief The incident iterator type.
       */
      using IncidentIter = typename GraphTraits<Graph>::IncidentIter;

      /**
       * @brief Default constructor.
       */
      AdjacentIterator()
      {
      }

      /**
       * @brief Constructor.
       *
       * @param g The graph.
       * @param vertex The central vertex.
       * @param iter The incident iterator.
       */
      AdjacentIterator(const Graph &g, Vertex vertex, IncidentIter iter)
        : m_graph(g), m_vertex(vertex), m_iter(iter)
      {
      }

      /**
       * @brief Dereference operator to get adjacent vertex.
       */
      Vertex operator*() const
      {
        return getOther(m_graph, *m_iter, m_vertex);
      }

      /**
       * @brief Pre-increment.
       */
      AdjacentIterator<Graph>& operator++()
      {
        ++m_iter;
        return *this;
      }

      /**
       * @brief Post-increment.
       */
      AdjacentIterator<Graph> operator++(int)
      {
        AdjacentIterator<Graph> tmp = *this;
        ++m_iter;
        return tmp;
      }

      /**
       * @brief Compare for equality.
       */
      bool operator==(const AdjacentIterator<Graph> &other) const
      {
        return m_iter == other.m_iter;
      }

      /**
       * @brief Compare for inequality.
       */
      bool operator!=(const AdjacentIterator<Graph> &other) const
      {
        return m_iter != other.m_iter;
      }

    private:
      /**
       * @brief The graph.
       */
      const Graph &m_graph;
      /**
       * @brief The central vertex.
       */
      Vertex m_vertex;
      /**
       * @brief The incident iterator.
       */
      IncidentIter m_iter;
  };

} // namespace ocgl

#endif // OCGL_ADJACENT_ITERATOR_H
