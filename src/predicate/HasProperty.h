#ifndef OCGL_PREDICATE_HAS_PROPERTY_H
#define OCGL_PREDICATE_HAS_PROPERTY_H

#include <ocgl/PropertyMap.h>

#include <functional>

/**
 * @file HasProperty.h
 * @brief Vertex and edge property predicates.
 */

namespace ocgl {

  /**
   * @namespace ocgl::predicate
   * @brief Predicates namespace.
   */
  namespace predicate {

    /**
     * @brief Predicate for vertex and edge properties.
     *
     * This class can be used to create vertex and edge predicates that compare
     * a properties using a specified compare operation. Instantiating this class
     * requires some code but helper functions are provided:
     *
     * - HasPropertyEQ(properties, value)
     * - HasPropertyNE(properties, value)
     * - HasPropertyLT(properties, value)
     * - HasPropertyGT(properties, value)
     * - HasPropertyLE(properties, value)
     * - HasPropertyGE(properties, value)
     */
    template<typename Graph, typename T, typename VertexOrEdgeTag,
      typename Compare>
    class HasProperty
    {
      public:
        /**
         * @brief Constructor.
         *
         * @param properties The properties.
         * @param value The value to compare with.
         */
        HasProperty(const PropertyMap<Graph, T, VertexOrEdgeTag> &properties,
            const T &value) : m_properties(properties), m_value(value)
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
          return m_compare(m_properties[v], m_value);
        }

        /**
         * @brief The call operator edges.
         *
         * @param g The graph.
         * @param e The edge.
         */
        template<typename Tag = VertexOrEdgeTag>
        typename std::enable_if<std::is_same<Tag, impl::EdgeTag>::value, bool>::type
        operator()(const Graph &g, typename GraphTraits<Graph>::Edge e) const
        {
          return m_compare(m_properties[e], m_value);
        }

      private:
        const PropertyMap<Graph, T, VertexOrEdgeTag> &m_properties;
        T m_value;
        Compare m_compare;
    };

    /**
     * @cond impl
     */

#define HAS_PROPERTY_PREDICATE(cmp_name, cmp_functor) \
    template<typename Graph, typename T, typename VertexOrEdgeTag> \
    HasProperty<Graph, T, VertexOrEdgeTag, cmp_functor<T>> \
    HasProperty##cmp_name(const PropertyMap<Graph, T, VertexOrEdgeTag> &properties, \
        const T &value) { \
      return HasProperty<Graph, T, VertexOrEdgeTag, cmp_functor<T>>(properties, value); \
    }

    HAS_PROPERTY_PREDICATE(EQ, std::equal_to);
    HAS_PROPERTY_PREDICATE(NE, std::not_equal_to);
    HAS_PROPERTY_PREDICATE(LT, std::less);
    HAS_PROPERTY_PREDICATE(GT, std::greater);
    HAS_PROPERTY_PREDICATE(LE, std::less_equal);
    HAS_PROPERTY_PREDICATE(GE, std::greater_equal);

    /**
     * @endcond
     */

    /**
     * @brief Predicate to select cyclic vertices and edges.
     *
     * @param cycleMembership The vertex or edge cycle membership.
     */
    template<typename Graph, typename VertexOrEdgeTag>
    HasProperty<Graph, bool, VertexOrEdgeTag, std::equal_to<bool>>
    IsCyclic(const PropertyMap<Graph, bool, VertexOrEdgeTag> &cycleMembership)
    {
      return HasProperty<Graph, bool, VertexOrEdgeTag,
             std::equal_to<bool>>(cycleMembership, true);
    }

    /**
     * @brief Predicate to select acyclic vertices and edges.
     *
     * @param cycleMembership The vertex or edge cycle membership.
     */
    template<typename Graph, typename VertexOrEdgeTag>
    HasProperty<Graph, bool, VertexOrEdgeTag, std::equal_to<bool>>
    IsAcyclic(const PropertyMap<Graph, bool, VertexOrEdgeTag> &cycleMembership)
    {
      return HasProperty<Graph, bool, VertexOrEdgeTag,
             std::equal_to<bool>>(cycleMembership, false);
    }

  } // namespace predicate

} // namespace ocgl

#endif // OCGL_PREDICATE_HAS_PROPERTY_H
