#ifndef OCGL_ALGORITHM_RELEVANT_CYCLES_H
#define OCGL_ALGORITHM_RELEVANT_CYCLES_H

#include <ocgl/Path.h>
#include <ocgl/Cycle.h>
#include <ocgl/CycleSpace.h>
#include <ocgl/BitMatrix.h>
#include <ocgl/algorithm/Dijkstra.h>
#include <ocgl/algorithm/CycleMembership.h>

/**
 * @file RelevantCycles.h
 * @brief Relevant cycles.
 */

namespace ocgl {

  namespace algorithm {

    namespace impl {

      template<bool IsUndirected>
      class AdjacencyMatrix
      {
        public:
          AdjacencyMatrix(unsigned int numVertices)
            : m_adjMatrix(numVertices * numVertices), m_numVertices(numVertices)
          {
          }

          void addEdge(unsigned int source, unsigned int target)
          {
            m_adjMatrix[index(source, target)] = true;

            if (IsUndirected)
              m_adjMatrix[index(target, source)] = true;
          }

          bool isEdge(unsigned int source, unsigned int target) const
          {
            return m_adjMatrix[index(source, target)];
          }

        private:
          unsigned int index(unsigned int s, unsigned int t) const
          {
            return s * m_numVertices + t;
          }

          std::vector<bool> m_adjMatrix;
          unsigned int m_numVertices;
      };

      using DirectedAdjacencyMatrix = AdjacencyMatrix<false>;
      using UndirectedAdjacencyMatrix = AdjacencyMatrix<true>;

      template<typename Graph, typename Vertex>
      bool pathsIntersectionIsSource(const Dijkstra<Graph> &dijkstra,
          const Graph &g, Vertex y, Vertex z)
      {
        Vertex u = y;

        while (isValid(g, dijkstra.prev()[u])) {
          Vertex v = z;
          while (isValid(g, dijkstra.prev()[v])) {
            if (u == v)
              return false;
            v = dijkstra.prev()[v];
          }
          u = dijkstra.prev()[u];
        }

        return true;
      }

      /**
       * @brief Cycle family from the Vismara paper.
       *
       * A cycle family consists of a vertex r and 2 equal length shortest paths
       * to vertices p and q. For odd cycles, the p and q vertex are connected
       * by an edge. For even cycles, an additional vertex x connects p and q.
       *
       *      ------ p         ------ p
       *    /        |       /          \
       *   r         |      r            x
       *    \        |       \          /
       *      ------ q         ------ q
       *
       * A family prototype cycle is used to select relevant families (all family
       * members are relevant if the prototype is relevant). The directed graph
       * Dr is used to enumerate all shortest paths between the vertex r and the
       * vertices p and q.
       */
      template<typename Graph>
      class CycleFamily
      {
        public:
          /**
           * @brief Teh vertex type.
           */
          using Vertex = typename GraphTraits<Graph>::Vertex;

          /**
           * @brief Constructor for odd cycle families.
           *
           * @param r The r vertex.
           * @param p The p vertex.
           * @param q The q vertex.
           * @param prototype A prototype cycle for the family.
           */
          CycleFamily(const Graph &g, Vertex r, Vertex p, Vertex q,
              const VertexCycle<Graph> &prototype,
              const std::shared_ptr<impl::DirectedAdjacencyMatrix> &Dr)
            : m_graph(&g), m_r(r), m_p(p), m_q(q), m_x(nullVertex<Graph>()),
              m_prototype(prototype), m_Dr(Dr)
          {
          }

          /**
           * @brief Constructor for even cycle families.
           *
           * @param r The r vertex.
           * @param p The p vertex.
           * @param q The q vertex.
           * @param x The x vertex.
           * @param prototype A prototype cycle for the family.
           */
          CycleFamily(const Graph &g, Vertex r, Vertex p, Vertex q, Vertex x,
              const VertexCycle<Graph> &prototype,
              const std::shared_ptr<DirectedAdjacencyMatrix> &Dr)
            : m_graph(&g), m_r(r), m_p(p), m_q(q), m_x(x),
              m_prototype(prototype), m_Dr(Dr)
          {
          }

          /**
           * @brief Get the r vertex.
           */
          Vertex r() const
          {
            return m_r;
          }

          /**
           * @brief Get the p vertex.
           */
          Vertex p() const
          {
            return m_p;
          }

          /**
           * @brief Get the q vertex.
           */
          Vertex q() const
          {
            return m_q;
          }

          /**
           * @brief Get the x vertex.
           */
          Vertex x() const
          {
            return m_x;
          }

          /**
           * @brief Get the prototype cycle.
           */
          const VertexCycle<Graph>& prototype() const
          {
            return m_prototype;
          }

          const DirectedAdjacencyMatrix& Dr() const
          {
            return *m_Dr;
          }

          /**
           * @return True if this is an odd cycle.
           */
          bool isOdd() const
          {
            return isNull(*m_graph, m_x);
          }

          /**
           * @return True if this is an even cycle.
           */
          bool isEven() const
          {
            return isValid(*m_graph, m_x);
          }

          bool operator<(const CycleFamily &other) const
          {
            return m_prototype.size() < other.m_prototype.size();
          }

          /**
           * @brief Create an odd vertex cycle form paths to p and q.
           *
           * @param pr The path (p .. r).
           * @param qr The path (q .. r).
           *
           * @return The cycle (r .. p q ..).
           */
          static VertexCycle<Graph> cycleFromPaths(const VertexPath<Graph> &pr,
              const VertexPath<Graph> &qr)
          {
            VertexCycle<Graph> cycle;
            cycle.reserve(2 * pr.size() - 1);

            std::copy(pr.rbegin(), pr.rend(),
                std::back_inserter(cycle)); // P(r .. p)
            std::copy(qr.begin(), qr.begin() + qr.size() - 1,
                std::back_inserter(cycle)); // P(r .. p q ..)

            return cycle;
          }

          /**
           * @brief Create an even vertex cycle form paths to p and q.
           *
           * @param pr The path (p .. r).
           * @param x The x vertex.
           * @param qr The path (q .. r).
           *
           * @return The cycle (r .. p x q ..).
           */
          static VertexCycle<Graph> cycleFromPaths(const VertexPath<Graph> &pr,
              Vertex x, const VertexPath<Graph> &qr)
          {
            VertexCycle<Graph> cycle;
            cycle.reserve(2 * pr.size());

            std::copy(pr.rbegin(), pr.rend(),
                std::back_inserter(cycle)); // P(r .. p)
            cycle.push_back(x); // P(r .. p x)
            std::copy(qr.begin(), qr.begin() + qr.size() - 1,
                std::back_inserter(cycle)); // P(r .. p x q ..)

            return cycle;
          }

          /**
           * @brief Enumerate the cycle family members.
           */
          void enumerate(std::function<void(const VertexCycle<Graph>&)> callback) const
          {
            std::vector<VertexPath<Graph>> qrPaths;
            listPaths(m_q, [&qrPaths] (const VertexPath<Graph> &qr) {
              qrPaths.push_back(qr);
            });

            listPaths(m_p, [&] (const VertexPath<Graph> &pr) {
              for (auto &qr : qrPaths) {
                if (isOdd())
                  callback(cycleFromPaths(pr, qr));
                else
                  callback(cycleFromPaths(pr, m_x, qr));
              }
            });
          }

        private:
          /**
           * @brief Extend the current path from x to m_r.
           */
          void listPaths(Vertex x, VertexPath<Graph> &current,
              std::function<void(const VertexPath<Graph>&)> callback) const
          {
            // add v to the current path
            current.push_back(x);

            if (x == m_r) {
              // found a path (r .. x)
              callback(current);
            } else {
              // for any z such that (x, z) is in Ur
              for (Index zi = 0; zi <= getIndex(*m_graph, m_r); ++zi)
                if (m_Dr->isEdge(getIndex(*m_graph, x), zi))
                  listPaths(getVertex(*m_graph, zi), current, callback);
            }

            current.pop_back();
          }

          /**
           * @brief List all paths from vertex m_r to vertex x.
           */
          void listPaths(Vertex x,
              std::function<void(const VertexPath<Graph>&)> callback) const
          {
            VertexPath<Graph> current;
            current.reserve(m_prototype.size() / 2);
            listPaths(x, current, callback);
          }

          const Graph *m_graph;
          Vertex m_r;
          Vertex m_p;
          Vertex m_q;
          Vertex m_x;
          VertexCycle<Graph> m_prototype;
          std::shared_ptr<DirectedAdjacencyMatrix> m_Dr;
      };

      /**
       * @brief Find the initial Vismara cycle families.
       *
       * @param graph The graph.
       * @param circuitRank The circuit rank.
       * @param cycleMembership Vertex and edge cycle membership.
       */
      template<typename Graph>
      std::vector<CycleFamily<Graph>> initialCycleFamilies(const Graph &g,
          unsigned int circuitRank,
          const VertexEdgePropertyMap<Graph, bool> &cycleMembership)
      {
        using Vertex = typename GraphTraits<Graph>::Vertex;

        // V = {1, ..., n}  |V| = n
        // E = { (x, y) | there is an edge between x and y }  |E| = m
        // G = (V, E)
        //
        // pi: a random total order on V (i.e. vertex indexes)
        //
        // Vr = { z in V | there is a shortest path in G from r to z that passes only
        //                 through vertices which precede r in the ordering pi }

        // digraph Dr = (Vr, Ur)
        //
        // Ur = { directed edge (y, z) | (z, y) belongs to a shortest path in G from
        //                               r to y that passes only to through vertices
        //                               which precede r in the ordering pi }

        std::vector<impl::CycleFamily<Graph>> families;


        // allocate memory for Vr and S
        std::vector<Vertex> Vr;
        Vr.reserve(numVertices(g));
        std::vector<Vertex> S;
        S.reserve(numVertices(g));

        // for all r in V do
        for (auto r : getVertices(g)) {
          // skip non-cycle vertices...
          if (!cycleMembership.vertices[r])
            continue;

          // compute Vr and for all t in Vr find a shortest path P(r, t) from r to t
          VertexPropertyMap<Graph, bool> vertexMask(g);
          for (std::size_t i = 0; i < getIndex(g, r) + 1; ++i)
            vertexMask[i] = cycleMembership.vertices[getVertex(g, i)];
          Dijkstra<Graph> dijkstra(g, r, vertexMask);

          Vr.clear();
          for (std::size_t i = 0; i <= getIndex(g, r); ++i)
            if (dijkstra.distance(getVertex(g, i)) < dijkstra.infinity())
              Vr.push_back(getVertex(g, i));

          auto Dr = std::make_shared<impl::DirectedAdjacencyMatrix>(numVertices(g));;

          // for all y in Vr do
          for (auto y : Vr) {
            // S <- {}
            S.clear();

            // for all z in Vr such that z is adjacent to y
            for (auto z : getAdjacent(g, y)) {
              if (!std::binary_search(Vr.begin(), Vr.end(), z))
                continue;

              // if d(r, z) + w((z, y)) = d(r, y) then
              if (dijkstra.distance(z) + 1 == dijkstra.distance(y)) {
                // S <- S U {z}
                S.push_back(z);

                // add directed edge (y, z) to Dr
                Dr->addEdge(getIndex(g, y), getIndex(g, z));

              // else if d(r, z) != d(r, y) + w((z, y))
              //     and pi(z) < pi(y)
              //     and P(r, y) ^ P(r, z) = {r}
              // then
              } else if (dijkstra.distance(z) != dijkstra.distance(y) + 1 &&
                         getIndex(g, z) < getIndex(g, y) &&
                         impl::pathsIntersectionIsSource(dijkstra, g, y, z)) {

                // add to CI' the odd cycle C = P(r, y) + P(r, z) + (z, y)
                auto prototype = impl::CycleFamily<Graph>::cycleFromPaths(
                    dijkstra.reversePath(y), dijkstra.reversePath(z));

                families.push_back(impl::CycleFamily<Graph>(g, r, y, z,
                      prototype, Dr));
              }
            }

            // for any pair of vertices p, q in S such that P(r, p) ^ P(r, q) = {r} do
            for (std::size_t j = 0; j < S.size(); ++j)
              for (std::size_t k = j + 1; k < S.size(); ++k) {
                const Vertex &p = S[j];
                const Vertex &q = S[k];
                if (!impl::pathsIntersectionIsSource(dijkstra, g, p, q))
                  continue;

                // add to CI' the even cycle C = P(r .. p) + P(r .. q) + (p, y, q)
                auto prototype = impl::CycleFamily<Graph>::cycleFromPaths(
                    dijkstra.reversePath(p), y, dijkstra.reversePath(q));

                families.push_back(impl::CycleFamily<Graph>(g, r, p, q, y,
                      prototype, Dr));
              }
          }
        }

        return families;
      }

      /**
       * @brief Select the relevant families from the initial set of families.
       *
       * Families that are not relevant will be removed.
       *
       * @param g The graph.
       * @param families The initial set of cycle families.
       *
       * @post families contains only relevant cycle families.
       */
      template<typename Graph>
      void selectRelevantCycleFamilies(const Graph &g, unsigned int circuitRank,
          std::vector<CycleFamily<Graph>> &families)
      {
        // if there are no families, there is nothing to do..
        if (families.empty())
          return;

        // sort families by cycle size
        std::sort(families.begin(), families.end());

        // keep track of families that are not relevant
        std::vector<std::size_t> remove;
        // keep track of families that are relevant and not yet added to B
        // (i.e. families of the current cycle size being considered)
        std::vector<std::size_t> add;
        // the cycle space of cycles smaller than the current cycle size
        CycleSpace<Graph> cycleSpace(g, circuitRank);


        unsigned int lastSize = families.front().prototype().size();
        for (std::size_t i = 0; i < families.size(); ++i) {
          const impl::CycleFamily<Graph> &family = families[i];

          // update cycleSpace
          if (lastSize < family.prototype().size()) {
            // add newly added relevant family prototypes to cycleSpace
            for (auto j : add)
              cycleSpace.add(families[j].prototype());
            add.clear();

            // check if the cycle set is complete
            if (cycleSpace.isBasis()) {
              // all remaining families are not relevant
              while (i < families.size()) {
                remove.push_back(i);
                ++i;
              }
              break;
            }

            // update last cycle size
            lastSize = family.prototype().size();
          }

          if (cycleSpace.contains(family.prototype()))
            remove.push_back(i);
          else
            add.push_back(i);
        }

        // remove all families that are not relevant
        for (std::size_t i = 0; i < remove.size(); ++i)
          families.erase(families.begin() + remove[remove.size() - i - 1]);
      }

    } // namespace impl

    /**
     * @brief Find the relevant cycles using Vismara algorithm.
     *
     * @param g The graph.
     * @param circuitRank The circuit rank.
     * @param cycleMembership Vertex and edge cycle membership.
     *
     * @return The set of relevant cycles.
     */
    template<typename Graph>
    VertexCycleList<Graph> relevantCyclesVismara(const Graph &g, unsigned int circuitRank,
        const VertexEdgePropertyMap<Graph, bool> &cycleMembership)
    {
      // find initial set of cycle families
      std::vector<impl::CycleFamily<Graph>> families =
        impl::initialCycleFamilies(g, circuitRank, cycleMembership);

      // select relevant families
      impl::selectRelevantCycleFamilies(g, circuitRank, families);

      // enumerate relevant cycles
      VertexCycleList<Graph> cycles;
      for (auto &family : families)
        family.enumerate([&cycles] (const VertexCycle<Graph> &cycle) {
          cycles.push_back(cycle);
        });

      return cycles;
    }

    /**
     * @brief Find the relevant cycles.
     *
     * The set of relevant cycles is formed by taking the union of all the
     * minimum cycles bases. An alternative definition is that a cycle is
     * relevant if it is not the sum of smaller cycles.
     *
     * @param graph The graph.
     *
     * @return The set of relevant cycles.
     */
    template<typename Graph>
    VertexCycleList<Graph> relevantCycles(const Graph &graph)
    {
      auto cycleMember = cycleMembership(graph);
      return relevantCyclesVismara(graph, circuitRank(graph),
          cycleMember);
    }

  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_RELEVANT_CYCLES_H
