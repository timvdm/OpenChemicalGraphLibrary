#ifndef OCGL_SUBGRAPH_H
#define OCGL_SUBGRAPH_H

#include <ocgl/PropertyMap.h>
#include <ocgl/predicate/HasProperty.h>

#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>

/**
 * @file Subgraph.h
 * @brief Subgraph view of a graph.
 */

namespace ocgl {

  namespace impl {

    template<typename Graph>
    struct SubSuper
    {
      using Type = Graph;

      static const Type& get(const Graph &g)
      {
        return g;
      }
    };

  } // namespace impl

  /**
   * @class Subgraph Subgraph.h <ocgl/Subgraph.h>
   * @brief Subgraph view of a graph.
   *
   * The Subgraph class can be used to create a subgraph view of a graph without
   * the need to copy (part) of the graph. The vertices and edges that are part
   * of a subgraph are specified using masks (i.e. boolean property maps with a
   * value of true indicating that the vertex or edge belongs to the subgraph).
   *
   * The vertex and edge types and values are the same as those from the
   * supergraph which means results from an algorithm do not need to be
   * transformed.
   */
  template<typename Graph>
  class Subgraph
  {
    public:
      /**
       * @brief The type of the supergraph.
       *
       * This type trait avoids recursive Subgraphs (i.e. Subgraph<Graph>
       * becomes Graph).
       */
      using Super = typename impl::SubSuper<Graph>::Type;

      /**
       * @brief The type of the subgraph.
       *
       * This type trait avoids recursive Subgraphs (i.e. Subgraph<Subgraph<Graph>>
       * becomes Subgraph<Graph>).
       */
      using Sub = Subgraph<Super>;

      /**
       * @brief The vertex type (same as supergraph).
       */
      using Vertex = typename GraphTraits<Graph>::Vertex;

      /**
       * @brief The edge type (same as supergraph).
       */
      using Edge = typename GraphTraits<Graph>::Edge;

      /**
       * @brief The vertex iterator type.
       */
      using VertexIter = FilterIterator<Graph,
            typename GraphTraits<Graph>::VertexIter,
            typename ocgl::predicate::HasProperty<Graph, bool, impl::VertexTag,
            std::equal_to<bool>>>;

      /**
       * @brief The edge iterator type.
       */
      using EdgeIter = FilterIterator<Graph,
            typename GraphTraits<Graph>::EdgeIter,
            typename ocgl::predicate::HasProperty<Graph, bool, impl::EdgeTag,
            std::equal_to<bool>>>;

      /**
       * @brief The incident edge iterator type.
       */
      using IncidentIter = FilterIterator<Graph,
            typename GraphTraits<Graph>::IncidentIter,
            typename ocgl::predicate::HasProperty<Graph, bool, impl::EdgeTag,
            std::equal_to<bool>>>;

      /**
       * @brief The adjacent vertex iterator type.
       */
      using AdjacentIter = FilterIterator<Graph,
            typename GraphTraits<Graph>::AdjacentIter,
            typename ocgl::predicate::HasProperty<Graph, bool, impl::VertexTag,
            std::equal_to<bool>>>;

      /**
       * @brief Constructor.
       *
       * @param g The supergraph.
       * @param vertexMask The vertex mask.
       * @param edgeMask The edge mask.
       */
      Subgraph(const Graph &g, const VertexPropertyMap<Graph, bool> &vertexMask,
          const EdgePropertyMap<Graph, bool> &edgeMask)
        : m_graph(&g), m_vertexMask(vertexMask), m_edgeMask(edgeMask),
          m_numVertices(0), m_numEdges(0)
      {
        init();
      }

      /**
       * @brief Constructor.
       *
       * @param g The supergraph.
       * @param mask The vertex and edge mask.
       */
      Subgraph(const Graph &g, const VertexEdgePropertyMap<Graph, bool> &mask)
        : m_graph(&g), m_vertexMask(mask.vertices), m_edgeMask(mask.edges),
          m_numVertices(0), m_numEdges(0)
      {
        init();
      }

      /**
       * @brief Copy constructor.
       */
      Subgraph(const Subgraph<Graph> &other) = default;

      /**
       * @brief Move constructor.
       */
      Subgraph(Subgraph<Graph> &&other) = default;

      /**
       * @brief Copy assignment.
       */
      Subgraph<Graph>& operator=(const Subgraph<Graph> &other) = default;

      /**
       * @brief Move assignment.
       */
      Subgraph<Graph>& operator=(Subgraph<Graph> &&other) = default;


      /**
       * @brief Get the supergraph of a graph.
       */
      static const Super& super(const Graph &g)
      {
        return impl::SubSuper<Graph>::get(g);
      }

      /**
       * @brief Get the supergraph.
       */
      const Graph& graph() const
      {
        return *m_graph;
      }

      /**
       * @brief Get the vertex mask.
       */
      const VertexPropertyMap<Graph, bool>& vertexMask() const
      {
        return m_vertexMask;
      }

      /**
       * @brief Get the edge mask.
       */
      const EdgePropertyMap<Graph, bool>& edgeMask() const
      {
        return m_edgeMask;
      }

      /**
       * @brief Get the null vertex.
       */
      static Vertex nullVertex()
      {
        return GraphTraits<Graph>::nullVertex();
      }

      /**
       * @brief Get the null edge.
       */
      static Vertex nullEdge()
      {
        return GraphTraits<Graph>::nullEdge();
      }

      /**
       * @brief Get the number of vertices.
       */
      unsigned int numVertices() const
      {
        return m_numVertices;
      }

      /**
       * @brief Get the number of edges.
       */
      unsigned int numEdges() const
      {
        return m_numEdges;
      }

      /**
       * @brief Get the vertices.
       */
      Range<VertexIter> vertices() const
      {
        return getVertices(*m_graph,
            ocgl::predicate::HasPropertyEQ(m_vertexMask, true));
      }

      /**
       * @brief Get the edges.
       */
      Range<EdgeIter> edges() const
      {
        return getEdges(*m_graph,
            ocgl::predicate::HasPropertyEQ(m_edgeMask, true));
      }

      /**
       * @brief Get a vertex by index.
       *
       * @param subIndex The vertex index in the subgraph.
       */
      Vertex vertex(VertexIndex subIndex) const
      {
        auto superIndex = m_sub2superVertexIndex[subIndex];
        return getVertex(*m_graph, superIndex);
      }

      /**
       * @brief Get an edge by index.
       *
       * @param subIndex The edge index in the subgraph.
       */
      Edge edge(EdgeIndex subIndex) const
      {
        auto superIndex = m_sub2superEdgeIndex[subIndex];
        return getEdge(*m_graph, superIndex);
      }

      /**
       * @brief Get the index of a vertex in the subgraph.
       *
       * @param v The vertex.
       */
      VertexIndex vertexIndex(typename GraphTraits<Graph>::Vertex v) const
      {
        auto superIndex = getVertexIndex(*m_graph, v);
        return m_super2subVertexIndex[superIndex];
      }

      /**
       * @brief Get the index of an edge in the subgraph.
       *
       * @param e The edge.
       */
      EdgeIndex edgeIndex(typename GraphTraits<Graph>::Edge e) const
      {
        auto superIndex = getEdgeIndex(*m_graph, e);
        return m_super2subEdgeIndex[superIndex];
      }

      /**
       * @brief Get the degree of a vertex in the subgraph.
       *
       * @param v The vertex.
       */
      unsigned int degree(typename GraphTraits<Graph>::Vertex v) const
      {
        unsigned int result = 0;
        for (auto w : getAdjacent(*m_graph, v))
          if (m_vertexMask[w])
            result++;
        return result;
      }

      /**
       * @brief Get the incident edges of a vertex in the subgraph.
       *
       * @param v The vertex.
       */
      Range<IncidentIter> incident(typename GraphTraits<Graph>::Vertex v) const
      {
        return getIncident(*m_graph, v,
            ocgl::predicate::HasPropertyEQ(m_edgeMask, true));
      }

      /**
       * @brief Get the adjacent vertices of a vertex in the subgraph.
       *
       * @param v The vertex.
       */
      Range<AdjacentIter> adjacent(typename GraphTraits<Graph>::Vertex v) const
      {
        return getAdjacent(*m_graph, v,
            ocgl::predicate::HasPropertyEQ(m_vertexMask, true));
      }

      /**
       * @brief Get the source vertex of an edge in the subgraph.
       *
       * @param e The edge.
       */
      typename GraphTraits<Graph>::Vertex source(typename GraphTraits<Graph>::Edge e) const
      {
        return getSource(*m_graph, e);
      }

      /**
       * @brief Get the target vertex of an edge in the subgraph.
       *
       * @param e The edge.
       */
      typename GraphTraits<Graph>::Vertex target(typename GraphTraits<Graph>::Edge e) const
      {
        return getTarget(*m_graph, e);
      }

    private:
      void init()
      {
        // count number of vertices
        for (auto v : getVertices(*m_graph))
          if (m_vertexMask[v])
            ++m_numVertices;

        // count number of edges
        for (auto e : getEdges(*m_graph))
          if (m_edgeMask[e])
            ++m_numEdges;

        /*
        std::cout << "Subgraph:" << std::endl;
        std::cout << "    V: ";
        for (auto v : getVertices(m_graph))
          std::cout << m_vertexMask[v] << " ";
        std::cout << std::endl;
        std::cout << "    E: ";
        for (auto v : getEdges(m_graph))
          std::cout << m_edgeMask[v] << " ";
        std::cout << std::endl;
        */

        // create subgraph to supergraph vertex index map
        m_sub2superVertexIndex.reserve(m_numVertices);
        for (auto v : vertices())
          m_sub2superVertexIndex.push_back(getVertexIndex(*m_graph, v));

        // create subgraph to supergraph edge index map
        m_sub2superEdgeIndex.reserve(m_numEdges);
        for (auto e : edges())
          m_sub2superEdgeIndex.push_back(getEdgeIndex(*m_graph, e));

        // create supergraph to subgraph vertex index map
        Index index = 0;
        m_super2subVertexIndex.resize(ocgl::numVertices(*m_graph),
            std::numeric_limits<Index>::max());
        for (auto v : getVertices(*m_graph))
          if (m_vertexMask[v])
            m_super2subVertexIndex[getVertexIndex(*m_graph, v)] = index++;

        // create supergraph to subgraph edge index map
        index = 0;
        m_super2subEdgeIndex.resize(ocgl::numEdges(*m_graph),
            std::numeric_limits<Index>::max());
        for (auto e : getEdges(*m_graph))
          if (m_edgeMask[e])
            m_super2subEdgeIndex[getEdgeIndex(*m_graph, e)] = index++;

        /*
        std::cout << "    V sub2super: ";
        for (auto x : m_sub2superVertexIndex)
          std::cout << x << " ";
        std::cout << std::endl;
        std::cout << "    V super2sub: ";
        for (auto x : m_super2subVertexIndex)
          std::cout << x << " ";
        std::cout << std::endl;
        */


      }

      /**
       * @brief The supergraph.
       */
      const Graph *m_graph;
      /**
       * @brief The vertex mask.
       */
      VertexPropertyMap<Graph, bool> m_vertexMask;
      /**
       * @brief The edge mask.
       */
      EdgePropertyMap<Graph, bool> m_edgeMask;
      /**
       * @brief Convert vertex indices from subgraph to supergraph.
       */
      std::vector<Index> m_sub2superVertexIndex;
      /**
       * @brief Convert edge indices from subgraph to supergraph.
       */
      std::vector<Index> m_sub2superEdgeIndex;
      /**
       * @brief Convert vertex indices from supergraph to subgraph.
       */
      std::vector<Index> m_super2subVertexIndex;
      /**
       * @brief Convert edge indices from supergraph to subgraph.
       */
      std::vector<Index> m_super2subEdgeIndex;
      /**
       * @brief The number of vertices.
       */
      unsigned int m_numVertices;
      /**
       * @brief The number of edges.
       */
      unsigned int m_numEdges;
  };


  namespace impl {

    template<typename Graph>
    struct SubSuper<Subgraph<Graph>>
    {
      using Type = Graph;

      static const Type& get(const Subgraph<Graph> &g)
      {
        return g.graph();
      }
    };

  } // namespace impl

  /**
   * @brief Create a subgraph.
   *
   * This function can be used to create a subgraph while avoiding to create
   * resursive subgraphs.
   *
   * @param g The supergraph.
   * @param mask The vertex and edge mask.
   */
  template<typename Graph>
  Subgraph<typename impl::SubSuper<Graph>::Type> makeSubgraph(const Graph &g,
      const VertexEdgePropertyMap<typename impl::SubSuper<Graph>::Type, bool> &mask)
  {
    return Subgraph<typename impl::SubSuper<Graph>::Type>(
        impl::SubSuper<Graph>::get(g), mask);
  }

  /**
   * @brief Create a subgraph.
   *
   * This function can be used to create a subgraph while avoiding to create
   * resursive subgraphs.
   *
   * @param g The supergraph.
   * @param vertexMask The vertex mask.
   * @param edgeMask The edge mask.
   */
  template<typename Graph>
  Subgraph<typename impl::SubSuper<Graph>::Type> makeSubgraph(const Graph &g,
      const VertexPropertyMap<typename impl::SubSuper<Graph>::Type, bool> &vertexMask,
      const EdgePropertyMap<typename impl::SubSuper<Graph>::Type, bool> &edgeMask)
  {
    return Subgraph<typename impl::SubSuper<Graph>::Type>(
        impl::SubSuper<Graph>::get(g), vertexMask, edgeMask);
  }

  /**
   * @cond impl
   */

  template<typename Graph>
  unsigned int numVertices(const Subgraph<Graph> &g)
  {
    return g.numVertices();
  }

  template<typename Graph>
  unsigned int numEdges(const Subgraph<Graph> &g)
  {
    return g.numEdges();
  }

  template<typename Graph>
  Range<typename Subgraph<Graph>::VertexIter> getVertices(const Subgraph<Graph> &g)
  {
    return g.vertices();
  }

  template<typename Graph>
  Range<typename Subgraph<Graph>::EdgeIter> getEdges(const Subgraph<Graph> &g)
  {
    return g.edges();
  }

  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getVertex(const Subgraph<Graph> &g,
      VertexIndex index)
  {
    return g.vertex(index);
  }

  template<typename Graph>
  typename GraphTraits<Graph>::Edge getEdge(const Subgraph<Graph> &g,
      EdgeIndex index)
  {
    return g.edge(index);
  }

  template<typename Graph>
  VertexIndex getVertexIndex(const Subgraph<Graph> &g,
      typename GraphTraits<Graph>::Vertex v)
  {
    return g.vertexIndex(v);
  }

  template<typename Graph>
  EdgeIndex getEdgeIndex(const Subgraph<Graph> &g,
      typename GraphTraits<Graph>::Edge e)
  {
    return g.edgeIndex(e);
  }

  template<typename Graph>
  unsigned int getDegree(const Subgraph<Graph> &g,
      typename GraphTraits<Graph>::Vertex v)
  {
    return g.degree(v);
  }

  template<typename Graph>
  Range<typename Subgraph<Graph>::IncidentIter> getIncident(const Subgraph<Graph> &g,
      typename GraphTraits<Graph>::Vertex v)
  {
    return g.incident(v);
  }

  template<typename Graph>
  Range<typename Subgraph<Graph>::AdjacentIter> getAdjacent(const Subgraph<Graph> &g,
      typename GraphTraits<Graph>::Vertex v)
  {
    return g.adjacent(v);
  }

  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getSource(const Subgraph<Graph> &g,
      typename GraphTraits<Graph>::Edge e)
  {
    return g.source(e);
  }

  template<typename Graph>
  typename GraphTraits<Graph>::Vertex getTarget(const Subgraph<Graph> &g,
      typename GraphTraits<Graph>::Edge e)
  {
    return g.target(e);
  }

  /**
   * @endcond
   */

} // namespace ocgl

#endif // OCGL_SUBGRAPH_H
