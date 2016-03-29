#ifndef OCGL_ALGORITHM_RELEVANT_CYCLES_H
#define OCGL_ALGORITHM_RELEVANT_CYCLES_H

#include <ocgl/Cycle.h>
#include <ocgl/BitMatrix.h>
#include <ocgl/algorithm/Dijkstra.h>
#include <ocgl/algorithm/CycleMembership.h>

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
           * @param rp The path (r .. p).
           * @param rq The path (r .. q).
           *
           * @return The cycle (r .. p q ..).
           */
          static VertexCycle<Graph> cycleFromPaths(const VertexPath<Graph> &rp,
              const VertexPath<Graph> &rq)
          {
            VertexCycle<Graph> cycle;
            cycle.reserve(2 * rp.size() - 1);

            std::copy(rp.begin(), rp.end(),
                std::back_inserter(cycle)); // P(r .. p)
            std::copy(rq.rbegin(), rq.rbegin() + rq.size() - 1,
                std::back_inserter(cycle)); // P(r .. p q ..)

            return cycle;
          }

          /**
           * @brief Create an even vertex cycle form paths to p and q.
           *
           * @param rp The path (r .. p).
           * @param x The x vertex.
           * @param rq The path (r .. q).
           *
           * @return The cycle (r .. p x q ..).
           */
          static VertexCycle<Graph> cycleFromPaths(const VertexPath<Graph> &rp,
              Vertex x, const VertexPath<Graph> &rq)
          {
            VertexCycle<Graph> cycle;
            cycle.reserve(2 * rp.size());

            std::copy(rp.begin(), rp.end(),
                std::back_inserter(cycle)); // P(r .. p)
            cycle.push_back(x); // P(r .. p x)
            std::copy(rq.rbegin(), rq.rbegin() + rq.size() - 1,
                std::back_inserter(cycle)); // P(r .. p x q ..)

            return cycle;
          }

          /**
           * @brief Enumerate the cycle family members.
           */
          void enumerate(std::function<void(const VertexCycle<Graph>&)> callback) const
          {
            listPaths(m_p, [&] (const VertexCycle<Graph> &rp) {
              listPaths(m_q, [&] (const VertexCycle<Graph> &rq) {
                VertexCycle<Graph> cycle;

                if (isOdd())
                  cycle = cycleFromPaths(rp, rq);
                else
                  cycle = cycleFromPaths(rp, m_x, rq);

                callback(cycle);
              });
            });
          }

        private:
          /**
           * @brief Extend the current path from x to m_r.
           */
          void listPaths(Vertex x, VertexPath<Graph> &current,
              std::function<void(const VertexPath<Graph>&)> callback) const
          {
            // add v at the head-end of current path
            current.insert(current.begin(), x);

            if (x == m_r) {
              // found a path (r .. x)
              callback(current);
            } else {
              // for any z such that (x, z) is in Ur
              for (Index zi = 0; zi <= getIndex(*m_graph, m_r); ++zi)
                if (m_Dr->isEdge(getIndex(*m_graph, x), zi))
                  listPaths(getVertex(*m_graph, zi), current, callback);
            }

            current.erase(current.begin());
          }

          /**
           * @brief List all paths from vertex m_r to vertex x.
           */
          void listPaths(Vertex x,
              std::function<void(const VertexPath<Graph>&)> callback) const
          {
            VertexPath<Graph> current;
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
       * @brief Check if a cycle is relevant.
       *
       * @param g The graph.
       * @param B Basis for the cycle space.
       * @param cycle The cycle to check.
       */
      template<typename Graph>
      bool isCycleRelevant(const Graph &g, const BitMatrix &B,
          const VertexCycle<Graph> &cycle)
      {
        // copy B
        BitMatrix m(B);

        // add cycle to B as new row
        int row = m.rows();
        m.addRow();
        for (auto e : edgeCycleFromVertexCycle(g, cycle))
          m.set(row, getIndex(g, e));

        // perform gaussian eliminate
        int rank = m.rows();
        bool relevant = (rank == m.eliminate());

        return relevant;
      }

      /**
       * This function checks to ensure that all cylic edges are covered by the
       * current cycle set. A simple example where this is needed:
       *
       *          6
       *         /|
       * 0 ---- 1 +--- 2           C ---- D ---- E
       * |        7    |          /               \
       * |       /     |        /                  \
       * 5 ---- 4 ---- 3       8 ---- 9 ---- A ---- B
       *
       * cyclomatic number: 16 - 15 + 2 = 3
       *
       * 6-membered cycles:
       *   0 1 2 3 4 5
       *   0 1 6 7 4 5
       *   1 2 3 4 7 6
       *
       * 7-membered cycle:
       *   8 9 A B C D E
       *
       * When all relevant 6-membered cycles are added to the cycle set, the
       * edges of the 7-membered cycle are not yet covered by the cycle set.
       * The algorithm will continue to add 7-membered cycles to complete the
       * set.
       */
      /*
      template<typename Graph>
      bool isCyclesetComplete(const Graph &g,
          const EdgePropertyMap<Graph, bool> &coveredEdges,
          const EdgePropertyMap<Graph, bool> &cycleMembership)
      {
        for (auto e : getEdges(g))
          if (cycleMembership[e] && !coveredEdges[e])
            return false;

        return true;
      }
      */

      /**
       * @brief Find the initial Vismara cycle families.
       *
       * @param graph The graph.
       * @param cyclomaticNumber The cyclomatic number.
       * @param cycleMembership Vertex and edge cycle membership.
       */
      template<typename Graph>
      std::vector<CycleFamily<Graph>> initialCycleFamilies(const Graph &g,
          unsigned int cyclomaticNumber,
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
                    dijkstra.path(y), dijkstra.path(z));

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
                    dijkstra.path(p), y, dijkstra.path(q));

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
      void selectRelevantCycleFamilies(const Graph &g,
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
        // the matrix representing the cycle space of cycles smaller than the
        // current cycle size
        BitMatrix B_less(numEdges(g));


        unsigned int lastSize = families.front().prototype().size();
        for (std::size_t i = 0; i < families.size(); ++i) {
          const impl::CycleFamily<Graph> &family = families[i];

          // update B_less
          if (lastSize < family.prototype().size()) {

            /*
            if (cycles.size() >= cyclomaticNumber &&
                impl::isCyclesetComplete(g, cycles, cycleMembership.edges)) {

              while (i < families.size()) {
                remove.push_back(i);
                ++i;
              }

              break;
            }
            */

            // add newly added relevant family prototypes to B_less
            for (auto j : add) {
              int row = B_less.rows();
              B_less.addRow();
              for (auto e : edgeCycleFromVertexCycle(g, families[j].prototype()))
                B_less.set(row, getIndex(g, e));
            }

            // run gaussian elimination on B_less
            int rank = B_less.eliminate();
            while (B_less.rows() > rank)
              B_less.popRow();

            lastSize = family.prototype().size();
            add.clear();
          }

          if (!impl::isCycleRelevant(g, B_less, family.prototype()))
            remove.push_back(i);
          else {
            add.push_back(i);

            /*
            family.enumerate([&] (const VertexCycle<Graph> &cycle) {
              cycles.push_back(cycle);
            });
            */

          }
        }

        for (std::size_t i = 0; i < remove.size(); ++i)
          families.erase(families.begin() + remove[remove.size() - i - 1]);
      }

    } // namespace impl

    /**
     * @brief Find the relevant cycles using Vismara algorithm.
     *
     * @param graph The graph.
     * @param cyclomaticNumber The cyclomatic number.
     * @param cycleMembership Vertex and edge cycle membership.
     *
     * @return The set of relevant cycles.
     */
    template<typename Graph>
    VertexCycles<Graph> relevantCyclesVismara(const Graph &g, unsigned int cyclomaticNumber,
        const VertexEdgePropertyMap<Graph, bool> &cycleMembership)
    {
      // find initial set of cycle families
      std::vector<impl::CycleFamily<Graph>> families =
        impl::initialCycleFamilies(g, cyclomaticNumber, cycleMembership);

      // select relevant families
      impl::selectRelevantCycleFamilies(g, families);

      // enumerate relevant cycles
      VertexCycles<Graph> cycles;
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
    VertexCycles<Graph> relevantCycles(const Graph &graph)
    {
      auto cycleMember = cycleMembership(graph);
      return relevantCyclesVismara(graph, cyclomaticNumber(graph),
          cycleMember);
    }

  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_RELEVANT_CYCLES_H
