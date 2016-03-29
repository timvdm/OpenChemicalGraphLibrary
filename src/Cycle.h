#ifndef OCGL_CYCLE_H
#define OCGL_CYCLE_H

#include <ocgl/algorithm/ConnectedComponents.h>

namespace ocgl {

  template<typename Graph>
  using VertexPath = std::vector<typename GraphTraits<Graph>::Vertex>;

  template<typename Graph>
  using EdgePath = std::vector<typename GraphTraits<Graph>::Edge>;


  template<typename Graph>
  using VertexCycle = std::vector<typename GraphTraits<Graph>::Vertex>;

  template<typename Graph>
  using EdgeCycle = std::vector<typename GraphTraits<Graph>::Edge>;


  template<typename Graph>
  using VertexCycles = std::vector<VertexCycle<Graph>>;

  template<typename Graph>
  using EdgeCycles = std::vector<EdgeCycle<Graph>>;

  /**
   * @brief Get the cyclomatic number.
   *
   * The cyclomatic number is defined by \f$m - n + c\f$ where \f$n\f$ is the
   * number of vertices, \f$m\f$ the number of edges and \f$c\f$ the number of
   * connected components. This formula is known as Cauchy's formula. The
   * cyclomatic number is the same as the nullity or first Betti's number.
   *
   * @param g The graph.
   * @param numComponents The number of connected components.
   *
   * @return The cyclomatic number.
   */
  template<typename Graph>
  unsigned int cyclomaticNumber(const Graph &g, unsigned int numComponents)
  {
    return numEdges(g) - numVertices(g) + numComponents;
  }

  /**
   * @brief Get the cyclomatic number.
   *
   * The cyclomatic number is defined by \f$m - n + c\f$ where \f$n\f$ is the
   * number of vertices, \f$m\f$ the number of edges and \f$c\f$ the number of
   * connected components. This formula is known as Cauchy's formula. The
   * cyclomatic number is the same as the nullity or first Betti's number.
   *
   * @param g The graph.
   *
   * @return The cyclomatic number.
   */
  template<typename Graph>
  unsigned int cyclomaticNumber(const Graph &g)
  {
    return cyclomaticNumber(g, algorithm::numConnectedComponents(g));
  }

  template<typename Graph>
  EdgeCycle<Graph> edgeCycleFromVertexCycle(const Graph &g, const VertexCycle<Graph> &cycle)
  {
    EdgeCycle<Graph> result;

    for (std::size_t i = 1; i < cycle.size(); ++i)
      result.push_back(getEdge(g, cycle[i-1], cycle[i]));
    result.push_back(getEdge(g, cycle.front(), cycle.back()));

    return result;
  }

} // namespace ocgl

#endif // OCGL_CYCLE_H
