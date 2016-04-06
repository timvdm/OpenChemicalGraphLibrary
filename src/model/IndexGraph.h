#ifndef OCGL_MODEL_INDEX_GRAPH_H
#define OCGL_MODEL_INDEX_GRAPH_H

#include <ocgl/Contract.h>
#include <ocgl/Range.h>
#include <ocgl/AdjacentIterator.h>

#include <algorithm>
#include <vector>
#include <limits>

namespace ocgl {

  namespace model {

    class IndexIterator : public std::iterator<std::forward_iterator_tag, Index>
    {
      public:
        IndexIterator(Index index) : m_index(index)
        {
        }

        Index operator*() const
        {
          return m_index;
        }

        IndexIterator& operator++()
        {
          ++m_index;
          return *this;
        }

        IndexIterator operator++(int)
        {
          IndexIterator tmp = *this;
          ++m_index;
          return tmp;
        }

        bool operator==(const IndexIterator &other) const
        {
          return m_index == other.m_index;
        }

        bool operator!=(const IndexIterator &other) const
        {
          return m_index != other.m_index;
        }

      private:
        Index m_index;
    };

    struct IndexGraph
    {
      IndexGraph() = default;
      IndexGraph(const IndexGraph &other) = default;
      IndexGraph(IndexGraph &&other) = default;
      ~IndexGraph() = default;
      IndexGraph& operator=(const IndexGraph &other) = default;
      IndexGraph& operator=(IndexGraph &&other) = default;

      // vertex index -> incident edge indexes
      std::vector<std::vector<EdgeIndex>> incident;
      // edge index -> source & target vertex index
      std::vector<std::pair<VertexIndex, VertexIndex>> edges;
    };

  } // namespace model

  template<>
  struct GraphTraits<model::IndexGraph>
  {
    using Vertex = VertexIndex;
    using Edge = EdgeIndex;
    using VertexIter = model::IndexIterator;
    using EdgeIter = model::IndexIterator;
    using IncidentIter = std::vector<EdgeIndex>::const_iterator;
    using AdjacentIter = AdjacentIterator<model::IndexGraph>;

    static Vertex nullVertex()
    {
      return std::numeric_limits<Index>::max();
    }

    static Edge nullEdge()
    {
      return std::numeric_limits<Index>::max();
    }
  };


  namespace model {

    inline unsigned int num_vertices(const IndexGraph &g)
    {
      return g.incident.size();
    }

    inline unsigned int num_edges(const IndexGraph &g)
    {
      return g.edges.size();
    }

    inline Range<IndexIterator> get_vertices(const IndexGraph &g)
    {
      return makeRange(IndexIterator(0), IndexIterator(num_vertices(g)));
    }

    inline Range<IndexIterator> get_edges(const IndexGraph &g)
    {
      return makeRange(IndexIterator(0), IndexIterator(num_edges(g)));
    }

    inline VertexIndex get_vertex(const IndexGraph &g, VertexIndex index)
    {
      return index;
    }

    inline EdgeIndex get_edge(const IndexGraph &g, EdgeIndex index)
    {
      return index;
    }

    inline VertexIndex get_vertex_index(const IndexGraph &g, VertexIndex index)
    {
      return index;
    }

    inline EdgeIndex get_edge_index(const IndexGraph &g, EdgeIndex index)
    {
      return index;
    }

    inline unsigned int get_degree(const IndexGraph &g, VertexIndex v)
    {
      return g.incident[v].size();
    }

    inline Range<std::vector<EdgeIndex>::const_iterator>
    get_incident(const IndexGraph &g, VertexIndex v)
    {
      return makeRange(g.incident[v].begin(), g.incident[v].end());
    }

    inline Range<AdjacentIterator<IndexGraph>>
    get_adjacent(const IndexGraph &g, VertexIndex v)
    {
      auto begin = AdjacentIterator<IndexGraph>(g, v, g.incident[v].begin());
      auto end = AdjacentIterator<IndexGraph>(g, v, g.incident[v].end());
      return makeRange(begin, end);
    }

    inline VertexIndex get_source(const IndexGraph &g, EdgeIndex e)
    {
      return g.edges[e].first;
    }

    inline VertexIndex get_target(const IndexGraph &g, EdgeIndex e)
    {
      return g.edges[e].second;
    }

    inline VertexIndex add_vertex(IndexGraph &g)
    {
      auto index = num_vertices(g);
      g.incident.resize(g.incident.size() + 1);
      return index;
    }

    void remove_edge(IndexGraph &g, EdgeIndex e);

    void remove_vertex(IndexGraph &g, VertexIndex v)
    {
      // make copy of incident edges
      std::vector<EdgeIndex> incident(g.incident[v]);
      // remove incident edges
      for (auto e : incident)
        remove_edge(g, e);

      // remove list of incident edge indices
      g.incident.erase(g.incident.begin() + v);

      // fix source & target vertex indices
      for (auto &e : g.edges) {
        if (e.first > v)
          --e.first;
        else if (e.second > v)
          --e.second;
      }
    }

    inline EdgeIndex add_edge(IndexGraph &g,
        VertexIndex v, VertexIndex w)
    {
      auto index = num_edges(g);

      // add source & target vertex indices
      g.edges.push_back(std::make_pair(v, w));

      // add edge to source & target incident list
      g.incident[v].push_back(index);
      g.incident[w].push_back(index);

      return index;
    }

    void remove_edge(IndexGraph &g, EdgeIndex e)
    {
      auto v = g.edges[e].first;
      auto w = g.edges[e].second;

      //PRE(std::find(g.incident[v].begin(), g.incident[v].end(), e) != g.incident[v].end());
      //PRE(std::find(g.incident[w].begin(), g.incident[w].end(), e) != g.incident[w].end());

      g.incident[v].erase(std::find(g.incident[v].begin(), g.incident[v].end(), e));
      g.incident[w].erase(std::find(g.incident[w].begin(), g.incident[w].end(), e));

      // remove source & target vertex indices
      g.edges.erase(g.edges.begin() + e);

      // fix incident edge indices
      for (auto &edgeIndices : g.incident)
        for (auto &edgeIndex : edgeIndices)
          if (edgeIndex > e)
            --edgeIndex;
    }

    inline void clear_graph(IndexGraph &g)
    {
      g.incident.clear();
      g.edges.clear();
    }

  } // namespace model

} // namespace ocgl

#endif // OCGL_MODEL_INDEX_GRAPH_H
