#ifndef OCGL_MODEL_OBJECT_GRAPH_H
#define OCGL_MODEL_OBJECT_GRAPH_H

#include <ocgl/Contract.h>
#include <ocgl/Range.h>
#include <ocgl/AdjacentIterator.h>

#include <vector>
#include <limits>

namespace ocgl {

  namespace model {

    class ObjectEdge;
    class ObjectGraph;

    class ObjectVertex
    {
      public:
        using IncidentIter = std::vector<ObjectEdge>::const_iterator;
        using AdjacentIter = AdjacentIterator<ObjectGraph>;

        ObjectVertex(const ObjectGraph *g = nullptr,
            unsigned int id = std::numeric_limits<unsigned int>::max())
          : m_graph(g), m_id(id)
        {
        }

        unsigned int id() const
        {
          return m_id;
        }

        unsigned int degree() const;

        Range<IncidentIter> incident() const;

        Range<AdjacentIter> adjacent() const;

        bool operator==(const ObjectVertex &other) const
        {
          return m_graph == other.m_graph && m_id == other.m_id;
        }

        bool operator!=(const ObjectVertex &other) const
        {
          return m_graph != other.m_graph || m_id != other.m_id;
        }

      private:
        friend class ObjectGraph;

        const ObjectGraph *m_graph;
        unsigned int m_id;
    };

    class ObjectEdge
    {
      public:
        ObjectEdge(const ObjectGraph *g = nullptr,
            unsigned int id = std::numeric_limits<unsigned int>::max())
          : m_graph(g), m_id(id)
        {
        }

        unsigned int id() const
        {
          return m_id;
        }

        ObjectVertex source() const;

        ObjectVertex target() const;

        bool operator==(const ObjectEdge &other) const
        {
          return m_graph == other.m_graph && m_id == other.m_id;
        }

        bool operator!=(const ObjectEdge &other) const
        {
          return m_graph != other.m_graph && m_id != other.m_id;
        }

      private:
        friend class ObjectGraph;

        const ObjectGraph *m_graph;
        unsigned int m_id;
    };

    /**
     * @brief
     */
    class ObjectGraph
    {
      public:
        using Vertex = ObjectVertex;
        using Edge = ObjectEdge;
        using VertexIter = std::vector<Vertex>::const_iterator;
        using EdgeIter = std::vector<Edge>::const_iterator;
        using IncidentIter = ObjectVertex::IncidentIter;
        using AdjacentIter = AdjacentIterator<ObjectGraph>;

        ObjectGraph() = default;

        ObjectGraph(const ObjectGraph &other);

        ObjectGraph(ObjectGraph &&other);

        ~ObjectGraph() = default;

        ObjectGraph& operator=(const ObjectGraph &other);

        ObjectGraph& operator=(ObjectGraph &&other);

        template<typename VertexOrEdge>
        static VertexOrEdge null();

        unsigned int numVertices() const
        {
          return m_vertices.size();
        }

        unsigned int numEdges() const
        {
          return m_edges.size();
        }

        unsigned int numVertexIds() const
        {
          return m_incident.size();
        }

        unsigned int numEdgeIds() const
        {
          return m_edgeVertexIds.size();
        }

        Range<VertexIter> vertices() const
        {
          return makeRange(m_vertices.begin(), m_vertices.end());
        }

        Range<EdgeIter> edges() const
        {
          return makeRange(m_edges.begin(), m_edges.end());
        }

        Vertex vertex(unsigned int id) const
        {
          return Vertex(this, id);
        }

        Edge edge(unsigned int id) const
        {
          return Edge(this, id);
        }

        unsigned int degree(unsigned int id) const
        {
          return m_incident[id].size();
        }

        Range<IncidentIter> incident(unsigned id) const
        {
          return makeRange(m_incident[id].begin(), m_incident[id].end());
        }

        Range<AdjacentIter> adjacent(unsigned int id) const
        {
          ObjectVertex v(this, id);
          auto begin = AdjacentIterator<ObjectGraph>(*this, v, m_incident[id].begin());
          auto end = AdjacentIterator<ObjectGraph>(*this, v, m_incident[id].end());
          return makeRange(begin, end);
        }

        ObjectVertex source(unsigned int id) const
        {
          return ObjectVertex(this, m_edgeVertexIds[id].first);
        }

        ObjectVertex target(unsigned int id) const
        {
          return ObjectVertex(this, m_edgeVertexIds[id].second);
        }

        Vertex addVertex();

        void removeVertex(Vertex v);

        Edge addEdge(Vertex v, Vertex w);

        void removeEdge(Edge e);

        void clear();

        void compress();

      private:
        void copy(const ObjectGraph &other);
        void fixPointers();

        std::vector<Vertex> m_vertices;
        std::vector<Edge> m_edges;
        std::vector<std::vector<Edge>> m_incident;
        std::vector<std::pair<unsigned int, unsigned int>> m_edgeVertexIds;
    };

    unsigned int ObjectVertex::degree() const
    {
      return m_graph->degree(m_id);
    }

    Range<ObjectVertex::IncidentIter> ObjectVertex::incident() const
    {
      return m_graph->incident(m_id);
    }

    Range<ObjectVertex::AdjacentIter> ObjectVertex::adjacent() const
    {
      return m_graph->adjacent(m_id);
    }

    ObjectVertex ObjectEdge::source() const
    {
      return m_graph->source(m_id);
    }

    ObjectVertex ObjectEdge::target() const
    {
      return m_graph->target(m_id);
    }

    template<>
    ObjectVertex ObjectGraph::null<ObjectVertex>()
    {
      return ObjectVertex(nullptr, std::numeric_limits<unsigned int>::max());
    }

    template<>
    ObjectEdge ObjectGraph::null<ObjectEdge>()
    {
      return ObjectEdge(nullptr, std::numeric_limits<unsigned int>::max());
    }

    void ObjectGraph::copy(const ObjectGraph &other)
    {
      // copy
      m_vertices = other.m_vertices;
      m_edges = other.m_edges;
      m_incident = other.m_incident;
      m_edgeVertexIds = other.m_edgeVertexIds;

      // fix pointer to this
      fixPointers();
    }

    void ObjectGraph::fixPointers()
    {
      for (auto &v : m_vertices)
        v.m_graph = this;
      for (auto &e : m_edges)
        e.m_graph = this;
      for (auto &incident : m_incident)
        for (auto &e : incident)
          e.m_graph = this;
    }

    ObjectGraph::ObjectGraph(const ObjectGraph &other)
    {
      // copy vertices and edges
      copy(other);
    }

    ObjectGraph::ObjectGraph(ObjectGraph &&other)
    {
      // move memory
      m_vertices = std::move(other.m_vertices);
      m_edges = std::move(other.m_edges);
      m_incident = std::move(other.m_incident);
      m_edgeVertexIds = std::move(other.m_edgeVertexIds);

      // fix pointer to this
      fixPointers();
    }

    ObjectGraph& ObjectGraph::operator=(const ObjectGraph &other)
    {
      // free memory
      m_vertices.clear();
      m_edges.clear();
      m_incident.clear();
      m_edgeVertexIds.clear();

      // copy vertices and edges
      copy(other);

      return *this;
    }

    ObjectGraph& ObjectGraph::operator=(ObjectGraph &&other)
    {
      // free memory
      m_vertices.clear();
      m_edges.clear();
      m_incident.clear();
      m_edgeVertexIds.clear();

      // move memory
      m_vertices = std::move(other.m_vertices);
      m_edges = std::move(other.m_edges);
      m_incident = std::move(other.m_incident);
      m_edgeVertexIds = std::move(other.m_edgeVertexIds);

      // fix pointers to this
      fixPointers();

      return *this;
    }

    ObjectGraph::Vertex ObjectGraph::addVertex()
    {
      auto id = numVertexIds();
      ObjectVertex v(this, id);

      m_vertices.push_back(v);
      m_incident.resize(m_incident.size() + 1);

      return v;
    }

    void ObjectGraph::removeVertex(Vertex v)
    {
      PRE(std::find(m_vertices.begin(), m_vertices.end(), v) != m_vertices.end());

      // make copy of incident edges
      std::vector<ObjectGraph::Edge> incident(m_incident[v.id()].begin(), m_incident[v.id()].end());
      // remove incident edges
      for (auto e : incident)
        removeEdge(e);

      m_vertices.erase(std::find(m_vertices.begin(), m_vertices.end(), v));
      m_incident[v.id()].clear();
    }

    ObjectGraph::Edge ObjectGraph::addEdge(Vertex v, Vertex w)
    {
      auto id = numEdgeIds();
      ObjectEdge e(this, id);

      m_incident[v.id()].push_back(e);
      m_incident[w.id()].push_back(e);

      m_edges.push_back(e);
      m_edgeVertexIds.push_back(std::make_pair(v.id(), w.id()));

      return e;
    }

    void ObjectGraph::removeEdge(Edge e)
    {
      PRE(std::find(m_edges.begin(), m_edges.end(), e) != m_edges.end());

      auto v = source(e.id()).id();
      auto w = target(e.id()).id();

      PRE(std::find(m_incident[v].begin(), m_incident[v].end(), e) != m_incident[v].end());
      PRE(std::find(m_incident[w].begin(), m_incident[w].end(), e) != m_incident[w].end());

      m_incident[v].erase(std::find(m_incident[v].begin(), m_incident[v].end(), e));
      m_incident[w].erase(std::find(m_incident[w].begin(), m_incident[w].end(), e));

      m_edges.erase(std::find(m_edges.begin(), m_edges.end(), e));
      m_edgeVertexIds[e.id()].first = std::numeric_limits<unsigned int>::max();
      m_edgeVertexIds[e.id()].second = std::numeric_limits<unsigned int>::max();
    }

    void ObjectGraph::clear()
    {
      m_vertices.clear();
      m_edges.clear();
      for (auto &edge : m_edgeVertexIds) {
        edge.first = std::numeric_limits<unsigned int>::max();
        edge.second = std::numeric_limits<unsigned int>::max();
      }
      for (auto &incident : m_incident)
        incident.clear();
    }

    void ObjectGraph::compress()
    {
      // FIXME
    }

    inline unsigned int num_vertices(const ObjectGraph &g)
    {
      return g.numVertices();
    }

    inline unsigned int num_vertex_ids(const ObjectGraph &g)
    {
      return g.numVertexIds();
    }

    inline unsigned int num_edges(const ObjectGraph &g)
    {
      return g.numEdges();
    }

    inline unsigned int num_edge_ids(const ObjectGraph &g)
    {
      return g.numEdgeIds();
    }

    inline Range<ObjectGraph::VertexIter> get_vertices(const ObjectGraph &g)
    {
      return g.vertices();
    }

    inline Range<ObjectGraph::EdgeIter> get_edges(const ObjectGraph &g)
    {
      return g.edges();
    }

    inline ObjectGraph::Vertex get_vertex(const ObjectGraph &g, unsigned int id)
    {
      return g.vertex(id);
    }

    inline ObjectGraph::Edge get_edge(const ObjectGraph &g, unsigned int id)
    {
      return g.edge(id);
    }

    inline unsigned int get_id(const ObjectGraph &g, ObjectGraph::Vertex v)
    {
      return v.id();
    }

    inline unsigned int get_degree(const ObjectGraph &g,
        ObjectGraph::Vertex v)
    {
      return v.degree();
    }

    inline Range<ObjectGraph::IncidentIter>
    get_incident(const ObjectGraph &g, ObjectGraph::Vertex v)
    {
      return v.incident();
    }

    inline Range<ObjectGraph::AdjacentIter>
    get_adjacent(const ObjectGraph &g, ObjectGraph::Vertex v)
    {
      return v.adjacent();
    }

    inline unsigned int get_id(const ObjectGraph &g, ObjectGraph::Edge e)
    {
      return e.id();
    }

    inline ObjectGraph::Vertex get_source(const ObjectGraph &g,
        ObjectGraph::Edge e)
    {
      return e.source();
    }

    inline ObjectGraph::Vertex get_target(const ObjectGraph &g,
        ObjectGraph::Edge e)
    {
      return e.target();
    }

    inline ObjectGraph::Vertex add_vertex(ObjectGraph &g)
    {
      return g.addVertex();
    }

    void remove_vertex(ObjectGraph &g, ObjectGraph::Vertex v)
    {
      g.removeVertex(v);
    }

    inline ObjectGraph::Edge add_edge(ObjectGraph &g,
        ObjectGraph::Vertex v, ObjectGraph::Vertex w)
    {
      return g.addEdge(v, w);
    }

    void remove_edge(ObjectGraph &g, ObjectGraph::Edge e)
    {
      g.removeEdge(e);
    }

    inline void clear_graph(ObjectGraph &g)
    {
      g.clear();
    }

  } // namespace model

} // namespace ocgl

#endif // OCGL_MODEL_OBJECT_GRAPH_H
