#ifndef OCGL_PATH_H
#define OCGL_PATH_H

#include <ocgl/GraphTraits.h>

/**
 * @file Path.h
 * @brief Path classes and functions.
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
    for (auto i = 1; i < p.size(); ++i)
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
    for (auto i = 1; i < p.size(); ++i)
      if (commonVertex(g, p[i - 1], p[i]) == nullVertex<Graph>())
        return false;
    return true;
  }

  // fwd declaration
  template<typename Graph>
  class EdgePath;

  /**
   * @class VertexPath Path.h <ocgl/Path.h>
   * @brief Vertex path in a graph.
   */
  template<typename Graph>
  class VertexPath : public VertexList<Graph>
  {
    public:
      /**
       * @brief Default constructor.
       */
      VertexPath() = default;

      /**
       * @brief Copy constructor.
       */
      VertexPath(const VertexPath<Graph> &other) = default;

      /**
       * @brief Move constructor.
       */
      VertexPath(VertexPath<Graph> &&other) = default;

      /**
       * @brief Copy assignment.
       */
      VertexPath<Graph>& operator=(const VertexPath<Graph> &other) = default;

      /**
       * @brief Move assignment.
       */
      VertexPath<Graph>& operator=(VertexPath<Graph> &&other) = default;

      /**
       * @brief Copy constructor for vertex list.
       */
      explicit VertexPath(const VertexList<Graph> &vertices)
        : VertexList<Graph>(vertices)
      {
      }

      /**
       * @brief Move constructor for vertex list.
       */
      explicit VertexPath(VertexList<Graph> &&vertices)
        : VertexList<Graph>(std::move(vertices))
      {
      }

      /**
       * @brief Constructor for vertex initializer list.
       */
      explicit VertexPath(std::initializer_list<typename
          GraphTraits<Graph>::Vertex> vertices) : VertexList<Graph>(vertices)
      {
      }

      /**
       * @brief Get the corresponding edge path.
       *
       * The edge path is not cached (i.e. it is reconstructed each time this
       * function is called).
       *
       * @param g The graph.
       */
      EdgePath<Graph> edges(const Graph &g) const
      {
        EdgePath<Graph> result;
        result.reserve(this->size());

        for (auto i = 1; i < this->size(); ++i)
          result.push_back(getEdge(g, this->operator[](i - 1),
                                      this->operator[](i)));
        return result;
      }
  };

  /**
   * @class EdgePath Path.h <ocgl/Path.h>
   * @brief Edge path in a graph.
   */
  template<typename Graph>
  class EdgePath : public EdgeList<Graph>
  {
    public:
      /**
       * @brief Default constructor.
       */
      EdgePath() = default;

      /**
       * @brief Copy constructor.
       */
      EdgePath(const EdgePath<Graph> &other) = default;

      /**
       * @brief Move constructor.
       */
      EdgePath(EdgePath<Graph> &&other) = default;

      /**
       * @brief Copy assignment.
       */
      EdgePath<Graph>& operator=(const EdgePath<Graph> &other) = default;

      /**
       * @brief Move assignment.
       */
      EdgePath<Graph>& operator=(EdgePath<Graph> &&other) = default;

      /**
       * @brief Copy constructor for edge list.
       */
      explicit EdgePath(const EdgeList<Graph> &edges)
        : EdgeList<Graph>(edges)
      {
      }

      /**
       * @brief Move constructor for edge list.
       */
      explicit EdgePath(EdgeList<Graph> &&edges)
        : EdgeList<Graph>(std::move(edges))
      {
      }

      /**
       * @brief Constructor for edge initializer list.
       */
      explicit EdgePath(std::initializer_list<typename
          GraphTraits<Graph>::Edge> edges) : EdgeList<Graph>(edges)
      {
      }

      /**
       * @brief Get the path source vertex.
       *
       * @param g The graph.
       */
      typename GraphTraits<Graph>::Vertex source(const Graph &g) const
      {
        if (this->empty())
          return nullVertex<Graph>();

        if (this->size() == 1)
          return getSource(g, this->front());

        return getOther(g, this->front(),
            commonVertex(g, this->front(), this->operator[](1)));
      }

      /**
       * @brief Get the path target vertex.
       *
       * @param g The graph.
       */
      typename GraphTraits<Graph>::Vertex target(const Graph &g) const
      {
        if (this->empty())
          return nullVertex<Graph>();

        if (this->size() == 1)
          return getTarget(g, this->front());

        return getOther(g, this->back(),
            commonVertex(g, this->back(), this->operator[](this->size() - 1)));
      }

      /**
       * @brief Get the corresponding vertex path.
       *
       * The vertex path is not cached (i.e. it is reconstructed each time this
       * function is called).
       *
       * @param g The graph.
       */
      VertexPath<Graph> vertices(const Graph &g) const
      {
        if (this->empty())
          return VertexPath<Graph>();

        VertexPath<Graph> result;
        result.reserve(this->size() + 1);

        result.push_back(source(g));
        for (auto i = 1; i < this->size(); ++i) {
          auto e1 = this->operator[](i - 1);
          auto e2 = this->operator[](i);
          result.push_back(commonVertex(g, e1, e2));
        }
        result.push_back(target(g));

        return result;
      }
  };

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
