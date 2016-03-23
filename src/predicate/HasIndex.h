#ifndef OCGL_PREDICATE_HAS_INDEX_H
#define OCGL_PREDICATE_HAS_INDEX_H

#include <ocgl/PropertyMap.h>

#include <functional>

/**
 * @file HasIndex.h
 * @brief HasIndex vertex and edge predicates.
 */

namespace ocgl {

  namespace predicate {

    /**
     * @brief Predicate for vertex and edge indices.
     *
     * Functions are provided to help instantiate this class:
     *
     * - HasIndexEQ(properties, value)
     * - HasIndexNE(properties, value)
     * - HasIndexLT(properties, value)
     * - HasIndexGT(properties, value)
     * - HasIndexLE(properties, value)
     * - HasIndexGE(properties, value)
     */
    template<typename Graph, typename Compare>
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
         * @brief The call operator itself.
         *
         * @param g The graph.
         * @param x The vertex or edge.
         */
        template<typename VertexOrEdge>
        bool operator()(const Graph &g, VertexOrEdge x) const
        {
          return m_compare(getIndex(g, x), m_value);
        }

      private:
        Index m_value;
        Compare m_compare;
    };

    /**
     * @cond impl
     */

#define HAS_INDEX_PREDICATE(cmp_name, cmp_functor) \
    template<typename Graph> \
    HasIndex<Graph, cmp_functor<Index>> \
    HasIndex##cmp_name(Index value) { \
      return HasIndex<Graph, cmp_functor<Index>>(value); \
    }

    HAS_INDEX_PREDICATE(EQ, std::equal_to);
    HAS_INDEX_PREDICATE(NE, std::not_equal_to);
    HAS_INDEX_PREDICATE(LT, std::less);
    HAS_INDEX_PREDICATE(GT, std::greater);
    HAS_INDEX_PREDICATE(LE, std::less_equal);
    HAS_INDEX_PREDICATE(GE, std::greater_equal);

    /**
     * @endcond
     */

  } // namespace predicate

} // namespace ocgl

#endif // OCGL_PREDICATE_HAS_INDEX_H
