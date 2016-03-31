#ifndef OCGL_CYCLE_H
#define OCGL_CYCLE_H

#include <ocgl/Path.h>
#include <ocgl/algorithm/ConnectedComponents.h>

/**
 * @file Cycle.h
 * @brief Cycle classes and functions.
 */

namespace ocgl {

  // fwd declaration
  template<typename Graph>
  class EdgeCycle;

  /**
   * @class VertexCycle Cycle.h <ocgl/Cycle.h>
   * @brief Vertex cycle in a graph.
   */
  template<typename Graph>
  class VertexCycle : public VertexPath<Graph>
  {
    public:
      /**
       * @brief Default constructor.
       */
      VertexCycle() = default;

      /**
       * @brief Copy constructor.
       */
      VertexCycle(const VertexCycle<Graph> &other) = default;

      /**
       * @brief Move constructor.
       */
      VertexCycle(VertexCycle<Graph> &&other) = default;

      /**
       * @brief Copy assignment.
       */
      VertexCycle<Graph>& operator=(const VertexCycle<Graph> &other) = default;

      /**
       * @brief Move assignment.
       */
      VertexCycle<Graph>& operator=(VertexCycle<Graph> &&other) = default;

      /**
       * @brief Copy constructor for vertex list.
       */
      explicit VertexCycle(const VertexList<Graph> &vertices)
        : VertexPath<Graph>(vertices)
      {
      }

      /**
       * @brief Move constructor for vertex list.
       */
      explicit VertexCycle(VertexList<Graph> &&vertices)
        : VertexPath<Graph>(std::move(vertices))
      {
      }

      /**
       * @brief Constructor for vertex initializer list.
       */
      explicit VertexCycle(std::initializer_list<typename
          GraphTraits<Graph>::Vertex> vertices) : VertexPath<Graph>(vertices)
      {
      }

      /**
       * @brief Get the corresponding edge cycle.
       *
       * The edge cycle is not cached (i.e. it is reconstructed each time this
       * function is called).
       *
       * @param g The graph.
       */
      EdgeCycle<Graph> edges(const Graph &g) const
      {
        if (this->size() < 3)
         return EdgeCycle<Graph>();

        EdgeCycle<Graph> result;
        result.reserve(this->size());

        for (auto i = 1; i < this->size(); ++i) {
          auto v1 = this->operator[](i - 1);
          auto v2 = this->operator[](i);
          result.push_back(getEdge(g, v1, v2));
        }

        result.push_back(getEdge(g, this->front(), this->back()));

        return result;
      }
  };

  /**
   * @class EdgeCycle Cycle.h <ocgl/Cycle.h>
   * @brief Edge cycle in a graph.
   */
  template<typename Graph>
  class EdgeCycle : public EdgePath<Graph>
  {
    public:
      /**
       * @brief Default constructor.
       */
      EdgeCycle() = default;

      /**
       * @brief Copy constructor.
       */
      EdgeCycle(const EdgeCycle<Graph> &other) = default;

      /**
       * @brief Move constructor.
       */
      EdgeCycle(EdgeCycle<Graph> &&other) = default;

      /**
       * @brief Copy assignment.
       */
      EdgeCycle<Graph>& operator=(const EdgeCycle<Graph> &other) = default;

      /**
       * @brief Move assignment.
       */
      EdgeCycle<Graph>& operator=(EdgeCycle<Graph> &&other) = default;

      /**
       * @brief Copy constructor for edge list.
       */
      explicit EdgeCycle(const EdgeList<Graph> &edges)
        : EdgePath<Graph>(edges)
      {
      }

      /**
       * @brief Move constructor for edge list.
       */
      explicit EdgeCycle(EdgeList<Graph> &&edges)
        : EdgePath<Graph>(std::move(edges))
      {
      }

      /**
       * @brief Constructor for edge initializer list.
       */
      explicit EdgeCycle(std::initializer_list<typename
          GraphTraits<Graph>::Edge> edges) : EdgePath<Graph>(edges)
      {
      }

      /**
       * @brief Get the corresponding vertex cycle.
       *
       * The vertex cycle is not cached (i.e. it is reconstructed each time this
       * function is called).
       *
       * @param g The graph.
       */
      VertexCycle<Graph> vertices(const Graph &g) const
      {
        if (this->size() < 3)
          return VertexCycle<Graph>();

        VertexCycle<Graph> result;
        result.reserve(this->size());

        result.push_back(this->source(g));
        for (auto i = 1; i < this->size(); ++i) {
          auto e1 = this->operator[](i - 1);
          auto e2 = this->operator[](i);
          result.push_back(commonVertex(g, e1, e2));
        }

        return result;
      }
  };

  /**
   * @brief A list of vertex cycles.
   */
  template<typename Graph>
  using VertexCycleList = std::vector<VertexCycle<Graph>>;

  /**
   * @brief A list of edge cycles.
   */
  template<typename Graph>
  using EdgeCycleList = std::vector<EdgeCycle<Graph>>;

  /**
   * @brief Get the graph circuit rank.
   *
   * The circuit rank is defined by \f$m - n + c\f$ where \f$n\f$ is the
   * number of vertices, \f$m\f$ the number of edges and \f$c\f$ the number of
   * connected components. The circuit rank is also known as the cyclomatic
   * number or the nullity of the graph. In terms of algebraic graph theory it
   * is the dimension of the cycle space of the graph.
   *
   * @param g The graph.
   * @param numComponents The number of connected components.
   */
  template<typename Graph>
  unsigned int circuitRank(const Graph &g, unsigned int numComponents)
  {
    return numEdges(g) - numVertices(g) + numComponents;
  }

  /**
   * @brief Get the graph circuit rank.
   *
   * The circuit rank is defined by \f$m - n + c\f$ where \f$n\f$ is the
   * number of vertices, \f$m\f$ the number of edges and \f$c\f$ the number of
   * connected components. The circuit rank is also known as the cyclomatic
   * number or the nullity of the graph. In terms of algebraic graph theory it
   * is the dimension of the cycle space of the graph.
   *
   * @param g The graph.
   */
  template<typename Graph>
  unsigned int circuitRank(const Graph &g)
  {
    return circuitRank(g, algorithm::numConnectedComponents(g));
  }

} // namespace ocgl

#endif // OCGL_CYCLE_H
