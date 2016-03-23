#ifndef OCGL_PREDICATE_HAS_DEGREE_H
#define OCGL_PREDICATE_HAS_DEGREE_H

#include <ocgl/PropertyMap.h>

#include <functional>

/**
 * @file HasDegree.h
 * @brief HasDegree vertex predicates.
 */

namespace ocgl {

  namespace predicate {

    /**
     * @brief Predicate for vertex degree.
     *
     * Functions are provided to help instantiate this class:
     *
     * - HasDegreeEQ(properties, value)
     * - HasDegreeNE(properties, value)
     * - HasDegreeLT(properties, value)
     * - HasDegreeGT(properties, value)
     * - HasDegreeLE(properties, value)
     * - HasDegreeGE(properties, value)
     */
    template<typename Graph, typename Compare>
    class HasDegree
    {
      public:
        /**
         * @brief The vertex type.
         */
        using Vertex = typename GraphTraits<Graph>::Vertex;

        /**
         * @brief Constructor.
         *
         * @param value The degree to compare with.
         */
        HasDegree(unsigned int value) : m_value(value)
        {
        }

        /**
         * @brief The call operator itself.
         *
         * @param g The graph.
         * @param v The vertex.
         */
        bool operator()(const Graph &g, Vertex v) const
        {
          return m_compare(getDegree(g, v), m_value);
        }

      private:
        unsigned int m_value;
        Compare m_compare;
    };

    /**
     * @cond impl
     */

#define HAS_DEGREE_PREDICATE(cmp_name, cmp_functor) \
    template<typename Graph> \
    HasDegree<Graph, cmp_functor<unsigned int>> \
    HasDegree##cmp_name(unsigned int value) { \
      return HasDegree<Graph, cmp_functor<unsigned int>>(value); \
    }

    HAS_DEGREE_PREDICATE(EQ, std::equal_to);
    HAS_DEGREE_PREDICATE(NE, std::not_equal_to);
    HAS_DEGREE_PREDICATE(LT, std::less);
    HAS_DEGREE_PREDICATE(GT, std::greater);
    HAS_DEGREE_PREDICATE(LE, std::less_equal);
    HAS_DEGREE_PREDICATE(GE, std::greater_equal);

    /**
     * @endcond
     */

  } // namespace predicate

} // namespace ocgl

#endif // OCGL_PREDICATE_HAS_DEGREE_H
