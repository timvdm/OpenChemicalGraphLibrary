#ifndef OCGL_PATH_H
#define OCGL_PATH_H

#include <ocgl/GraphTraits.h>

/**
 * @file Path.h
 * @brief Functions for working with vertex and edge paths.
 */

namespace ocgl {

  /**
   * @brief Get the common vertex of two edges.
   *
   * @param g The graph.
   * @param e1 One of the edges.
   * @param e2 One of the edges.
   *
   * @return The common vertex or a null vertex if there is no common vertex.
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex commonVertex(const Graph &g,
      typename GraphTraits<Graph>::Edge e1,
      typename GraphTraits<Graph>::Edge e2)
  {
    if (getSource(g, e1) == getSource(g, e2))
      return getSource(g, e1);
    if (getSource(g, e1) == getTarget(g, e2))
      return getSource(g, e1);
    if (getTarget(g, e1) == getSource(g, e2))
      return getTarget(g, e1);
    if (getTarget(g, e1) == getTarget(g, e2))
      return getTarget(g, e1);

    return nullVertex<Graph>();
  }

  /**
   * @brief Check if an (ordered) vertex set is a path.
   *
   * A list of vertices is considered to be a path if all sequential vertices
   * are connected by an edge. An empty or singleton set are also considered to
   * be a path.
   *
   * @param g The graph.
   * @param p The list of vertices.
   *
   * @return True if the vertices form a path.
   */
  template<typename Graph>
  bool isVertexPath(const Graph &g, const VertexList<Graph> &p)
  {
    for (std::size_t i = 1; i < p.size(); ++i)
      if (!isConnected(g, p[i - 1], p[i]))
        return false;
    return true;
  }

  /**
   * @brief Check if an (ordered) edge set is a path.
   *
   * A list of edges is considered to be a path if all sequential edges have
   * a common vertex. An empty or singleton set are also considered to be
   * a path.
   *
   * @param g The graph.
   * @param p The list of egdes.
   *
   * @return True if the edges form a path.
   */
  template<typename Graph>
  bool isEdgePath(const Graph &g, const EdgeList<Graph> &p)
  {
    for (std::size_t i = 1; i < p.size(); ++i)
      if (commonVertex(g, p[i - 1], p[i]) == nullVertex<Graph>())
        return false;
    return true;
  }

  /**
   * @brief Vertex path in a graph.
   */
  template<typename Graph>
  using VertexPath = VertexList<Graph>;

  /**
   * @brief Edge path in a graph.
   */
  template<typename Graph>
  using EdgePath = EdgeList<Graph>;

  /**
   * @brief Convert a vertex path to the corresponding edge path.
   *
   * @param g The graph.
   * @param vertices The vertex path.
   */
  template<typename Graph>
  EdgePath<Graph> vertexPathToEdgePath(const Graph &g,
      const VertexPath<Graph> &vertices)
  {
    EdgePath<Graph> edges;
    edges.reserve(vertices.size());

    for (std::size_t i = 1; i < vertices.size(); ++i)
      edges.push_back(getEdge(g, vertices[i - 1], vertices[i]));

    return edges;
  }

  /**
   * @brief Get the edge path source vertex.
   *
   * @param g The graph.
   * @param edges The edge path.
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex edgePathSource(const Graph &g,
      const EdgePath<Graph> &edges)
  {
    if (edges.empty())
      return nullVertex<Graph>();

    if (edges.size() == 1)
      return getSource(g, edges.front());

    return getOther(g, edges.front(),
        commonVertex(g, edges.front(), edges[1]));
  }

  /**
   * @brief Get the edge path target vertex.
   *
   * @param g The graph.
   * @param edges The edge path.
   */
  template<typename Graph>
  typename GraphTraits<Graph>::Vertex edgePathTarget(const Graph &g,
      const EdgePath<Graph> &edges)
  {
    if (edges.empty())
      return nullVertex<Graph>();

    if (edges.size() == 1)
      return getTarget(g, edges.front());

    return getOther(g, edges.back(),
        commonVertex(g, edges.back(), edges[edges.size() - 1]));
  }

  /**
   * @brief Convert an edge path to the corresponding vertex path.
   *
   * @param g The graph.
   * @param edges The edge path.
   */
  template<typename Graph>
  VertexPath<Graph> edgePathToVertexPath(const Graph &g, const EdgePath<Graph> &edges)
  {
    if (edges.empty())
      return VertexPath<Graph>();

    VertexPath<Graph> vertices;
    vertices.reserve(edges.size() + 1);

    vertices.push_back(edgePathSource(g, edges));
    for (std::size_t i = 1; i < edges.size(); ++i) {
      auto e1 = edges[i - 1];
      auto e2 = edges[i];
      vertices.push_back(commonVertex(g, e1, e2));
    }
    vertices.push_back(edgePathTarget(g, edges));

    return vertices;
  }

  /**
   * @brief A list of vertex paths.
   */
  template<typename Graph>
  using VertexPathList = std::vector<VertexPath<Graph>>;

  /**
   * @brief A list of edge paths.
   */
  template<typename Graph>
  using EdgePathList = std::vector<EdgePath<Graph>>;

} // namespace ocgl

#endif // OCGL_PATH_H
