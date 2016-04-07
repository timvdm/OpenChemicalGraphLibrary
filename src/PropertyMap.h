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
   * vertex or edge index. When a property map is created, storage is allocated
   * based on the number of vertices or edges.
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
        init();
      }

      /**
       * @brief Constructor.
       *
       * @param graph The graph.
       * @param value The initial property value.
       */
      PropertyMap(const Graph &graph, const T &value) : m_graph(graph)
      {
        init();
        std::fill(m_props.begin(), m_props.end(), value);
      }

      /**
       * @brief Get the graph.
       */
      const Graph& graph() const
      {
        return m_graph;
      }

      /**
       * @brief Get const reference to vertex property.
       *
       * @param v The vertex.
       *
       * @pre isValidVertex(g, v)
       */
      template<typename Tag = VertexOrEdgeTag>
      typename std::enable_if<std::is_same<Tag, impl::VertexTag>::value, ConstReference>::type
      operator[](typename GraphTraits<Graph>::Vertex v) const
      {
        PRE(isValidVertex(m_graph, v));
        PRE_LT(getVertexIndex(m_graph, v), m_props.size());

        return m_props[getVertexIndex(m_graph, v)];
      }

      /**
       * @brief Get const reference to edge property.
       *
       * @param e The edge.
       *
       * @pre isValidEdge(g, e)
       */
      template<typename Tag = VertexOrEdgeTag>
      typename std::enable_if<std::is_same<Tag, impl::EdgeTag>::value, ConstReference>::type
      operator[](typename GraphTraits<Graph>::Edge e) const
      {
        PRE(isValidEdge(m_graph, e));
        PRE_LT(getEdgeIndex(m_graph, e), m_props.size());

        return m_props[getEdgeIndex(m_graph, e)];
      }

      /**
       * @brief Get reference to vertex property.
       *
       * @param v The vertex.
       *
       * @pre isValidVertex(g, v)
       */
      template<typename Tag = VertexOrEdgeTag>
      typename std::enable_if<std::is_same<Tag, impl::VertexTag>::value, Reference>::type
      operator[](typename GraphTraits<Graph>::Vertex v)
      {
        PRE(isValidVertex(m_graph, v));
        PRE_LT(getVertexIndex(m_graph, v), m_props.size());

        return m_props[getVertexIndex(m_graph, v)];
      }

      /**
       * @brief Get reference to edge property.
       *
       * @param e The edge.
       *
       * @pre isValidEdge(g, e)
       */
      template<typename Tag = VertexOrEdgeTag>
      typename std::enable_if<std::is_same<Tag, impl::EdgeTag>::value, Reference>::type
      operator[](typename GraphTraits<Graph>::Edge e)
      {
        PRE(isValidEdge(m_graph, e));
        PRE_LT(getEdgeIndex(m_graph, e), m_props.size());

        return m_props[getEdgeIndex(m_graph, e)];
      }

    private:
      template<typename Tag = VertexOrEdgeTag>
      typename std::enable_if<std::is_same<Tag, impl::VertexTag>::value>::type
      init()
      {
        m_props.resize(numVertices(m_graph));
      }

      template<typename Tag = VertexOrEdgeTag>
      typename std::enable_if<std::is_same<Tag, impl::EdgeTag>::value>::type
      init()
      {
        m_props.resize(numEdges(m_graph));
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

  /**
   * @class VertexEdgePropertyMap PropertyMap.h <ocgl/PropertyMap.h>
   * @brief Wrapper for combined vertex/edge property map.
   */
  template<typename Graph, typename T>
  struct VertexEdgePropertyMap
  {
    public:
      /**
       * @brief Constructor.
       *
       * @param g The graph.
       */
      VertexEdgePropertyMap(const Graph &g) : vertices(g), edges(g)
      {
      }

      /**
       * @brief Constructor.
       *
       * @param g The graph.
       * @param value The initial property value.
       */
      VertexEdgePropertyMap(const Graph &g, const T &value)
        : vertices(g, value), edges(g, value)
      {
      }

      /**
       * @brief Get the graph.
       */
      const Graph& graph() const
      {
        return vertices.graph();
      }

      /**
       * @brief The vertex property map.
       */
      VertexPropertyMap<Graph, T> vertices;
      /**
       * @brief The edge property map.
       */
      EdgePropertyMap<Graph, T> edges;
  };

} // namespace ocgl

#endif // OCGL_PROPERTY_MAP_H
