#ifndef OCGL_GRAPH_TRAITS_H
#define OCGL_GRAPH_TRAITS_H

#include <ocgl/Contract.h>
#include <ocgl/IterPair.h>

#include <type_traits>

/**
 * @file GraphTraits.h
 * @brief Graph concept type traits and functions.
 */

/**
 * @namespace ocgl
 * @brief Namespace ocgl
 */
namespace ocgl {

  /*
   * @page graph_concept_page Graph Concept
   *
   * num_vertices(g)
   * num_edges(g)
   * num_vertex_ids(g)
   * num_edge_ids(g)
   * get_vertices(g)
   * get_edges(g)
   * get_vertex(g, id)
   * get_edge(g, id)
   *
   * get_id(g, v)
   * get_degree(g, v)
   * get_incident(g, v)
   * get_adjacent(g, v)
   *
   * get_id(g, e)
   * get_source(g, e)
   * get_target(g, e)
   *
   *
   * add_vertex(g)
   * remove_vertex(g, v)
   * add_edge(g, v, w)
   * remove_edge(g, e)
   * clear_graph()
   *
   *
   *
   * GraphTraits<Graph>::template null<typename GraphTraits<Graph>::Vertex>()
   * nullVertex<Graph>()
   * nullEdge<Graph>()
   *
   * isNull(g, x)
   * isValid(g, x)
   *
   * getOther(g, e, v)
   * getEdge(g, v, w)
   * isConnected(g, v, w)
   *
   *
   */

  /**
   * @brief Graph concept type traits.
   *
   * The GraphTraits class is used to determine the associated types for a
   * type that models the Graph concept.
   */
  template<typename Graph>
  struct GraphTraits
  {
    /**
     * @brief The vertex type.
     */
    using Vertex = typename Graph::Vertex;
    /**
     * @brief The edge type.
     */
    using Edge = typename Graph::Edge;
    /**
     * @brief The vertex iterator type.
     */
    using VertexIter = typename Graph::VertexIter;
    /**
     * @brief The edge iterator type.
     */
    using EdgeIter = typename Graph::EdgeIter;
    /**
     * @brief The incident edge iterator type.
     */
    using IncidentIter = typename Graph::IncidentIter;
    /**
     * @brief The adjacent vertex iterator type.
     */
    using AdjacentIter = typename Graph::AdjacentIter;

    /**
     * @brief Get the null vertex/edge.
     *
     * The vertex/edge returned by this function can be compared with other
     * vertices/edges for equality. Calling this function directly is not needed
     * since the isNull() and isValid() functions can be used.
     */
    template<typename VertexOrEdge>
    static VertexOrEdge null()
    {
      return Graph::template null<VertexOrEdge>();
    }
  };

  namespace impl {

    struct VertexTag {};
    struct EdgeTag {};

    template<typename Graph, typename Tag>
    struct Tag2Type;

    template<typename Graph>
    struct Tag2Type<Graph, VertexTag>
    {
      using Type = typename GraphTraits<Graph>::Vertex;
    };

    template<typename Graph>
    struct Tag2Type<Graph, EdgeTag>
    {
      using Type = typename GraphTraits<Graph>::Edge;
    };

  } // namespace impl

  //////////////////////////////////////////////////////////////////////////////
  //
  // Graph Concept Wrapper Functions
  //
  //////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Get the number of vertices.
   *
   * This is a wrapper function around the num_vertices(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   */
  template<typename Graph>
  unsigned int numVertices(const Graph &g)
  {
    return num_vertices(g);
  }

  /**
   * @brief Get the number of edges.
   *
   * This is a wrapper function around the num_edges(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   */
  template<typename Graph>
  unsigned int numEdges(const Graph &g)
  {
    return num_edges(g);
  }

  /**
   * @brief Get the number of vertex ids.
   *
   * The number of vertex ids is equal to the number of ids that are already
   * assigned to (possibly later removed) vertices. This count can be used to
   * as the size for a std::vector such that a vertex id can be used as index
   * into this std::vector.
   *
   * This is a wrapper function around the num_vertex_ids(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   */
  template<typename Graph>
  unsigned int numVertexIds(const Graph &g)
  {
    return num_vertex_ids(g);
  }

  /**
   * @brief Get the number of edge ids.
   *
   * The number of edge ids is equal to the number of ids that are already
   * assigned to (possibly later removed) edges. This count can be used to
   * as the size for a std::vector such that an edge id can be used as index
   * into this std::vector.
   *
   * This is a wrapper function around the num_edge_ids(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   */
  template<typename Graph>
  unsigned int numEdgeIds(const Graph &g)
  {
    return num_edge_ids(g);
  }

  /**
   * @brief Get an iterator pair over the graph's vertices.
   *
   * This is a wrapper function around the get_vertices(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   */
  template<typename Graph>
  IterPair<typename GraphTraits<Graph>::VertexIter> getVertices(const Graph &g)
  {
    return get_vertices(g);
  }

  /**
   * @brief Get an iterator pair over the graph's edges.
   *
   * This is a wrapper function around the get_edges(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   */
  template<typename Graph>
  IterPair<typename GraphTraits<Graph>::EdgeIter> getEdges(const Graph &g)
  {
    return get_edges(g);
  }

  /**
   * @brief Get a vertex by id.
   *
   * This is a wrapper function around the get_vertex(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param id The vertex id.
   *
   * @pre id < numVertexIds(g)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getVertex(const Graph &g, unsigned int id)
  {
    PRE_LT(id, numVertexIds(g));

    return get_vertex(g, id);
  }

  /**
   * @brief Get an edge by id.
   *
   * This is a wrapper function around the get_edge(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param id The edge id.
   *
   * @pre id < numEdgeIds(g)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Edge getEdge(const Graph &g, unsigned int id)
  {
    PRE_LT(id, numEdgeIds(g));

    return get_edge(g, id);
  }

  template<typename Graph, typename VertexOrEdge>
  bool isValid(const Graph &g, VertexOrEdge x);

  /**
   * @brief Get the vertex or edge id.
   *
   * This is a wrapper function around the get_id(g, x) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param x The vertex or edge.
   *
   * @pre isValid(g, x)
   */
  template<typename Graph, typename VertexOrEdge>
  unsigned int getId(const Graph &g, VertexOrEdge x)
  {
    PRE(isValid(g, x));

    return get_id(g, x);
  }

  /**
   * @brief Get the vertex degree.
   *
   * This is a wrapper function around the get_degree(g, v) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param v The vertex.
   *
   * @pre isValid(g, v)
   */
  template<typename Graph>
  unsigned int getDegree(const Graph &g, typename GraphTraits<Graph>::Vertex v)
  {
    PRE(isValid(g, v));

    return get_degree(g, v);
  }

  /**
   * @brief Get an iterator pair over the vertex' incident edges.
   *
   * This is a wrapper function around the get_incident(g, v) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param v The vertex.
   *
   * @pre isValid(g, v)
   */
  template<typename Graph>
  IterPair<typename GraphTraits<Graph>::IncidentIter> getIncident(const Graph &g,
      typename GraphTraits<Graph>::Vertex v)
  {
    PRE(isValid(g, v));

    return get_incident(g, v);
  }

  /**
   * @brief Get an iterator pair over the vertex' adjacent vertices.
   *
   * This is a wrapper function around the get_adjacent(g, v) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param v The vertex.
   *
   * @pre isValid(g, v)
   */
  template<typename Graph>
  IterPair<typename GraphTraits<Graph>::AdjacentIter> getAdjacent(const Graph &g,
      typename GraphTraits<Graph>::Vertex v)
  {
    PRE(isValid(g, v));

    return get_adjacent(g, v);
  }

  /**
   * @brief Get the edge source vertex.
   *
   * This is a wrapper function around the get_source(g, v) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param e The edge.
   *
   * @pre isValid(g, e)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getSource(const Graph &g,
      typename GraphTraits<Graph>::Edge e)
  {
    PRE(isValid(g, e));

    return get_source(g, e);
  }

  /**
   * @brief Get the edge target vertex.
   *
   * This is a wrapper function around the get_target(g, v) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param e The edge.
   *
   * @pre isValid(g, e)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getTarget(const Graph &g,
      typename GraphTraits<Graph>::Edge e)
  {
    PRE(isValid(g, e));

    return get_target(g, e);
  }

  /**
   * @brief Add a vertex to the graph.
   *
   * This is a wrapper function around the add_vertex(g) function that needs
   * to be implemented for types that model the editable graph concept.
   *
   * @param g The graph.
   *
   * @return The new vertex.
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex addVertex(Graph &g)
  {
    return add_vertex(g);
  }

  /**
   * @brief Remove a vertex from the graph.
   *
   * This is a wrapper function around the remove_vertex(g, v) function that
   * needs to be implemented for types that model the editable graph concept.
   *
   * @param g The graph.
   * @param v The vertex.
   */
  template<typename Graph>
  void removeVertex(Graph &g, typename GraphTraits<Graph>::Vertex v)
  {
    PRE(isValid(g, v));

    return remove_vertex(g, v);
  }

  template<typename Graph>
  bool isConnected(const Graph &g, typename GraphTraits<Graph>::Vertex v,
      typename GraphTraits<Graph>::Vertex w);

  /**
   * @brief Add an edge to the graph.
   *
   * This is a wrapper function around the add_edge(g, v, w) function that needs
   * to be implemented for types that model the editable graph concept.
   *
   * @param g The graph.
   * @param v The source vertex.
   * @param w The target vertex.
   *
   * @pre isValid(g, v)
   * @pre isValid(g, w)
   * @pre v != w
   * @pre !isConnected(g, v, w)
   *
   * @return The new edge.
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Edge addEdge(Graph &g,
      typename GraphTraits<Graph>::Vertex v,
      typename GraphTraits<Graph>::Vertex w)
  {
    PRE(isValid(g, v));
    PRE(isValid(g, w));
    PRE_NE(v, w);
    PRE_FALSE(isConnected(g, v, w));

    return add_edge(g, v, w);
  }

  /**
   * @brief Remove an edge from the graph.
   *
   * This is a wrapper function around the remove_edge(g, e) function that
   * needs to be implemented for types that model the editable graph concept.
   *
   * @param g The graph.
   * @param e The edge.
   *
   * @pre isValid(g, e)
   */
  template<typename Graph>
  void removeEdge(Graph &g, typename GraphTraits<Graph>::Edge e)
  {
    PRE(isValid(g, e));

    return remove_edge(g, e);
  }

  /**
   * @brief Remove all vertices and edges from the graph.
   *
   * This is a wrapper function around the clear_graph(g) function that needs to
   * be implemented for types that model the editable graph concept.
   */
  template<typename Graph>
  void clearGraph(Graph &g)
  {
    clear_graph(g);
  }

  //////////////////////////////////////////////////////////////////////////////
  //
  // Graph Concept Additional Functions
  //
  //////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Get a null vertex.
   *
   * This is a helper function to shorten
   *
   * @code
   * GraphTraits<Graph>::template null<typename GraphTraits<Graph>::Vertex>()
   * @endcode
   *
   * to
   *
   * @code
   * nullVertex<Graph>()
   * @endcode
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex nullVertex()
  {
    using Vertex = typename GraphTraits<Graph>::Vertex;
    return GraphTraits<Graph>::template null<Vertex>();
  }

  /**
   * @brief Get a null edge.
   *
   * This is a helper function to shorten
   *
   * @code
   * GraphTraits<Graph>::template null<typename GraphTraits<Graph>::Edge>()
   * @endcode
   *
   * to
   *
   * @code
   * nullEdge<Graph>()
   * @endcode
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Edge nullEdge()
  {
    using Edge = typename GraphTraits<Graph>::Edge;
    return GraphTraits<Graph>::template null<Edge>();
  }

  /**
   * @brief Check if a vertex/edge is a null vertex/edge.
   *
   * @param g The graph.
   * @param x The vertex/edge.
   */
  template<typename Graph, typename VertexOrEdge>
  bool isNull(const Graph &g, VertexOrEdge x)
  {
    return GraphTraits<Graph>::template null<VertexOrEdge>() == x;
  }

  /**
   * @brief Check if a vertex/edge is a valid (i.e. not a null vertex/edge).
   *
   * @param g The graph.
   * @param x The vertex/edge.
   */
  template<typename Graph, typename VertexOrEdge>
  bool isValid(const Graph &g, VertexOrEdge x)
  {
    return !isNull(g, x);
  }

  /**
   * @brief Get an edge's other vertex given source or target vertex.
   *
   * @param g The graph.
   * @param e The edge.
   * @param v The source or target vertex.
   *
   * @pre isValid(g, e)
   * @pre isValid(g, v)
   * @pre v == getSource(g, e) || v == getTarget(g, e)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getOther(const Graph &g,
      typename GraphTraits<Graph>::Edge e, typename GraphTraits<Graph>::Vertex v)
  {
    auto s = getSource(g, e);
    auto t = getTarget(g, e);

    return v == t ? s : t;
  }

  /**
   * @brief Get the edge between two vertices.
   *
   * @param g The graph.
   * @param v One of the vertices.
   * @param w One of the vertices.
   *
   * @pre isValid(g, v)
   * @pre isValid(g, w)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Edge getEdge(const Graph &g,
      typename GraphTraits<Graph>::Vertex v,
      typename GraphTraits<Graph>::Vertex w)
  {
    for (auto e : getIncident(g, v)) {
      auto s = getSource(g, e);
      auto t = getTarget(g, e);

      if ((v == s && w == t) || (v == t && w == s))
        return e;
    }

    return nullEdge<Graph>();
  }

  /**
   * @brief Check if two vertices are connected by an edge.
   *
   * This is a wrapper around getEdge(g, v, w) that compares the return value
   * with the null edge.
   *
   * @param g The graph.
   * @param v One of the vertices.
   * @param w One of the vertices.
   *
   * @pre isValid(g, v)
   * @pre isValid(g, w)
   *
   * @return isValid(getEdge(g, v, w))
   */
  template<typename Graph>
  bool isConnected(const Graph &g, typename GraphTraits<Graph>::Vertex v,
      typename GraphTraits<Graph>::Vertex w)
  {
    return isValid(g, getEdge(g, v, w));
  }

} // namespace ocgl

#endif // OCGL_GRAPH_TRAITS_H
