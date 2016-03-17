#ifndef OCGL_ALGORITHM_DFS_H
#define OCGL_ALGORITHM_DFS_H

#include <ocgl/PropertyMap.h>

/**
 * @file DFS.h
 * @brief Depth-first search algorithm.
 */

namespace ocgl {

  /**
   * @namespace ocgl::algorithm
   * @brief Algorithms namespace.
   */
  namespace algorithm {

    /**
     * @class DFSVisitor DFS.h <ocgl/algorithm/DFS.h>
     * @brief Base class for depth first search (DFS) visitors.
     */
    template<typename Graph>
    struct DFSVisitor
    {
      /**
       * @brief The vertex type.
       */
      using Vertex = typename GraphTraits<Graph>::Vertex;
      /**
       * @brief The edge type.
       */
      using Edge = typename GraphTraits<Graph>::Edge;

      /**
       * @brief Initialize the visitor.
       *
       * This function is called once when the DFS search is started.
       *
       * @param g The graph.
       */
      void initialize(const Graph &g) {}

      /**
       * @brief A new component starts.
       *
       * @param g The graph.
       * @param i The component (i.e. [0,n])
       */
      void component(const Graph &g, unsigned int i) {}

      /**
       * @brief Visit a vertex.
       *
       * This function is called every time a new vertex is traversed.
       *
       * @param g The graph.
       * @param v The traversed vertex.
       */
      void vertex(const Graph &g, Vertex v) {}

      /**
       * @brief Visit an edge.
       *
       * This function is called every time a new edge is traversed.
       *
       * @param g The graph.
       * @param e The traversed edge.
       */
      void edge(const Graph &g, Edge e) {}

      /**
       * @brief Visit a "back" edge.
       *
       * The "back" edges are the chords that would make the DFS spanning
       * graph cyclic.
       *
       * @param g The graph.
       * @param e The "back" edge.
       */
      void backEdge(const Graph &g, Edge e) {}

      /**
       * @brief Invoked when the edge's target vertex is finished.
       *
       * @note This function is not invoked for back edges.
       *
       * @param g The graph.
       * @param e The edge.
       */
      void finishEdge(const Graph &g, Edge e) {}

      /**
       * @brief Invoked when all edges are finished.
       *
       * @param g The graph.
       * @param v The vertex
       */
      void finishVertex(const Graph &g, Vertex v) {}
    };

    namespace impl {

      /**
       * @brief Basic DFS recursive function.
       */
      template<typename Graph, typename DFSVisitor>
      void dfs(const Graph &g, typename GraphTraits<Graph>::Vertex v,
          DFSVisitor &visitor, VertexEdgePropertyMap<Graph, bool> &visited)
      {
        // mark vertex as visited
        visited.vertices[v] = true;
        // invoke vertex visitor
        visitor.vertex(g, v);

        // call impl::dfs for all unvisited neighbors of v
        for (auto e : getIncident(g, v)) {
          // skip already visited edges
          if (visited.edges[e])
            continue;

          auto w = getOther(g, e, v);

          if (visited.vertices[w]) {
            // if this edge has not been visited before, a back edge has been found
            if (!visited.edges[e]) {
              // invoke back edge visitor
              visitor.backEdge(g, e);
              // mark edge as visited
              visited.edges[e] = true;
            }
            continue;
          }

          // mark edge as visited
          visited.edges[e] = true;
          // invoke edge visitor
          visitor.edge(g, e);

          dfs(g, w, visitor, visited);

          // invoke finish edge visitor
          visitor.finishEdge(g, e);
        }

        // invoke finish vertex visitor
        visitor.finishVertex(g, v);
      }

    } // namespace impl

    /**
     * @brief Perform a depth-first search on a graph (DFS).
     *
     * This depth-first search function considers all components and walks a
     * single spanning tree for each component. The vertex with the lowest
     * index from each component is used as root of the resulting spanning
     * tree to start the search.
     *
     * This function makes use of a visitor functor to allow actions to be
     * performed. Visitors can be implemented by inheriting the DFSVisitor
     * class and reimplementing the required functions.
     *
     * @param g The graph.
     * @param visitor The DFS visitor.
     *
     * Example:
     * @include algorithm/DFS.cpp
     */
    template<typename Graph, typename DFSVisitor>
    void dfs(const Graph &g, DFSVisitor &visitor)
    {
      visitor.initialize(g);

      // keep track of visited vertices and edges using property maps
      VertexEdgePropertyMap<Graph, bool> visited(g);

      unsigned int c = 0;
      for (auto v : getVertices(g)) {
        if (!visited.vertices[v]) {
          // invoke component visitor
          visitor.component(g, c++);
          // initiate DFS for component
          impl::dfs(g, v, visitor, visited);
        }
      }
    }

    /**
     * @brief Perform a depth-first search on a component (DFS).
     *
     * This depth-first search function considers a single components and walks
     * a single spanning tree for that component. The component is specified by
     * the supplied vertex which is also the root of the resulting spanning
     * tree.
     *
     * This function makes use of a visitor functor to allow actions to be
     * performed. Visitors can be implemented by inheriting the DFSVisitor
     * class and reimplementing the required functions.
     *
     * @param g The graph.
     * @param v The start vertex.
     * @param visitor The DFS visitor.
     */
    template<typename Graph, typename DFSVisitor>
    void dfs(const Graph &g, typename GraphTraits<Graph>::Vertex v,
        DFSVisitor &visitor)
    {
      visitor.initialize(g);

      // keep track of visited vertices and edges using property maps
      VertexEdgePropertyMap<Graph, bool> visited(g);

      // initiate DFS for component
      impl::dfs(g, v, visitor, visited);
    }

  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_DFS_H
