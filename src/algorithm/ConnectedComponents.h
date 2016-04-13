#ifndef OCGL_ALGORITHM_CONNECTED_COMPONENTS_H
#define OCGL_ALGORITHM_CONNECTED_COMPONENTS_H

#include <ocgl/algorithm/DFS.h>
#include <ocgl/Subgraph.h>
#include <ocgl/predicate/HasProperty.h>

/**
 * @file ConnectedComponents.h
 * @brief Connected components algorithms.
 */

namespace ocgl {

  namespace algorithm {

    namespace impl {

      template<typename Graph>
      class ConnectedComponentsDFSVisitor : public DFSVisitor<Graph>
      {
        public:
          using Vertex = typename GraphTraits<Graph>::Vertex;
          using Edge = typename GraphTraits<Graph>::Edge;

          ConnectedComponentsDFSVisitor(
              VertexEdgePropertyMap<Graph, unsigned int> &component)
            : m_component(component)
          {
          }

          void component(const Graph&, unsigned int i)
          {
            m_current = i;
          }

          void vertex(const Graph&, Vertex v)
          {
            m_component.vertices[v] = m_current;
          }

          void edge(const Graph&, Edge e)
          {
            m_component.edges[e] = m_current;
          }

          void backEdge(const Graph&, Edge e)
          {
            m_component.edges[e] = m_current;
          }

        private:
          // the current component
          int m_current;
          // map : vertex/edge -> component index
          VertexEdgePropertyMap<Graph, unsigned int> &m_component;
      };

    } // namespace impl


    /**
     * @brief Determine the connected components.
     *
     * Example:
     * @include algorithm/ConnectedComponents.cpp
     */
    template<typename Graph>
    VertexEdgePropertyMap<Graph, unsigned int> connectedComponents(const Graph &g)
    {
      // create property map to hold result
      VertexEdgePropertyMap<Graph, unsigned int> result(g);
      // create DFS visitor
      impl::ConnectedComponentsDFSVisitor<Graph> visitor(result);
      // run DFS algorithm
      dfs(g, visitor);
      // return rsult
      return result;
    }

    /**
     * @brief Determine the number of connected components.
     *
     * @param components The connected components (see connectedComponents()).
     */
    template<typename Graph>
    unsigned int numConnectedComponents(const VertexEdgePropertyMap<Graph,
        unsigned int> &components)
    {
      if (!numVertices(components.graph()))
        return 0;

      unsigned int max = 0;
      for (auto v : getVertices(components.graph()))
        max = std::max(max, components.vertices[v]);
      return max + 1;
    }

    /**
     * @brief Determine the number of connected components.
     *
     * @param g The graph.
     */
    template<typename Graph>
    unsigned int numConnectedComponents(const Graph &g)
    {
      return numConnectedComponents(connectedComponents(g));
    }

    /**
     * @brief Get a list of connected component subgraphs.
     *
     * @param g The graph.
     * @param components The connected components.
     */
    template<typename Graph>
    std::vector<typename Subgraph<Graph>::Sub> connectedComponentsSubgraphs(const Graph &g,
        const VertexEdgePropertyMap<Graph, unsigned int> &components)
    {
      auto numComponents = numConnectedComponents(components);

      std::vector<typename Subgraph<Graph>::Sub> subgraphs;
      for (unsigned int i = 0; i < numComponents; ++i) {
        subgraphs.push_back(makeSubgraph(g,
              predicate::HasPropertyEQ(components.vertices, i),
              predicate::HasPropertyEQ(components.edges, i)));
      }

      return subgraphs;
    }

    /**
     * @brief Get a list of connected component subgraphs.
     *
     * @param g The graph.
     */
    template<typename Graph>
    std::vector<typename Subgraph<Graph>::Sub> connectedComponentsSubgraphs(const Graph &g)
    {
      return connectedComponentsSubgraphs(g, connectedComponents(g));
    }


  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_CONNECTED_COMPONENTS_H
