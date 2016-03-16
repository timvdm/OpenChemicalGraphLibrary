#ifndef OCGL_MODEL_POINTER_GRAPH_H
#define OCGL_MODEL_POINTER_GRAPH_H

#include <ocgl/Contract.h>
#include <ocgl/Range.h>
#include <ocgl/AdjacentIterator.h>

#include <vector>
#include <memory>
#include <algorithm>

namespace ocgl {

  namespace model {

    class PointerEdge;
    class PointerGraph;

    class PointerVertex
    {
      public:
        using IncidentIter = std::vector<PointerEdge*>::const_iterator;
        using AdjacentIter = AdjacentIterator<PointerGraph>;

        PointerVertex(unsigned int id) : m_id(id)
        {
        }

        unsigned int id() const
        {
          return m_id;
        }

        unsigned int degree() const
        {
          return m_edges.size();
        }

        Range<IncidentIter> incident() const
        {
          return makeRange(m_edges.begin(), m_edges.end());
        }

        Range<AdjacentIter> adjacent() const;

      private:
        friend class PointerGraph;

        void addEdge(PointerEdge *edge)
        {
          PRE(edge);
          PRE(std::find(m_edges.begin(), m_edges.end(), edge) == m_edges.end());

          m_edges.push_back(edge);
        }

        void removeEdge(PointerEdge *edge)
        {
          PRE(std::find(m_edges.begin(), m_edges.end(), edge) != m_edges.end());

          m_edges.erase(std::find(m_edges.begin(), m_edges.end(), edge));
        }

        std::vector<PointerEdge*> m_edges;
        unsigned int m_id;
    };

    class PointerEdge
    {
      public:
        PointerEdge(PointerVertex *source, PointerVertex *target,
            unsigned int id)
          : m_source(source), m_target(target), m_id(id)
        {
          PRE(source);
          PRE(target);
        }

        unsigned int id() const
        {
          return m_id;
        }

        PointerVertex* source() const
        {
          return m_source;
        }

        PointerVertex* target() const
        {
          return m_target;
        }

      private:
        PointerVertex *m_source;
        PointerVertex *m_target;
        unsigned int m_id;
    };

    /**
     * @brief
     */
    class PointerGraph
    {
      public:
        using Vertex = PointerVertex*;
        using Edge = PointerEdge*;
        using VertexIter = std::vector<Vertex>::const_iterator;
        using EdgeIter = std::vector<Edge>::const_iterator;
        using IncidentIter = PointerVertex::IncidentIter;
        using AdjacentIter = AdjacentIterator<PointerGraph>;

        PointerGraph() = default;

        PointerGraph(const PointerGraph &other);

        PointerGraph(PointerGraph &&other);

        ~PointerGraph() = default;

        PointerGraph& operator=(const PointerGraph &other);

        PointerGraph& operator=(PointerGraph &&other);

        template<typename VertexOrEdge>
        static VertexOrEdge null()
        {
          return nullptr;
        }

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
          return m_id2vertex.size();
        }

        unsigned int numEdgeIds() const
        {
          return m_id2edge.size();
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
          PRE_LT(id, m_id2vertex.size());

          return m_id2vertex[id].get();
        }

        Edge edge(unsigned int id) const
        {
          PRE_LT(id, m_id2edge.size());

          return m_id2edge[id].get();
        }

        Vertex addVertex();

        void removeVertex(Vertex v);

        Edge addEdge(Vertex v, Vertex w);

        void removeEdge(Edge e);

        void clear();

        void compress();

      private:
        void copy(const PointerGraph &other);

        std::vector<Vertex> m_vertices;
        std::vector<Edge> m_edges;
        std::vector<std::unique_ptr<PointerVertex>> m_id2vertex;
        std::vector<std::unique_ptr<PointerEdge>> m_id2edge;
    };

    Range<PointerVertex::AdjacentIter> PointerVertex::adjacent() const
    {
      // works but it's an ugly hack...
      // get_adjacent below has it's own implementation
      const PointerGraph &g = *static_cast<PointerGraph*>(nullptr);
      PointerVertex *v = const_cast<PointerVertex*>(this);
      auto begin = AdjacentIterator<PointerGraph>(g, v, m_edges.begin());
      auto end = AdjacentIterator<PointerGraph>(g, v, m_edges.end());
      return makeRange(begin, end);
    }

    void PointerGraph::copy(const PointerGraph &other)
    {
      // reserve memory
      m_vertices.reserve(other.m_vertices.size());
      m_edges.reserve(other.m_edges.size());
      m_id2vertex.reserve(other.m_id2vertex.size());
      m_id2edge.reserve(other.m_id2edge.size());

      // copy vertices
      for (auto &v : other.m_id2vertex) {
        if (v) {
          auto w = new PointerVertex(v->id());
          m_vertices.push_back(w);
          m_id2vertex.push_back(std::unique_ptr<PointerVertex>(w));
        } else {
          m_id2vertex.push_back(nullptr);
        }
      }

      // copy edges
      for (auto &e : other.m_id2edge) {
        if (e) {
          auto v = m_id2vertex[e->source()->id()].get();
          auto w = m_id2vertex[e->target()->id()].get();
          auto f = new PointerEdge(v, w, e->id());
          m_edges.push_back(f);
          m_id2edge.push_back(std::unique_ptr<PointerEdge>(f));
        } else {
          m_id2edge.push_back(nullptr);
        }
      }
    }

    PointerGraph::PointerGraph(const PointerGraph &other)
    {
      // copy vertices and edges
      copy(other);
    }

    PointerGraph::PointerGraph(PointerGraph &&other)
    {
      // move memory
      m_vertices = std::move(other.m_vertices);
      m_edges = std::move(other.m_edges);
      m_id2vertex = std::move(other.m_id2vertex);
      m_id2edge = std::move(other.m_id2edge);
    }

    PointerGraph& PointerGraph::operator=(const PointerGraph &other)
    {
      // free memory
      m_vertices.clear();
      m_edges.clear();
      m_id2vertex.clear();
      m_id2edge.clear();

      // copy vertices and edges
      copy(other);

      return *this;
    }

    PointerGraph& PointerGraph::operator=(PointerGraph &&other)
    {
      // free memory
      m_vertices.clear();
      m_edges.clear();
      m_id2vertex.clear();
      m_id2edge.clear();

      // move memory
      m_vertices = std::move(other.m_vertices);
      m_edges = std::move(other.m_edges);
      m_id2vertex = std::move(other.m_id2vertex);
      m_id2edge = std::move(other.m_id2edge);

      return *this;
    }

    PointerGraph::Vertex PointerGraph::addVertex()
    {
      auto id = numVertexIds();
      auto v = new PointerVertex(id);

      m_vertices.push_back(v);
      m_id2vertex.push_back(std::unique_ptr<PointerVertex>(v));

      return v;
    }

    void PointerGraph::removeVertex(Vertex v)
    {
      PRE(std::find(m_vertices.begin(), m_vertices.end(), v) != m_vertices.end());

      // make copy of incident edges
      std::vector<PointerGraph::Edge> incident(v->incident().begin(), v->incident().end());
      // remove incident edges
      for (auto e : incident)
        removeEdge(e);

      m_vertices.erase(std::find(m_vertices.begin(), m_vertices.end(), v));
      m_id2vertex[v->id()].reset();
    }

    PointerGraph::Edge PointerGraph::addEdge(Vertex v, Vertex w)
    {
      auto id = numEdgeIds();
      auto e = new PointerEdge(v, w, id);

      v->addEdge(e);
      w->addEdge(e);

      m_edges.push_back(e);
      m_id2edge.push_back(std::unique_ptr<PointerEdge>(e));

      return e;
    }

    void PointerGraph::removeEdge(Edge e)
    {
      PRE(std::find(m_edges.begin(), m_edges.end(), e) != m_edges.end());

      auto v = e->source();
      auto w = e->target();

      v->removeEdge(e);
      w->removeEdge(e);

      m_edges.erase(std::find(m_edges.begin(), m_edges.end(), e));
      m_id2edge[e->id()].reset();
    }

    void PointerGraph::clear()
    {
      m_vertices.clear();
      m_edges.clear();
      for (auto &v : m_id2vertex)
        v.reset();
      for (auto &e : m_id2edge)
        e.reset();
    }

    void PointerGraph::compress()
    {
      // FIXME
    }

    inline unsigned int num_vertices(const PointerGraph &g)
    {
      return g.numVertices();
    }

    inline unsigned int num_vertex_ids(const PointerGraph &g)
    {
      return g.numVertexIds();
    }

    inline unsigned int num_edges(const PointerGraph &g)
    {
      return g.numEdges();
    }

    inline unsigned int num_edge_ids(const PointerGraph &g)
    {
      return g.numEdgeIds();
    }

    inline Range<PointerGraph::VertexIter> get_vertices(const PointerGraph &g)
    {
      return g.vertices();
    }

    inline Range<PointerGraph::EdgeIter> get_edges(const PointerGraph &g)
    {
      return g.edges();
    }

    inline PointerGraph::Vertex get_vertex(const PointerGraph &g, unsigned int id)
    {
      return g.vertex(id);
    }

    inline PointerGraph::Edge get_edge(const PointerGraph &g, unsigned int id)
    {
      return g.edge(id);
    }

    inline unsigned int get_id(const PointerGraph &g, PointerGraph::Vertex v)
    {
      return v->id();
    }

    inline unsigned int get_degree(const PointerGraph &g,
        PointerGraph::Vertex v)
    {
      return v->degree();
    }

    inline Range<PointerGraph::IncidentIter>
    get_incident(const PointerGraph &g, PointerGraph::Vertex v)
    {
      return v->incident();
    }

    inline Range<PointerGraph::AdjacentIter>
    get_adjacent(const PointerGraph &g, PointerGraph::Vertex v)
    {
      //return v->adjacent();
      auto incident = get_incident(g, v);
      auto begin = AdjacentIterator<PointerGraph>(g, v, incident.begin());
      auto end = AdjacentIterator<PointerGraph>(g, v, incident.end());
      return makeRange(begin, end);
    }

    inline unsigned int get_id(const PointerGraph &g, PointerGraph::Edge e)
    {
      return e->id();
    }

    inline PointerGraph::Vertex get_source(const PointerGraph &g,
        PointerGraph::Edge e)
    {
      return e->source();
    }

    inline PointerGraph::Vertex get_target(const PointerGraph &g,
        PointerGraph::Edge e)
    {
      return e->target();
    }

    inline PointerGraph::Vertex add_vertex(PointerGraph &g)
    {
      return g.addVertex();
    }

    void remove_vertex(PointerGraph &g, PointerGraph::Vertex v)
    {
      g.removeVertex(v);
    }

    inline PointerGraph::Edge add_edge(PointerGraph &g,
        PointerGraph::Vertex v, PointerGraph::Vertex w)
    {
      return g.addEdge(v, w);
    }

    void remove_edge(PointerGraph &g, PointerGraph::Edge e)
    {
      g.removeEdge(e);
    }

    inline void clear_graph(PointerGraph &g)
    {
      g.clear();
    }

  } // namespace model

} // namespace ocgl

#endif // OCGL_MODEL_POINTER_GRAPH_H
