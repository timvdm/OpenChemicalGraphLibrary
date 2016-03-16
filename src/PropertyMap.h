#ifndef OCGL_PROPERTY_MAP_H
#define OCGL_PROPERTY_MAP_H

#include <ocgl/GraphTraits.h>

#include <vector>

/**
 * @file PropertyMap.h
 * @brief Properties associated with vertices and edges.
 */

namespace ocgl {

  /**
   * @class PropertyMap PropertyMap.h <ocgl/PropertyMap.h>
   * @brief Properties associated with vertices and edges.
   *
   * A property map associates properties with vertices or edges. Access to
   * these properties is O(1) since these are stored in an array indexed by
   * vertex or edge id. When a property map is created, storage is allocated
   * based on the number of vertex or edge ids (i.e. numVertexIds() or
   * numEdgeIds()).
   */
  template<typename Graph, typename T, typename VertexOrEdgeTag>
  class PropertyMap
  {
    public:
      /**
       * @brief Reference to property.
       */
      using Reference = typename std::vector<T>::reference;
      /**
       * @brief Const reference to property.
       */
      using ConstReference = typename std::vector<T>::const_reference;

      /**
       * @brief Constructor.
       *
       * @param graph The graph.
       */
      PropertyMap(const Graph &graph) : m_graph(graph)
      {
        init(VertexOrEdgeTag());
      }

      /**
       * @brief Get const reference to vertex/edge property.
       *
       * @param x The vertex/edge.
       *
       * @pre isValid(g, x)
       */
      template<typename VertexOrEdge>
      ConstReference operator[](VertexOrEdge x) const
      {
        PRE(isValid(m_graph, x));
        PRE_LT(getId(m_graph, x), m_props.size());

        return m_props[getId(m_graph, x)];
      }

      /**
       * @brief Get reference to vertex/edge property.
       *
       * @param x The vertex/edge.
       *
       * @pre isValid(g, x)
       */
      template<typename VertexOrEdge>
      Reference operator[](VertexOrEdge x)
      {
        PRE(isValid(m_graph, x));
        PRE_LT(getId(m_graph, x), m_props.size());

        return m_props[getId(m_graph, x)];
      }

    private:
      void init(impl::VertexTag)
      {
        m_props.resize(numVertexIds(m_graph));
      }

      void init(impl::EdgeTag)
      {
        m_props.resize(numEdgeIds(m_graph));
      }

      /**
       * @brief The graph.
       */
      const Graph &m_graph;
      /**
       * @brief The properties.
       */
      std::vector<T> m_props;
  };

  /**
   * @brief PropertyMap for vertices.
   */
  template<typename Graph, typename T>
  using VertexPropertyMap = PropertyMap<Graph, T, impl::VertexTag>;

  /**
   * @brief Property map for edges.
   */
  template<typename Graph, typename T>
  using EdgePropertyMap = PropertyMap<Graph, T, impl::EdgeTag>;

} // namespace ocgl

#endif // OCGL_PROPERTY_MAP_H
