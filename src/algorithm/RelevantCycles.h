#ifndef OCGL_ALGORITHM_RELEVANT_CYCLES_H
#define OCGL_ALGORITHM_RELEVANT_CYCLES_H

#include <ocgl/algorithm/Dijkstra.h>
#include <ocgl/algorithm/CycleMembership.h>
#include <ocgl/algorithm/ConnectedComponents.h>


// TODO:
// * becnhmark std::swap_ranges for vector<bool>
// * listPaths w/o constructing all of them


#include <iostream> // FIXME

namespace ocgl {


  template<typename Graph>
  using VertexCycle = std::vector<typename GraphTraits<Graph>::Vertex>;

  template<typename Graph>
  using EdgeCycle = std::vector<typename GraphTraits<Graph>::Edge>;


  template<typename Graph>
  using VertexCycles = std::vector<VertexCycle<Graph>>;

  template<typename Graph>
  using EdgeCycles = std::vector<EdgeCycle<Graph>>;

  template<typename Graph>
  EdgeCycle<Graph> edgeCycleFromVertexCycle(const Graph &g, const VertexCycle<Graph> &cycle)
  {
    EdgeCycle<Graph> result;

    for (std::size_t i = 1; i < cycle.size(); ++i)
      result.push_back(getEdge(g, cycle[i-1], cycle[i]));
    result.push_back(getEdge(g, cycle.front(), cycle.back()));

    return result;
  }




  namespace algorithm {

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
      return cyclomaticNumber(g, numConnectedComponents(g));
    }

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

      class CycleBitMatrix
      {
        public:
          CycleBitMatrix(int cols) : m_rows(0), m_cols(cols)
          {
          }

          CycleBitMatrix(int rows, int cols) : m_rows(rows), m_cols(cols)
          {
            m_data.resize(rows * cols);
          }

          void addRow()
          {
            ++m_rows;
            m_data.resize(m_data.size() + m_cols);
          }

          void popRow()
          {
            --m_rows;
            m_data.resize(m_data.size() - m_cols);
          }

          int rows() const
          {
            return m_rows;
          }

          int cols() const
          {
            return m_cols;
          }

          bool get(int row, int col) const
          {
            return m_data[index(row, col)];
          }

          void set(int row, int col, bool value)
          {
            m_data[index(row, col)] = value;
          }

          int eliminate(int x = 0, int y = 0)
          {
            while (x < m_cols && y < m_rows) {
              int i = indexOf(x, y);

              // this column is done, continue with next column
              if (i < 0)
                return eliminate(x + 1, y);

              // swap rows if needed
              if (i != y)
                swapRows(i, y);

              for (int j = y + 1; j < m_rows; ++j)
                if (m_data[index(j, x)])
                  xorRows(y, j);

              ++y;
            }
            return y;
          }

        private:
          std::size_t index(int row, int col) const
          {
            return m_cols * row + col;
          }

          int indexOf(int x, int y) const
          {
            for (int i = y; i < m_rows; ++i)
              if (m_data[index(i, x)])
                return i;
            return -1;
          }

          void swapRows(int i, int j)
          {
            // TODO: std::swap_ranges ?
            // TODO: make data member?
            std::vector<bool> tmp(m_cols);
            // i -> tmp
            std::copy(m_data.begin() + i * m_cols, m_data.begin() + (i + 1) * m_cols, tmp.begin());
            // j -> i
            std::copy(m_data.begin() + j * m_cols, m_data.begin() + (j + 1) * m_cols, m_data.begin() + i * m_cols);
            // tmp -> j
            std::copy(tmp.begin(), tmp.end(), m_data.begin() + j * m_cols);
          }

          void xorRows(int i, int j)
          {
            for (int col = 0; col < m_cols; ++col)
              m_data[index(j, col)] = m_data[index(i, col)] ^ m_data[index(j, col)];
          }

          std::vector<bool> m_data;
          int m_rows;
          int m_cols;
      };

      inline std::ostream& operator<<(std::ostream &os, const CycleBitMatrix &m)
      {
        for (int i = 0; i < m.rows(); ++i) {
          os << "[ ";
          for (int j = 0; j < m.cols(); ++j)
            os << m.get(i, j) << " ";
          os << "]" << std::endl;
        }
        return os;
      }

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
       * - r is the source vertex
       * - there are equal length paths to vertex p and q
       * - for even cycles, there is also an x vertex
       */
      template<typename Graph>
      class CycleFamily
      {
        public:
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
              const std::vector<Vertex> &prototype)
            : m_graph(&g), m_r(r), m_p(p), m_q(q), m_x(nullVertex<Graph>()),
              m_prototype(prototype)
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
              const std::vector<Vertex> &prototype)
            : m_graph(&g), m_r(r), m_p(p), m_q(q), m_x(x), m_prototype(prototype)
          {
          }

          //CycleFamily(const CycleFamily<Graph> &other) = default;
          //CycleFamily(CycleFamily<Graph> &&other) = default;
          //CycleFamily<Graph>& operator=(const CycleFamily<Graph> &other) = default;
          //CycleFamily<Graph>& operator=(CycleFamily<Graph> &&other) = default;

          Vertex r() const
          {
            return m_r;
          }

          Vertex p() const
          {
            return m_p;
          }

          Vertex q() const
          {
            return m_q;
          }

          Vertex x() const
          {
            return m_x;
          }

          const std::vector<Vertex>& prototype() const
          {
            return m_prototype;
          }

          bool isOdd() const
          {
            return isNull(*m_graph, m_x);
          }

          bool isEven() const
          {
            return isValid(*m_graph, m_x);
          }

          bool operator<(const CycleFamily &other) const
          {
            return m_prototype.size() < other.m_prototype.size();
          }

        private:
          const Graph *m_graph;
          Vertex m_r;
          Vertex m_p;
          Vertex m_q;
          Vertex m_x;
          std::vector<Vertex> m_prototype;
      };

      template<typename Graph, typename Vertex>
      inline void listPaths(const Graph &g, const DirectedAdjacencyMatrix &Dr,
          Vertex r, Vertex x, std::vector<Vertex> &current,
          std::vector<std::vector<Vertex>> &result)
      {
        // add x at the head-end of current path
        current.insert(current.begin(), x);

        if (x == r) {
          result.push_back(current);
        } else {
          // for any z such that (x, z) is in Ur
          for (auto z : getVertices(g)) {
            if (getIndex(g, z) > getIndex(g, r))
              break;
            if (Dr.isEdge(getIndex(g, x), getIndex(g, z))) {
              // TODO: use callback to yield?
              std::vector<Vertex> currentCopy(current);
              listPaths(g, Dr, r, z, currentCopy, result);
            }
          }
        }
      }

      template<typename Graph, typename Vertex>
      inline std::vector<std::vector<Vertex>> listPaths(const Graph &g,
          const DirectedAdjacencyMatrix &Dr, Vertex r, Vertex x)
      {
        std::vector<std::vector<Vertex>> result;
        std::vector<Vertex> current;
        listPaths(g, Dr, r, x, current, result);
        return result;
      }

      template<typename Graph, typename Vertex>
      void addVertexCycleToMatrix(const Graph &g, CycleBitMatrix &B,
          const std::vector<Vertex> &cycle)
      {
        int row = B.rows();
        B.addRow();
        for (std::size_t i = 1; i < cycle.size(); ++i) {
          auto source = cycle[i - 1];
          auto target = cycle[i];
          auto edge = getEdge(g, source, target);
          B.set(row, getIndex(g, edge), true);
        }

        auto source = cycle.front();
        auto target = cycle.back();
        auto edge = getEdge(g, source, target);
        B.set(row, getIndex(g, edge), true);
      }

      template<typename Graph, typename Vertex>
      bool isCycleRelevant(const Graph &g, const CycleBitMatrix &matrix,
          const std::vector<Vertex> &cycle)
      {
        CycleBitMatrix m(matrix);

        addVertexCycleToMatrix(g, m, cycle);

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
      template<typename Graph>
      bool isCyclesetComplete(const Graph &g, const VertexCycles<Graph> &cycles,
          const EdgePropertyMap<Graph, bool> &cycleMembership)
      {
        // check if all cyclic edges are covered
        for (auto e : getEdges(g)) {
          if (!cycleMembership[e])
            continue;

          bool found = false;
          for (auto &cycle : cycles)
            if (std::find(cycle.begin(), cycle.end(), e) != cycle.end()) {
              found = true;
              break;
            }

          if (!found)
            return false;
        }

        return true;
      }

    } // namespace impl






    /**
     * @brief Find the relevant cycles.
     *
     * The set of relevant cycles is formed by taking the union of all the
     * minimum cycles bases. An alternative definition is that a cycle is
     * relevant if it is not the sum of smaller cycles.
     *
     * @param graph The graph.
     * @param cyclomaticNumber The cyclomatic number.
     * @param cyclicAtoms Atom cycle membership.
     * @param cyclicBonds Bond cycle membership.
     *
     * @return The set of relevant cycles.
     */
    template<typename Graph>
    VertexCycles<Graph> relevantCyclesVismara(const Graph &g, unsigned int cyclomaticNumber,
        const VertexEdgePropertyMap<Graph, bool> &cycleMembership)
    {
      using Vertex = typename GraphTraits<Graph>::Vertex;

      // V = {1, ..., n}  |V| = n
      //
      // E = { (x, y) | there is an edge between x and y }  |E| = m
      //
      // w((x, y)): weight of edge (x, y) (always 1)
      //
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
      std::vector<impl::DirectedAdjacencyMatrix> D;

      std::vector<impl::CycleFamily<Graph>> families;

      // for all r in V do
      for (auto r : getVertices(g)) {
        // compute Vr and for all t in Vr find a shortest path P(r, t) from r to t
        VertexPropertyMap<Graph, bool> vertexMask(g);
        for (std::size_t i = 0; i < getIndex(g, r) + 1; ++i)
          vertexMask[i] = cycleMembership.vertices[getVertex(g, i)];
        Dijkstra<Graph> dijkstra(g, r, vertexMask);

        std::vector<Vertex> Vr;
        for (std::size_t i = 0; i <= getIndex(g, r); ++i)
          if (dijkstra.distance(getVertex(g, i)) < dijkstra.infinity())
            Vr.push_back(getVertex(g, i));

        D.push_back(impl::DirectedAdjacencyMatrix(numVertices(g)));
        impl::DirectedAdjacencyMatrix &Dr = D.back();

        // for all y in Vr do
        for (auto y : Vr) {
          // S <- {}
          std::vector<Vertex> S;

          // for all z in Vr such that z is adjacent to y
          for (auto z : getAdjacent(g, y)) {
            if (!std::binary_search(Vr.begin(), Vr.end(), z))
              continue;

            // if d(r, z) + w((z, y)) = d(r, y) then
            if (dijkstra.distance(z) + 1 == dijkstra.distance(y)) {
              // S <- S U {z}
              S.push_back(z);

              // add directed edge (y, z) to Dr
              Dr.addEdge(getIndex(g, y), getIndex(g, z));

            // else if d(r, z) != d(r, y) + w((z, y))
            //     and pi(z) < pi(y)
            //     and P(r, y) ^ P(r, z) = {r}
            // then
            } else if (dijkstra.distance(z) != dijkstra.distance(y) + 1 &&
                       getIndex(g, z) < getIndex(g, y) &&
                       impl::pathsIntersectionIsSource(dijkstra, g, y, z)) {

              // add to CI' the odd cycle C = P(r, y) + P(r, z) + (z, y)
              std::vector<Vertex> prototype = dijkstra.path(y); // P(r .. y)
              std::vector<Vertex> Pz = dijkstra.path(z); // P(r .. y z)
              std::copy(Pz.rbegin(), Pz.rbegin() + Pz.size() - 1,
                  std::back_inserter(prototype)); // P(r .. y z ..)

              assert(prototype.size() == 2 * Pz.size() - 1);

              families.push_back(impl::CycleFamily<Graph>(g, r, y, z, prototype));
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
              std::vector<Vertex> prototype = dijkstra.path(p); // P(r .. p)
              prototype.push_back(y); // P(r .. p y)
              std::vector<Vertex> Pq = dijkstra.path(q);
              std::copy(Pq.rbegin(), Pq.rbegin() + Pq.size() - 1,
                  std::back_inserter(prototype)); // P(r .. p y q ..)

              assert(prototype.size() == 2 * Pq.size());

              families.push_back(impl::CycleFamily<Graph>(g, r, p, q, y, prototype));
            }
        }
      }

      if (families.empty())
        return VertexCycles<Graph>();

      //
      // select relevant families
      //

      std::sort(families.begin(), families.end());

      unsigned int lastSize = families.front().prototype().size();

      std::vector<std::size_t> remove;
      impl::CycleBitMatrix B_less(numEdges(g));
      for (std::size_t i = 0; i < families.size(); ++i) {
        const impl::CycleFamily<Graph> &family = families[i];

        // update B_less
        if (lastSize < family.prototype().size()) {
          for (std::size_t j = 0; j < families.size(); ++j) {
            if (families[j].prototype().size() < lastSize)
              continue;
            if (families[j].prototype().size() >= family.prototype().size())
              break;
            addVertexCycleToMatrix(g, B_less, families[j].prototype());
          }

          int rank = B_less.eliminate();
          while (B_less.rows() > rank)
            B_less.popRow();

          lastSize = family.prototype().size();
        }

        if (!isCycleRelevant(g, B_less, family.prototype()))
          remove.push_back(i);
      }

      for (std::size_t i = 0; i < remove.size(); ++i)
        families.erase(families.begin() + remove[remove.size() - i - 1]);

      //
      // enumerate relevant cycles
      //

      lastSize = 0;
      VertexCycles<Graph> cycles;
      for (std::size_t i = 0; i < families.size(); ++i) {
        const impl::CycleFamily<Graph> &family = families[i];

        if (lastSize < family.prototype().size()) {
          if (cycles.size() >= cyclomaticNumber &&
              impl::isCyclesetComplete(g, cycles, cycleMembership.edges))
            break;
          lastSize = family.prototype().size();
        }

        const impl::DirectedAdjacencyMatrix &Dr = D[family.r()];

        std::vector<std::vector<Vertex>> pPaths = impl::listPaths(g, Dr, family.r(), family.p());
        std::vector<std::vector<Vertex>> qPaths = impl::listPaths(g, Dr, family.r(), family.q());


        if (family.isOdd()) {
          for (std::size_t j = 0; j < pPaths.size(); ++j)
            for (std::size_t k = 0; k < qPaths.size(); ++k) {
              std::vector<Vertex> vertices;

              for (std::size_t l = 0; l < pPaths[j].size(); ++l)
                vertices.push_back(pPaths[j][l]);
              for (std::size_t l = qPaths[k].size() - 1; l > 0; --l)
                vertices.push_back(qPaths[k][l]);

              cycles.push_back(vertices);
            }
        } else {
          for (std::size_t j = 0; j < pPaths.size(); ++j)
            for (std::size_t k = 0; k < qPaths.size(); ++k) {
              std::vector<Vertex> vertices;

              for (std::size_t l = 0; l < pPaths[j].size(); ++l)
                vertices.push_back(pPaths[j][l]);
              vertices.push_back(family.x());
              for (std::size_t l = qPaths[k].size() - 1; l > 0; --l)
                vertices.push_back(qPaths[k][l]);

              cycles.push_back(vertices);
            }
        }

      }

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
