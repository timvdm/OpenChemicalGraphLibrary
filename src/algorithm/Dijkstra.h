#ifndef OCGL_ALGORITHM_DIJKSTRA_H
#define OCGL_ALGORITHM_DIJKSTRA_H

#include <ocgl/Path.h>
#include <ocgl/PropertyMap.h>
#include <ocgl/Predicates.h>

#include <algorithm>
#include <vector>
#include <limits>

/**
 * @file Dijkstra.h
 * @brief Dijkstra's shortest path algorithm.
 */

namespace ocgl {

  namespace algorithm {

    namespace impl {

      template<typename Graph>
      struct DijkstraHeapCompare
      {
        using Vertex = typename GraphTraits<Graph>::Vertex;

        DijkstraHeapCompare(const VertexPropertyMap<Graph, unsigned int> &dist_)
          : dist(dist_)
        {
        }

        bool operator()(Vertex u, Vertex v) const
        {
          return dist[u] >= dist[v];
        }

        const VertexPropertyMap<Graph, unsigned int> &dist;
      };

    } // namespace impl

    /**
     * @brief Dijkstra's shortest path algorithm.
     *
     * The Dijkstra shortest path algorithm finds a shortest path from a source
     * vertex to all other vertices in a graph. The algorithm is executed when
     * the constructor is executed. Later, the distances and paths can be
     * retrieved using the distance() and path() member functions.
     */
    template<typename Graph>
    class Dijkstra
    {
      public:
        /**
         * @brief The vertex type.
         */
        using Vertex = typename GraphTraits<Graph>::Vertex;

        /**
         * @brief Constructor.
         *
         * Using this constructor, all vertices will be considered.
         *
         * @param g The graph.
         * @param source The source vertex.
         */
        Dijkstra(const Graph &g, Vertex source)
          : m_graph(g), m_source(source), m_dist(g, infinity()),
            m_prev(g, nullVertex<Graph>())
        {
          // add all vertices in graph to Q
          std::vector<Vertex> Q = getVertices(g).toVector();

          VertexPropertyMap<Graph, bool> vertexMask(g, true);
          dijkstra(Q, vertexMask);
        }

        /**
         * @brief Constructor.
         *
         * Using this constructor, only the vertices in the mask will be
         * considered.
         *
         * @param g The graph.
         * @param source The source vertex.
         * @param vertexMask The vertex mask.
         */
        Dijkstra(const Graph &g, Vertex source,
            const VertexPropertyMap<Graph, bool> &vertexMask)
          : m_graph(g), m_source(source), m_dist(g, infinity()),
            m_prev(g, nullVertex<Graph>())
        {
          // add all vertices in graph to Q
          std::vector<Vertex> Q = getVertices(g,
              HasPropertyEQ(vertexMask, true)).toVector();

          dijkstra(Q, vertexMask);
        }

        /**
         * @brief Get the source vertex.
         */
        Vertex source() const
        {
          return m_source;
        }

        /**
         * @brief Get the infinity value that is returned by distance().
         *
         * @return The infinity value.
         */
        unsigned int infinity() const
        {
          return std::numeric_limits<unsigned int>::max();
        }

        /**
         * @brief Get the distance between source and target vertices.
         *
         * The distance is the number of bonds between the source and target
         * vertices. If there is no path, the infinity() value is returned.
         *
         * @param target the target vertex.
         */
        unsigned int distance(Vertex target) const
        {
          return m_dist[target];
        }

        /**
         * @brief Reconstruct the path between source and target vertices.
         *
         * The path includes the source and target vertices
         * (i.e. [source, ..., target]).
         *
         * @param target the target vertex.
         */
        VertexPath<Graph> path(Vertex target) const
        {
          VertexPath<Graph> S;
          S.reserve(distance(target) + 1);
          Vertex u = target;

          // reconstruct the path
          while (isValid(m_graph, m_prev[u])) {
            S.insert(S.begin(), u);
            u = m_prev[u];
          }

          S.insert(S.begin(), m_source);

          return S;
        }

        /**
         * @brief Reconstruct the reverse path between target and source vertices.
         *
         * The path includes the source and target vertices
         * (i.e. [target, ..., source]).
         *
         * @param target the target vertex.
         */
        VertexPath<Graph> reversePath(Vertex target) const
        {
          VertexPath<Graph> S;
          S.reserve(distance(target) + 1);
          Vertex u = target;

          // reconstruct the path
          while (isValid(m_graph, m_prev[u])) {
            S.push_back(u);
            u = m_prev[u];
          }

          S.push_back(m_source);

          return S;
        }

        /**
         * @brief Get the map with previous vertices.
         *
         * This map gives, for each vertex, the previous vertex for the shortest
         * path to source.
         */
        const VertexPropertyMap<Graph, Vertex>& prev() const
        {
          return m_prev;
        }

      private:
        void dijkstra(std::vector<Vertex> &Q,
            const VertexPropertyMap<Graph, bool> &vertexMask)
        {
          // distance from source to source
          m_dist[m_source] = 0;

          // make Q a heap [heap implementation only]
          using HeapCompare = typename impl::DijkstraHeapCompare<Graph>;
          std::make_heap(Q.begin(), Q.end(), HeapCompare(m_dist));

          while (Q.size()) {
            // find vertex in Q with smallest distance in m_dist
            Vertex u = Q.front();
            // remove u from Q
            std::pop_heap(Q.begin(), Q.end(), HeapCompare(m_dist));
            Q.pop_back();

            if (m_dist[u] == infinity())
              // all remaining vertices are inaccessible from source
              break;

            for (auto v : getAdjacent(m_graph, u)) {
              if (!vertexMask[v])
                continue;

              unsigned int alt = m_dist[u] + 1;

              if (alt < m_dist[v]) {
                m_dist[v] = alt;
                m_prev[v] = u;
                std::make_heap(Q.begin(), Q.end(), HeapCompare(m_dist));
              }
            }

          }
        }

        const Graph &m_graph;
        Vertex m_source;
        VertexPropertyMap<Graph, unsigned int> m_dist;
        VertexPropertyMap<Graph, Vertex> m_prev;
    };

  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_DIJKSTRA_H
