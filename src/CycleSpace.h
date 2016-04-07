#ifndef OCGL_CYCLE_SPACE_H
#define OCGL_CYCLE_SPACE_H

#include <ocgl/Cycle.h>
#include <ocgl/BitMatrix.h>

/**
 * @file CycleSpace.h
 * @brief Cycle space of a graph.
 */

namespace ocgl {

  /**
   * @class CycleSpace CycleSpace.h <ocgl/CycleSpace.h>
   * @brief Cycle space of a graph.
   *
   * The CycleSpace class represents a graph's cycle space using a bit matrix
   * (i.e. BitMatrix). Each column in this matrix corresponds to an edge of the
   * graph. A row in the matrix corresponds to a single cycle where a 1 bit in
   * a column indicates that this edge is part of the cycle. This class can be
   * used to find a basis for the cycle space using Gaussian elimination.
   */
  template<typename Graph>
  class CycleSpace
  {
    public:
      /**
       * @brief Constructor.
       *
       * This constructor calls circuitRank().
       *
       * @param g The graph.
       */
      CycleSpace(const Graph &g) : m_graph(g), m_B(numEdges(g)),
          m_cyclicEdges(numEdges(g))
      {
        m_circuitRank = circuitRank(g);
      }

      /**
       * @brief Constructor.
       *
       * @param g The graph.
       * @param circuitRank The circuit rank of the graph.
       */
      CycleSpace(const Graph &g, unsigned int circuitRank)
        : m_graph(g), m_B(numEdges(g)), m_cyclicEdges(numEdges(g)),
          m_circuitRank(circuitRank)
      {
      }

      /**
       * @brief Add an edge cycle to the cycle space.
       *
       * @param cycle The edge cycle to add.
       * @param update When true, updateMatrix() will be called when the cycle
       *               is added.
       */
      void addEdgeCycle(const EdgeCycle<Graph> &cycle, bool update = true)
      {
        // get the index for the new row
        int row = m_B.rows();
        // add the new row
        m_B.addRow();
        // set the bits for the edges
        for (auto e : cycle) {
          m_B.set(row, getEdgeIndex(m_graph, e));
          m_cyclicEdges[getEdgeIndex(m_graph, e)] = true;
        }

        if (update)
          updateMatrix();
      }

      /**
       * @brief Add a vertex cycle to the cycle space.
       *
       * @param cycle The vertex cycle to add.
       * @param update When true, updateMatrix() will be called when the cycle
       *               is added.
       */
      void addVertexCycle(const VertexCycle<Graph> &cycle, bool update = true)
      {
        addEdgeCycle(vertexCycleToEdgeCycle(m_graph, cycle), update);
      }

      /**
       * @brief Check if an edge cycle is contained in the cycle space.
       *
       * @param cycle The edge cycle to check.
       */
      bool containsEdgeCycle(const EdgeCycle<Graph> &cycle) const
      {
        for (auto e : cycle)
          if (!m_cyclicEdges[getEdgeIndex(m_graph, e)])
            return false;

        // add cycle to copied B as new row
        int row = m_B.rows();
        m_B.addRow();
        for (auto e : cycle)
          m_B.set(row, getEdgeIndex(m_graph, e));

        // perform gaussian elimination on copied B
        int rank = m_B.eliminateLastRow();

        m_B.popRow();

        // if the number of rows is unchanged after both matrices have been
        // eliminated, the cycle is contained in B
        return rank == m_B.rows();
      }

      /**
       * @brief Check if a vertex cycle is contained in the cycle space.
       *
       * @param cycle The vertex cycle to check.
       */
      bool containsVertexCycle(const VertexCycle<Graph> &cycle) const
      {
        return containsEdgeCycle(vertexCycleToEdgeCycle(m_graph, cycle));
      }

      /**
       * @brief Check if the currently added cycles form a basis for the cycle
       *        space of the graph.
       *
       * The added cycles form a basis for the cycle space of the graph if,
       * after performing Gaussian elimination on the bit matrix to determine
       * the rank, the rank is equal to the circuit rank of the graph.
       */
      bool isBasis()
      {
        return m_B.rows() >= m_circuitRank;
      }

      /**
       * Perform Gaussian elimination on the matrix and remove null rows.
       */
      void updateMatrix()
      {
        // run gaussian elimination on B
        int rank = m_B.eliminate();
        // remove any null rows
        while (m_B.rows() > rank)
          m_B.popRow();
      }

    private:
      /**
       * @brief The graph.
       */
      const Graph &m_graph;
      /**
       * @brief The bit matrix.
       */
      mutable BitMatrix m_B;
      /**
       * @brief Keep track of cyclic edges.
       */
      std::vector<bool> m_cyclicEdges;
      /**
       * @brief The graph's circuit rank.
       */
      unsigned int m_circuitRank;
  };

} // namespace ocgl

#endif // OCGL_CYCLE_SPACE_H
