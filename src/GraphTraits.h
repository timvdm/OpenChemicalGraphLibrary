#ifndef OCGL_GRAPH_TRAITS_H
#define OCGL_GRAPH_TRAITS_H

#include <ocgl/Contract.h>
#include <ocgl/Range.h>
#include <ocgl/FilterIterator.h>

#include <type_traits>

/**
 * @file GraphTraits.h
 * @brief Graph concept type traits and functions.
 */

/**
 * @namespace ocgl
 * @brief Open Chemical Graph Library namespace.
 */
namespace ocgl {

  /**
   * @brief The index type.
   */
  using Index = unsigned int;

  /**
   * @brief The vertex index type.
   *
   * This is the same type as Index and is only provided to indicate that a
   * vertex index is intended.
   */
  using VertexIndex = Index;

  /**
   * @brief The vertex index type.
   *
   * This is the same type as Index and is only provided to indicate that a
   * vertex index is intended.
   */
  using EdgeIndex = Index;

  /**
   * @page graph_concept_page Graph Concept
   * @brief Graph Concept documentation.
   *
   * num_vertices(g)
   * num_edges(g)
   * get_vertices(g)
   * get_edges(g)
   * get_vertex(g, index)
   * get_edge(g, index)
   *
   * get_vertex_index(g, v)
   * get_degree(g, v)
   * get_incident(g, v)
   * get_adjacent(g, v)
   *
   * get_edge_index(g, e)
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
   * GraphTraits<Graph>::nullVertex()
   * GraphTraits<Graph>::nullEdge()
   * nullVertex<Graph>()
   * nullEdge<Graph>()
   *
   * isNullVertex(g, v)
   * isNullEdge(g, e)
   * isValidVertex(g, v)
   * isValidEdge(g, e)
   *
   * getOther(g, e, v)
   * getEdge(g, v, w)
   * isConnected(g, v, w)
   *
   *
   */

  /**
   * @class GraphTraits GraphTraits.h <ocgl/GraphTraits.h>
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
     * @brief Get the null vertex.
     *
     * The vertex returned by this function can be compared with other
     * vertices for equality. Calling this function directly is not needed
     * since the isNullVertex() and isValidVertex() functions can be used.
     */
    static Vertex nullVertex()
    {
      return Graph::nullVertex();
    }

    /**
     * @brief Get the null edge.
     *
     * The edge returned by this function can be compared with other
     * edges for equality. Calling this function directly is not needed
     * since the isNullEdge() and isValidEdge() functions can be used.
     */
    static Edge nullEdge()
    {
      return Graph::nullEdge();
    }
  };

  /**
   * @brief A list (i.e. std::vector) of vertices.
   */
  template<typename Graph>
  using VertexList = std::vector<typename GraphTraits<Graph>::Vertex>;

  /**
   * @brief A list (i.e. std::vector) of edges.
   */
  template<typename Graph>
  using EdgeList = std::vector<typename GraphTraits<Graph>::Edge>;

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
   * @brief Get an iterator range over the graph's vertices.
   *
   * This is a wrapper function around the get_vertices(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   */
  template<typename Graph>
  Range<typename GraphTraits<Graph>::VertexIter> getVertices(const Graph &g)
  {
    return get_vertices(g);
  }

  /**
   * @brief Get an iterator range over the graph's vertices filtered by a
   *        predicate.
   *
   * @param g The graph.
   * @param predicate The predicate.
   */
  template<typename Graph, typename Predicate>
  Range<FilterIterator<Graph, typename GraphTraits<Graph>::VertexIter, Predicate>>
  getVertices(const Graph &g, const Predicate &predicate)
  {
    auto range = getVertices(g);
    auto begin = makeFilterIterator(g, range.begin(), range.end(), predicate);
    auto end = makeFilterIterator(g, range.end(), range.end(), predicate);
    return makeRange(begin, end);
  }

  /**
   * @brief Get an iterator range over the graph's edges.
   *
   * This is a wrapper function around the get_edges(g) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   */
  template<typename Graph>
  Range<typename GraphTraits<Graph>::EdgeIter> getEdges(const Graph &g)
  {
    return get_edges(g);
  }

  /**
   * @brief Get an iterator range over the graph's edges filtered by a
   *        predicate.
   *
   * @param g The graph.
   * @param predicate The predicate.
   */
  template<typename Graph, typename Predicate>
  Range<FilterIterator<Graph, typename GraphTraits<Graph>::EdgeIter, Predicate>>
  getEdges(const Graph &g, const Predicate &predicate)
  {
    auto range = getEdges(g);
    auto begin = makeFilterIterator(g, range.begin(), range.end(), predicate);
    auto end = makeFilterIterator(g, range.end(), range.end(), predicate);
    return makeRange(begin, end);
  }

  /**
   * @brief Get a vertex by index.
   *
   * This is a wrapper function around the get_vertex(g, i) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param index The vertex index.
   *
   * @pre index < numVertices(g)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getVertex(const Graph &g,
      VertexIndex index)
  {
    PRE_LT(index, numVertices(g));

    return get_vertex(g, index);
  }

  /**
   * @brief Get an edge by index.
   *
   * This is a wrapper function around the get_edge(g, i) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param index The edge index.
   *
   * @pre index < numEdges(g)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Edge getEdge(const Graph &g, EdgeIndex index)
  {
    PRE_LT(index, numEdges(g));

    return get_edge(g, index);
  }

  template<typename Graph>
  bool isValidVertex(const Graph &g, typename GraphTraits<Graph>::Vertex v);

  /**
   * @brief Get the vertex index.
   *
   * This is a wrapper function around the get_vertex_index(g, v) function that
   * needs to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param v The vertex.
   *
   * @pre isValidVertex(g, v)
   */
  template<typename Graph>
  Index getVertexIndex(const Graph &g, typename GraphTraits<Graph>::Vertex v)
  {
    PRE(isValidVertex(g, v));

    return get_vertex_index(g, v);
  }

  template<typename Graph>
  bool isValidEdge(const Graph &g, typename GraphTraits<Graph>::Edge e);

  /**
   * @brief Get the edge index.
   *
   * This is a wrapper function around the get_edge_index(g, e) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param e The edge.
   *
   * @pre isValidEdge(g, e)
   */
  template<typename Graph>
  Index getEdgeIndex(const Graph &g, typename GraphTraits<Graph>::Edge e)
  {
    PRE(isValidEdge(g, e));

    return get_edge_index(g, e);
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
   * @pre isValidVertex(g, v)
   */
  template<typename Graph>
  unsigned int getDegree(const Graph &g, typename GraphTraits<Graph>::Vertex v)
  {
    PRE(isValidVertex(g, v));

    return get_degree(g, v);
  }

  /**
   * @brief Get an iterator range over the vertex' incident edges.
   *
   * This is a wrapper function around the get_incident(g, v) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param v The vertex.
   *
   * @pre isValidVertex(g, v)
   */
  template<typename Graph>
  Range<typename GraphTraits<Graph>::IncidentIter> getIncident(const Graph &g,
      typename GraphTraits<Graph>::Vertex v)
  {
    PRE(isValidVertex(g, v));

    return get_incident(g, v);
  }

  /**
   * @brief Get an iterator range over the vertex' incident edges filtered by a
   *        predicate.
   *
   * @param g The graph.
   * @param v The vertex.
   * @param predicate The predicate.
   *
   * @pre isValidVertex(g, v)
   */
  template<typename Graph, typename Predicate>
  Range<FilterIterator<Graph, typename GraphTraits<Graph>::IncidentIter, Predicate>>
  getIncident(const Graph &g, typename GraphTraits<Graph>::Vertex v,
      const Predicate &predicate)
  {
    auto range = getIncident(g, v);
    auto begin = makeFilterIterator(g, range.begin(), range.end(), predicate);
    auto end = makeFilterIterator(g, range.end(), range.end(), predicate);
    return makeRange(begin, end);
  }

  /**
   * @brief Get an iterator range over the vertex' adjacent vertices.
   *
   * This is a wrapper function around the get_adjacent(g, v) function that needs
   * to be implemented for types that model the graph concept.
   *
   * @param g The graph.
   * @param v The vertex.
   *
   * @pre isValidVertex(g, v)
   */
  template<typename Graph>
  Range<typename GraphTraits<Graph>::AdjacentIter> getAdjacent(const Graph &g,
      typename GraphTraits<Graph>::Vertex v)
  {
    PRE(isValidVertex(g, v));

    return get_adjacent(g, v);
  }

  /**
   * @brief Get an iterator range over the vertex' adjacent vertices filtered by
   *        a predicate.
   *
   * @param g The graph.
   * @param v The vertex.
   * @param predicate The predicate.
   *
   * @pre isValidVertex(g, v)
   */
  template<typename Graph, typename Predicate>
  Range<FilterIterator<Graph, typename GraphTraits<Graph>::AdjacentIter, Predicate>>
  getAdjacent(const Graph &g, typename GraphTraits<Graph>::Vertex v,
      const Predicate &predicate)
  {
    auto range = getAdjacent(g, v);
    auto begin = makeFilterIterator(g, range.begin(), range.end(), predicate);
    auto end = makeFilterIterator(g, range.end(), range.end(), predicate);
    return makeRange(begin, end);
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
   * @pre isValidEdge(g, e)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getSource(const Graph &g,
      typename GraphTraits<Graph>::Edge e)
  {
    PRE(isValidEdge(g, e));

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
   * @pre isValidEdge(g, e)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getTarget(const Graph &g,
      typename GraphTraits<Graph>::Edge e)
  {
    PRE(isValidEdge(g, e));

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
    PRE(isValidVertex(g, v));

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
   * @pre isValidVertex(g, v)
   * @pre isValidVertex(g, w)
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
    PRE(isValidVertex(g, v));
    PRE(isValidVertex(g, w));
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
   * @pre isValidEdge(g, e)
   */
  template<typename Graph>
  void removeEdge(Graph &g, typename GraphTraits<Graph>::Edge e)
  {
    PRE(isValidEdge(g, e));

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
    //using Vertex = typename GraphTraits<Graph>::Vertex;
    //return GraphTraits<Graph>::template null<Vertex>();
    return GraphTraits<Graph>::nullVertex();
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
    //using Edge = typename GraphTraits<Graph>::Edge;
    //return GraphTraits<Graph>::template null<Edge>();
    return GraphTraits<Graph>::nullEdge();
  }

  /**
   * @brief Check if a vertex is a null vertex.
   *
   * @param g The graph.
   * @param v The vertex.
   */
  template<typename Graph>
  bool isNullVertex(const Graph &g, typename GraphTraits<Graph>::Vertex v)
  {
    return v == GraphTraits<Graph>::nullVertex();
  }

  /**
   * @brief Check if an edge is a null edge.
   *
   * @param g The graph.
   * @param e The edge.
   */
  template<typename Graph>
  bool isNullEdge(const Graph &g, typename GraphTraits<Graph>::Edge e)
  {
    return e == GraphTraits<Graph>::nullEdge();
  }

  /**
   * @brief Check if a vertex is a valid (i.e. not a null vertex).
   *
   * @param g The graph.
   * @param v The vertex.
   */
  template<typename Graph>
  bool isValidVertex(const Graph &g, typename GraphTraits<Graph>::Vertex v)
  {
    return !isNullVertex(g, v);
  }

  /**
   * @brief Check if an edge is a valid (i.e. not a null edge).
   *
   * @param g The graph.
   * @param e The edge.
   */
  template<typename Graph>
  bool isValidEdge(const Graph &g, typename GraphTraits<Graph>::Edge e)
  {
    return !isNullEdge(g, e);
  }

  /**
   * @brief Get an edge's other vertex given source or target vertex.
   *
   * @param g The graph.
   * @param e The edge.
   * @param v The source or target vertex.
   *
   * @pre isValidEdge(g, e)
   * @pre isValidVertex(g, v)
   * @pre v == getSource(g, e) || v == getTarget(g, e)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getOther(const Graph &g,
      typename GraphTraits<Graph>::Edge e, typename GraphTraits<Graph>::Vertex v)
  {
    PRE(isValidEdge(g, e));
    PRE(isValidVertex(g, v));

    auto s = getSource(g, e);
    auto t = getTarget(g, e);

    PRE(v == s || v == t);

    return v == t ? s : t;
  }

  /**
   * @brief Get the edge between two vertices.
   *
   * @param g The graph.
   * @param v One of the vertices.
   * @param w One of the vertices.
   *
   * @pre isValidVertex(g, v)
   * @pre isValidVertex(g, w)
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Edge getEdge(const Graph &g,
      typename GraphTraits<Graph>::Vertex v,
      typename GraphTraits<Graph>::Vertex w)
  {
    PRE(isValidVertex(g, v));
    PRE(isValidVertex(g, w));

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
   * @pre isValidVertex(g, v)
   * @pre isValidVertex(g, w)
   *
   * @return isValidEdge(getEdge(g, v, w))
   */
  template<typename Graph>
  bool isConnected(const Graph &g, typename GraphTraits<Graph>::Vertex v,
      typename GraphTraits<Graph>::Vertex w)
  {
    PRE(isValidVertex(g, v));
    PRE(isValidVertex(g, w));

    return isValidEdge(g, getEdge(g, v, w));
  }

} // namespace ocgl

#endif // OCGL_GRAPH_TRAITS_H
