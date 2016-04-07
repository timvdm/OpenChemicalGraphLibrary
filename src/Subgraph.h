#ifndef OCGL_SUBGRAPH_H
#define OCGL_SUBGRAPH_H

#include <ocgl/PropertyMap.h>
#include <ocgl/predicate/HasProperty.h>

#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>

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

  }

  template<typename Graph>
  class Subgraph
  {
    public:
      using Type = Subgraph<typename impl::SubSuper<Graph>::Type>;


      using Vertex = typename GraphTraits<Graph>::Vertex;
      using Edge = typename GraphTraits<Graph>::Edge;
      using VertexIter = FilterIterator<Graph,
            typename GraphTraits<Graph>::VertexIter,
            typename ocgl::predicate::HasProperty<Graph, bool, impl::VertexTag,
            std::equal_to<bool>>>;
      using EdgeIter = FilterIterator<Graph,
            typename GraphTraits<Graph>::EdgeIter,
            typename ocgl::predicate::HasProperty<Graph, bool, impl::EdgeTag,
            std::equal_to<bool>>>;
      using IncidentIter = FilterIterator<Graph,
            typename GraphTraits<Graph>::IncidentIter,
            typename ocgl::predicate::HasProperty<Graph, bool, impl::EdgeTag,
            std::equal_to<bool>>>;
      using AdjacentIter = FilterIterator<Graph,
            typename GraphTraits<Graph>::AdjacentIter,
            typename ocgl::predicate::HasProperty<Graph, bool, impl::VertexTag,
            std::equal_to<bool>>>;

      Subgraph(const Graph &g, const VertexPropertyMap<Graph, bool> &vertexMask,
          const EdgePropertyMap<Graph, bool> &edgeMask)
        : m_graph(&g), m_vertexMask(vertexMask), m_edgeMask(edgeMask),
          m_numVertices(0), m_numEdges(0)
      {
        init();
      }


      Subgraph(const Graph &g, const VertexEdgePropertyMap<Graph, bool> &mask)
        : m_graph(&g), m_vertexMask(mask.vertices), m_edgeMask(mask.edges),
          m_numVertices(0), m_numEdges(0)
      {
        init();
      }


      const Graph& graph() const
      {
        return *m_graph;
      }

      static Vertex nullVertex()
      {
        return GraphTraits<Graph>::nullVertex();
      }

      static Vertex nullEdge()
      {
        return GraphTraits<Graph>::nullEdge();
      }

      unsigned int numVertices() const
      {
        return m_numVertices;
      }

      unsigned int numEdges() const
      {
        return m_numEdges;
      }

      Range<VertexIter> vertices() const
      {
        return getVertices(*m_graph,
            ocgl::predicate::HasPropertyEQ(m_vertexMask, true));
      }

      Range<EdgeIter> edges() const
      {
        return getEdges(*m_graph,
            ocgl::predicate::HasPropertyEQ(m_edgeMask, true));
      }

      Vertex vertex(VertexIndex subIndex) const
      {
        auto superIndex = m_sub2superVertexIndex[subIndex];
        return getVertex(*m_graph, superIndex);
      }

      Edge edge(EdgeIndex subIndex) const
      {
        auto superIndex = m_sub2superEdgeIndex[subIndex];
        return getEdge(*m_graph, superIndex);
      }

      VertexIndex vertexIndex(typename GraphTraits<Graph>::Vertex v) const
      {
        auto superIndex = getVertexIndex(*m_graph, v);
        return m_super2subVertexIndex[superIndex];
      }

      EdgeIndex edgeIndex(typename GraphTraits<Graph>::Edge e) const
      {
        auto superIndex = getEdgeIndex(*m_graph, e);
        return m_super2subEdgeIndex[superIndex];
      }

      unsigned int degree(typename GraphTraits<Graph>::Vertex v) const
      {
        unsigned int result = 0;
        for (auto w : getAdjacent(*m_graph, v))
          if (m_vertexMask[w])
            result++;
        return result;
      }

      Range<IncidentIter> incident(typename GraphTraits<Graph>::Vertex v) const
      {
        return getIncident(*m_graph, v,
            ocgl::predicate::HasPropertyEQ(m_edgeMask, true));
      }

      Range<AdjacentIter> adjacent(typename GraphTraits<Graph>::Vertex v) const
      {
        return getAdjacent(*m_graph, v,
            ocgl::predicate::HasPropertyEQ(m_vertexMask, true));
      }

      typename GraphTraits<Graph>::Vertex source(typename GraphTraits<Graph>::Edge e) const
      {
        return getSource(*m_graph, e);
      }

      typename GraphTraits<Graph>::Vertex target(typename GraphTraits<Graph>::Edge e) const
      {
        return getTarget(*m_graph, e);
      }

      const VertexPropertyMap<Graph, bool>& vertexMask() const
      {
        return m_vertexMask;
      }

      const EdgePropertyMap<Graph, bool>& edgeMask() const
      {
        return m_edgeMask;
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

      const Graph *m_graph;

      const VertexPropertyMap<Graph, bool> m_vertexMask;
      const EdgePropertyMap<Graph, bool> m_edgeMask;

      std::vector<Index> m_sub2superVertexIndex;
      std::vector<Index> m_sub2superEdgeIndex;
      std::vector<Index> m_super2subVertexIndex;
      std::vector<Index> m_super2subEdgeIndex;

      unsigned int m_numVertices;
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



  template<typename Graph>
  Subgraph<typename impl::SubSuper<Graph>::Type> makeSubgraph(const Graph &g,
      const VertexEdgePropertyMap<typename impl::SubSuper<Graph>::Type, bool> &mask)
  {
    return Subgraph<typename impl::SubSuper<Graph>::Type>(
        impl::SubSuper<Graph>::get(g), mask);
  }

  template<typename Graph>
  Subgraph<typename impl::SubSuper<Graph>::Type> makeSubgraph(const Graph &g,
      const VertexPropertyMap<typename impl::SubSuper<Graph>::Type, bool> &vertexMask,
      const EdgePropertyMap<typename impl::SubSuper<Graph>::Type, bool> &edgeMask)
  {
    return Subgraph<typename impl::SubSuper<Graph>::Type>(
        impl::SubSuper<Graph>::get(g), vertexMask, edgeMask);
  }


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



} // namespace ocgl

#endif // OCGL_SUBGRAPH_H
