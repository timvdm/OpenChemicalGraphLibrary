#ifndef OCGL_CYCLE_H
#define OCGL_CYCLE_H

#include <ocgl/Path.h>
#include <ocgl/algorithm/ConnectedComponents.h>

/**
 * @file Cycle.h
 * @brief Functions for working with vertex and edge cycles.
 */

namespace ocgl {

  /**
   * @brief Vertex cycle in a graph.
   */
  template<typename Graph>
  using VertexCycle = VertexList<Graph>;

  /**
   * @brief Edge cycle in a graph.
   */
  template<typename Graph>
  using EdgeCycle = EdgeList<Graph>;

  /**
   * @brief Convert a vertex cycle to the corresponding edge cycle.
   *
   * @param g The graph.
   * @param vertices The vertex cycle.
   */
  template<typename Graph>
  EdgeCycle<Graph> vertexCycleToEdgeCycle(const Graph &g,
      const VertexCycle<Graph> &vertices)
  {
    if (vertices.size() < 3)
      return EdgeCycle<Graph>();

    EdgeCycle<Graph> edges;
    edges.reserve(vertices.size());

    for (auto i = 1; i < vertices.size(); ++i) {
      auto v1 = vertices[i - 1];
      auto v2 = vertices[i];
      edges.push_back(getEdge(g, v1, v2));
    }

    edges.push_back(getEdge(g, vertices.front(), vertices.back()));

    return edges;
  }


  /**
   * @brief Convert an edge cycle to the corresponding vertex cycle.
   *
   * @param g The graph.
   * @param edges The edge cycle.
   */
  template<typename Graph>
  VertexCycle<Graph> edgeCycleToVertexCycle(const Graph &g,
      const EdgeCycle<Graph> &edges)
  {
    if (edges.size() < 3)
      return VertexCycle<Graph>();

    VertexCycle<Graph> vertices;
    vertices.reserve(edges.size());

    vertices.push_back(edgePathSource(g, edges));
    for (auto i = 1; i < edges.size(); ++i) {
      auto e1 = edges[i - 1];
      auto e2 = edges[i];
      vertices.push_back(commonVertex(g, e1, e2));
    }

    return vertices;
  }

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
