#ifndef OCGL_GRAPH_TRAITS_H
#define OCGL_GRAPH_TRAITS_H

#include <type_traits>

namespace ocgl {

  /**
   * @brief Graph concept type traits.
   *
   * The graph_traits class is used to determine the associated types for a
   * type (Graph) that models the graph concept.
   */
  template<typename Graph>
  struct graph_traits
  {
    /**
     * @brief The vertex type.
     */
    using vertex = typename Graph::vertex;
    /**
     * @brief The edge type.
     */
    using edge = typename Graph::edge;
    /**
     * @brief The vertex iterator type.
     */
    using vertex_iter = typename Graph::vertex_iter;
    /**
     * @brief The edge iterator type.
     */
    using edge_iter = typename Graph::edge_iter;
    /**
     * @brief The incident edge iterator type.
     */
    using incident_iter = typename Graph::incident_iter;
    /**
     * @brief The adjacent vertex iterator type.
     */
    using adjacent_iter = typename Graph::adjacent_iter;

    /**
     * @brief Get the null vertex.
     *
     * The vertex returned by this function can be compared with other vertices
     * for equality. Calling this function directly is not needed since the
     * is_null() and is_valid() functions can be used.
     */
    static vertex null_vertex()
    {
      return Graph::null_vertex();
    }

    /**
     * @brief Get the null edge.
     *
     * The edge returned by this function can be compared with other vertices
     * for equality. Calling this function directly is not needed since the
     * is_null() and is_valid() functions can be used.
     */
    static edge null_edge()
    {
      return Graph::null_edge();
    }
  };

  namespace impl {

    template<bool> struct vertex_or_edge {};
    using is_vertex_tag = vertex_or_edge<true>;
    using is_edge_tag = vertex_or_edge<false>;

    template<typename Graph, typename Vertex>
    bool is_null(const Graph &g, Vertex v, is_vertex_tag)
    {
      return graph_traits<Graph>::null_vertex() == v;
    }

    template<typename Graph, typename Edge>
    bool is_null(const Graph &g, Edge e, is_edge_tag)
    {
      return graph_traits<Graph>::null_edge() == e;
    }

  } // namespace impl

  /**
   * @brief Check if a vertex/edge is a null vertex/edge.
   *
   * @param g The graph.
   * @param x The vertex/edge.
   */
  template<typename Graph, typename VertexOrEdge>
  bool is_null(const Graph &g, VertexOrEdge x)
  {
    return impl::is_null(g, x, impl::vertex_or_edge<std::is_same<typename graph_traits<Graph>::vertex, VertexOrEdge>::value>());
  }

  /**
   * @brief Check if a vertex/edge is a valid (i.e. not a null vertex/edge).
   *
   * @param g The graph.
   * @param x The vertex/edge.
   */
  template<typename Graph, typename VertexOrEdge>
  bool is_valid(const Graph &g, VertexOrEdge x)
  {
    return !is_null(g, x);
  }

  /**
   * @brief Check if two vertices are connected by an edge.
   *
   * This is a wrapper around get_edge(g, v, w) that compares the return value
   * with the null edge.
   *
   * @param g The graph.
   * @param v One of the vertices.
   * @param w One of the vertices.
   *
   * @pre is_valid(g, v)
   * @pre is_valid(g, w)
   *
   * @return is_valid(get_edge(g, v, w))
   */
  template<typename Graph>
  bool is_connected(const Graph &g, typename graph_traits<Graph>::vertex v,
      typename graph_traits<Graph>::vertex w)
  {
    return is_valid(get_edge(g, v, w));
  }

} // namespace ocgl

#endif // OCGL_GRAPH_TRAITS_H
