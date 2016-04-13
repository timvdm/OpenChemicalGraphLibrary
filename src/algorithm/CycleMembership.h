#ifndef OCGL_ALGORITHM_CYCLE_MEMBERSHIP_H
#define OCGL_ALGORITHM_CYCLE_MEMBERSHIP_H

#include <ocgl/algorithm/DFS.h>

/**
 * @file CycleMembership.h
 * @brief Cycle membership algorithm.
 */

namespace ocgl {

  namespace algorithm {

    namespace impl {

      template<typename Graph>
      struct CycleMembershipDFSVisitor : public DFSVisitor<Graph>
      {
        public:
          using Vertex = typename GraphTraits<Graph>::Vertex;
          using Edge = typename GraphTraits<Graph>::Edge;

          CycleMembershipDFSVisitor(VertexEdgePropertyMap<Graph, bool> &cyclic)
            : m_cyclic(cyclic)
          {
          }

          void initialize(const Graph &g)
          {
            path.reserve(numVertices(g));
          }

          void component(const Graph&, unsigned int)
          {
            path.clear();
          }

          void vertex(const Graph&, Vertex v)
          {
            path.push_back(v);
          }

          void backEdge(const Graph &g, Edge e)
          {
            auto vLast = getOther(g, e, path.back());

            m_cyclic.vertices[vLast] = true;
            m_cyclic.edges[e] = true;

            // traceback the path to lastVertex
            for (std::size_t i = 0; i < path.size(); ++i) {
              auto v = path[path.size() - i - 1];
              // mark edge as cyclic
              if (i) {
                auto e2 = getEdge(g, v, path[path.size() - i]);
                m_cyclic.edges[e2] = true;
              }
              // stop when the atom closing the cycle is found
              if (v == vLast)
                break;
              // mark vertex as cyclic
              m_cyclic.vertices[v] = true;
            }
          }

          void finishVertex(const Graph&, Vertex)
          {
            path.pop_back();
          }

        private:
          // the current DFS path
          std::vector<Vertex> path;
          // map : vertex/edge -> cycle membership
          VertexEdgePropertyMap<Graph, bool> &m_cyclic;
      };

    } // namespace impl

    /**
     * @brief Determine vertex and edge cycle membership.
     *
     * @param graph The graph.
     *
     * @return The vertex and edge cycle membership as property maps.
     *
     * Example:
     * @include algorithm/CycleMembership.cpp
     */
    template<typename Graph>
    VertexEdgePropertyMap<Graph, bool> cycleMembership(const Graph &graph)
    {
      // create the vertex/edge property map to hold the result
      VertexEdgePropertyMap<Graph, bool> result(graph);
      // create the DFS visitor
      impl::CycleMembershipDFSVisitor<Graph> visitor(result);
      // run DFS
      dfs(graph, visitor);
      // return result
      return result;
    }

  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_CYCLE_MEMBERSHIP_H
