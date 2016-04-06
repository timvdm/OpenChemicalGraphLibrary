#ifndef OCGL_PREDICATE_HAS_INDEX_H
#define OCGL_PREDICATE_HAS_INDEX_H

#include <ocgl/PropertyMap.h>

#include <type_traits>
#include <functional>

/**
 * @file HasIndex.h
 * @brief HasVertexIndex and HasEdgeIndex predicates.
 */

namespace ocgl {

  namespace predicate {

    /**
     * @brief Predicate for vertex and edge indices.
     *
     * Functions are provided to help instantiate this class:
     *
     * - HasVertexIndexEQ(value)
     * - HasVertexIndexNE(value)
     * - HasVertexIndexLT(value)
     * - HasVertexIndexGT(value)
     * - HasVertexIndexLE(value)
     * - HasVertexIndexGE(value)
     * - HasEdgeIndexEQ(value)
     * - HasEdgeIndexNE(value)
     * - HasEdgeIndexLT(value)
     * - HasEdgeIndexGT(value)
     * - HasEdgeIndexLE(value)
     * - HasEdgeIndexGE(value)
     */
    template<typename Graph, typename Compare, typename VertexOrEdgeTag>
    class HasIndex
    {
      public:
        /**
         * @brief Constructor.
         *
         * @param value The index to compare with.
         */
        HasIndex(Index value) : m_value(value)
        {
        }

        /**
         * @brief The call operator for vertices.
         *
         * @param g The graph.
         * @param v The vertex.
         */
        template<typename Tag = VertexOrEdgeTag>
        typename std::enable_if<std::is_same<Tag, impl::VertexTag>::value, bool>::type
        operator()(const Graph &g, typename GraphTraits<Graph>::Vertex v) const
        {
          return m_compare(getVertexIndex(g, v), m_value);
        }

        /**
         * @brief The call operator for edges.
         *
         * @param g The graph.
         * @param e The edge.
         */
        template<typename Tag = VertexOrEdgeTag>
        typename std::enable_if<std::is_same<Tag, impl::EdgeTag>::value, bool>::type
        operator()(const Graph &g, typename GraphTraits<Graph>::Edge e) const
        {
          return m_compare(getEdgeIndex(g, e), m_value);
        }

      private:
        Index m_value;
        Compare m_compare;
    };

    /**
     * @cond impl
     */

#define HAS_INDEX_PREDICATE(name, tag, cmp_name, cmp_functor) \
    template<typename Graph> \
    HasIndex<Graph, cmp_functor<Index>, tag> \
    Has##name##Index##cmp_name(Index value) { \
      return HasIndex<Graph, cmp_functor<Index>, tag>(value); \
    }

    HAS_INDEX_PREDICATE(Vertex, impl::VertexTag, EQ, std::equal_to);
    HAS_INDEX_PREDICATE(Vertex, impl::VertexTag, NE, std::not_equal_to);
    HAS_INDEX_PREDICATE(Vertex, impl::VertexTag, LT, std::less);
    HAS_INDEX_PREDICATE(Vertex, impl::VertexTag, GT, std::greater);
    HAS_INDEX_PREDICATE(Vertex, impl::VertexTag, LE, std::less_equal);
    HAS_INDEX_PREDICATE(Vertex, impl::VertexTag, GE, std::greater_equal);

    HAS_INDEX_PREDICATE(Edge, impl::EdgeTag, EQ, std::equal_to);
    HAS_INDEX_PREDICATE(Edge, impl::EdgeTag, NE, std::not_equal_to);
    HAS_INDEX_PREDICATE(Edge, impl::EdgeTag, LT, std::less);
    HAS_INDEX_PREDICATE(Edge, impl::EdgeTag, GT, std::greater);
    HAS_INDEX_PREDICATE(Edge, impl::EdgeTag, LE, std::less_equal);
    HAS_INDEX_PREDICATE(Edge, impl::EdgeTag, GE, std::greater_equal);

    /**
     * @endcond
     */

  } // namespace predicate

} // namespace ocgl

#endif // OCGL_PREDICATE_HAS_INDEX_H
