#ifndef OCGL_MODEL_ID_GRAPH_H
#define OCGL_MODEL_ID_GRAPH_H

#include <ocgl/Contract.h>
#include <ocgl/Range.h>
#include <ocgl/AdjacentIterator.h>

#include <vector>
#include <limits>

namespace ocgl {

  namespace model {

    /**
     * @brief
     */
    class IdGraph
    {
      public:
        using Vertex = unsigned int;
        using Edge = unsigned int;
        using VertexIter = std::vector<unsigned int>::const_iterator;
        using EdgeIter = std::vector<unsigned int>::const_iterator;
        using IncidentIter = std::vector<unsigned int>::const_iterator;
        using AdjacentIter = AdjacentIterator<IdGraph>;

        IdGraph() = default;

        IdGraph(const IdGraph &other) = default;

        IdGraph(IdGraph &&other) = default;

        ~IdGraph() = default;

        IdGraph& operator=(const IdGraph &other) = default;

        IdGraph& operator=(IdGraph &&other) = default;

        template<typename VertexOrEdge>
        static VertexOrEdge null()
        {
          return std::numeric_limits<unsigned int>::max();
        }

        unsigned int numVertices() const
        {
          return m_vertexIds.size();
        }

        unsigned int numEdges() const
        {
          return m_edgeIds.size();
        }

        unsigned int numVertexIds() const
        {
          return m_incidentIds.size();
        }

        unsigned int numEdgeIds() const
        {
          return m_edgeVertexIds.size();
        }

        Range<VertexIter> vertices() const
        {
          return makeRange(m_vertexIds.begin(), m_vertexIds.end());
        }

        Range<EdgeIter> edges() const
        {
          return makeRange(m_edgeIds.begin(), m_edgeIds.end());
        }

        Vertex vertex(unsigned int id) const
        {
          return id;
        }

        Edge edge(unsigned int id) const
        {
          return id;
        }

        unsigned int degree(Vertex v) const
        {
          return m_incidentIds[v].size();
        }

        Range<IncidentIter> incident(Vertex v) const
        {
          return makeRange(m_incidentIds[v].begin(), m_incidentIds[v].end());
        }

        Range<AdjacentIter> adjacent(Vertex v) const
        {
          auto begin = AdjacentIterator<IdGraph>(*this, v, m_incidentIds[v].begin());
          auto end = AdjacentIterator<IdGraph>(*this, v, m_incidentIds[v].end());
          return makeRange(begin, end);
        }

        Vertex source(Edge e) const
        {
          return m_edgeVertexIds[e].first;
        }

        Vertex target(Edge e) const
        {
          return m_edgeVertexIds[e].second;
        }

        Vertex addVertex();

        void removeVertex(Vertex v);

        Edge addEdge(Vertex v, Vertex w);

        void removeEdge(Edge e);

        void clear();

        void compress();

      private:
        std::vector<unsigned int> m_vertexIds;
        std::vector<unsigned int> m_edgeIds;
        std::vector<std::vector<unsigned int>> m_incidentIds;
        std::vector<std::pair<unsigned int, unsigned int>> m_edgeVertexIds;
    };

    IdGraph::Vertex IdGraph::addVertex()
    {
      auto id = numVertexIds();

      m_vertexIds.push_back(id);
      m_incidentIds.resize(m_incidentIds.size() + 1);

      return id;
    }

    void IdGraph::removeVertex(Vertex v)
    {
      PRE(std::find(m_vertexIds.begin(), m_vertexIds.end(), v) != m_vertexIds.end());

      // make copy of incident edges
      std::vector<unsigned int> incident(m_incidentIds[v]);
      // remove incident edges
      for (auto e : incident)
        removeEdge(e);

      m_vertexIds.erase(std::find(m_vertexIds.begin(), m_vertexIds.end(), v));
      m_incidentIds[v].clear();
    }

    IdGraph::Edge IdGraph::addEdge(Vertex v, Vertex w)
    {
      auto id = numEdgeIds();

      m_incidentIds[v].push_back(id);
      m_incidentIds[w].push_back(id);

      m_edgeIds.push_back(id);
      m_edgeVertexIds.push_back(std::make_pair(v, w));

      return id;
    }

    void IdGraph::removeEdge(Edge e)
    {
      PRE(std::find(m_edgeIds.begin(), m_edgeIds.end(), e) != m_edgeIds.end());

      auto v = m_edgeVertexIds[e].first;
      auto w = m_edgeVertexIds[e].second;

      PRE(std::find(m_incidentIds[v].begin(), m_incidentIds[v].end(), e) != m_incidentIds[v].end());
      PRE(std::find(m_incidentIds[w].begin(), m_incidentIds[w].end(), e) != m_incidentIds[w].end());

      m_incidentIds[v].erase(std::find(m_incidentIds[v].begin(), m_incidentIds[v].end(), e));
      m_incidentIds[w].erase(std::find(m_incidentIds[w].begin(), m_incidentIds[w].end(), e));

      m_edgeIds.erase(std::find(m_edgeIds.begin(), m_edgeIds.end(), e));
      m_edgeVertexIds[e].first = null<Vertex>();
      m_edgeVertexIds[e].second = null<Vertex>();
    }

    void IdGraph::clear()
    {
      m_vertexIds.clear();
      m_edgeIds.clear();
      for (auto &edge : m_edgeVertexIds) {
        edge.first = null<Vertex>();
        edge.second = null<Vertex>();
      }
      for (auto &incident : m_incidentIds)
        incident.clear();
    }

    void IdGraph::compress()
    {
      // FIXME
    }

    inline unsigned int num_vertices(const IdGraph &g)
    {
      return g.numVertices();
    }

    inline unsigned int num_vertex_ids(const IdGraph &g)
    {
      return g.numVertexIds();
    }

    inline unsigned int num_edges(const IdGraph &g)
    {
      return g.numEdges();
    }

    inline unsigned int num_edge_ids(const IdGraph &g)
    {
      return g.numEdgeIds();
    }

    inline Range<IdGraph::VertexIter> get_vertices(const IdGraph &g)
    {
      return g.vertices();
    }

    inline Range<IdGraph::EdgeIter> get_edges(const IdGraph &g)
    {
      return g.edges();
    }

    inline IdGraph::Vertex get_vertex(const IdGraph &g, unsigned int id)
    {
      return g.vertex(id);
    }

    inline IdGraph::Edge get_edge(const IdGraph &g, unsigned int id)
    {
      return g.edge(id);
    }

    inline unsigned int get_id(const IdGraph &g, unsigned int id)
    {
      return id;
    }

    inline unsigned int get_degree(const IdGraph &g,
        IdGraph::Vertex v)
    {
      return g.degree(v);
    }

    inline Range<IdGraph::IncidentIter>
    get_incident(const IdGraph &g, IdGraph::Vertex v)
    {
      return g.incident(v);
    }

    inline Range<IdGraph::AdjacentIter>
    get_adjacent(const IdGraph &g, IdGraph::Vertex v)
    {
      return g.adjacent(v);
    }

    inline IdGraph::Vertex get_source(const IdGraph &g,
        IdGraph::Edge e)
    {
      return g.source(e);
    }

    inline IdGraph::Vertex get_target(const IdGraph &g,
        IdGraph::Edge e)
    {
      return g.target(e);
    }

    inline IdGraph::Vertex add_vertex(IdGraph &g)
    {
      return g.addVertex();
    }

    void remove_vertex(IdGraph &g, IdGraph::Vertex v)
    {
      g.removeVertex(v);
    }

    inline IdGraph::Edge add_edge(IdGraph &g,
        IdGraph::Vertex v, IdGraph::Vertex w)
    {
      return g.addEdge(v, w);
    }

    void remove_edge(IdGraph &g, IdGraph::Edge e)
    {
      g.removeEdge(e);
    }

    inline void clear_graph(IdGraph &g)
    {
      g.clear();
    }

  } // namespace model

} // namespace ocgl

#endif // OCGL_MODEL_POINTER_GRAPH_H
