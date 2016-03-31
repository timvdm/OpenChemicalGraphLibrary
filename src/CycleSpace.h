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
          m_eliminated(true)
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
        : m_graph(g), m_B(numEdges(g)), m_circuitRank(circuitRank),
          m_eliminated(true)
      {
      }

      /**
       * @brief Add an edge cycle to the cycle space.
       *
       * @param cycle The edge cycle to add.
       */
      void add(const EdgeCycle<Graph> &cycle)
      {
        // get the index for the new row
        int row = m_B.rows();
        // add the new row
        m_B.addRow();
        // set the bits for the edges
        for (auto e : cycle)
          m_B.set(row, getIndex(m_graph, e));
        // mark B as not eliminated
        m_eliminated = false;
      }

      /**
       * @brief Add a vertex cycle to the cycle space.
       *
       * @param cycle The vertex cycle to add.
       */
      void add(const VertexCycle<Graph> &cycle)
      {
        add(cycle.edges(m_graph));
      }

      /**
       * @brief Check if an edge cycle is contained in the cycle space.
       *
       * @param cycle The edge cycle to check.
       */
      bool contains(const EdgeCycle<Graph> &cycle)
      {
        // make sure B is eliminated
        if (!m_eliminated)
          eliminate();

        // copy B
        BitMatrix B(m_B);

        // add cycle to copied B as new row
        int row = B.rows();
        B.addRow();
        for (auto e : cycle)
          B.set(row, getIndex(m_graph, e));

        // perform gaussian elimination on copied B
        int rank = B.eliminate();

        // if the number of rows is unchanged after both matrices have been
        // eliminated, the cycle is contained in B
        return rank == m_B.rows();
      }

      /**
       * @brief Check if a vertex cycle is contained in the cycle space.
       *
       * @param cycle The vertex cycle to check.
       */
      bool contains(const VertexCycle<Graph> &cycle)
      {
        return contains(cycle.edges(m_graph));
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
        // make sure B is eliminated
        if (!m_eliminated)
          eliminate();

        return m_B.rows() >= m_circuitRank;
      }

    private:
      /**
       * Perform Gaussian elimination on the matrix and remove null rows.
       */
      void eliminate()
      {
        // run gaussian elimination on B
        int rank = m_B.eliminate();
        // remove any null rows
        while (m_B.rows() > rank)
          m_B.popRow();
        // mark B as eliminated
        m_eliminated = true;
      }

      /**
       * @brief The graph.
       */
      const Graph &m_graph;
      /**
       * @brief The bit matrix.
       */
      BitMatrix m_B;
      /**
       * @brief The graph's circuit rank.
       */
      unsigned int m_circuitRank;
      /**
       * @brief Flag to indicate whether the matrix is in row-echelon form.
       */
      bool m_eliminated;
  };

} // namespace ocgl

#endif // OCGL_CYCLE_SPACE_H
