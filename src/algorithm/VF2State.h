#ifndef OCGL_ALGORITHM_VF2STATE_H
#define OCGL_ALGORITHM_VF2STATE_H

#include <ocgl/PropertyMap.h>
#include <functional>
#include <vector>
#include <limits>
#include <iostream>

namespace ocgl {

  namespace algorithm {

    namespace impl {

      template<typename QueryT, typename GraphT>
      class VF2State
      {
        public:
          using Query = QueryT;
          using Graph = GraphT;

          using QueryVertex = typename GraphTraits<Query>::Vertex;
          using QueryEdge = typename GraphTraits<Query>::Edge;
          using GraphVertex = typename GraphTraits<Graph>::Vertex;
          using GraphEdge = typename GraphTraits<Graph>::Edge;

          using VertexMatcher = std::function<bool(const QueryVertex&, const GraphVertex&)>;
          using EdgeMatcher = std::function<bool(const QueryEdge&, const GraphEdge&)>;

          using Solution = VertexPropertyMap<Query, GraphVertex>;

          static constexpr VertexIndex NoIndex()
          {
            return std::numeric_limits<VertexIndex>::max();
          }

          VF2State(const Query &query, const Graph &graph,
              VertexMatcher vertexMatcher = nullptr,
              EdgeMatcher edgeMatcher = nullptr)
            : m_query(&query), m_graph(&graph),
              m_queryMap(numVertices(query), NoIndex()),
              m_graphMap(numVertices(graph), NoIndex()),
              m_vertexMatcher(vertexMatcher),
              m_edgeMatcher(edgeMatcher),
              m_queryTUM(numVertices(query), 0),
              m_graphTUM(numVertices(graph), 0),
              m_mapSize(0), m_queryTUMSize(0), m_graphTUMSize(0)
          {
          }

          const Query& query() const
          {
            return *m_query;
          }

          const Graph& graph() const
          {
            return *m_graph;
          }

          unsigned int queryTSize() const
          {
            return m_queryTUMSize - m_mapSize;
          }

          unsigned int graphTSize() const
          {
            return m_graphTUMSize - m_mapSize;
          }

          bool isInQueryM(VertexIndex u) const
          {
            return m_queryMap[u] != NoIndex();
          }

          bool isInGraphM(Index v) const
          {
            return m_graphMap[v] != NoIndex();
          }

          bool isInQueryT(Index u) const
          {
            return m_queryTUM[u] != 0 && !isInQueryM(u);
          }

          bool isInGraphT(Index v) const
          {
            return m_graphTUM[v] != 0 && !isInGraphM(v);
          }

         /*
          const Mapping<Query, Graph>& mapping() const
          {
            return m_mapping;
          }
          */

          bool nextPair(QueryVertex &u, GraphVertex &v)
          {
            Index ui = isValidVertex(query(), u) ? getVertexIndex(query(), u) : 0;
            Index vi = isValidVertex(graph(), v) ? getVertexIndex(graph(), v) + 1 : 0;

            auto querySize = numVertices(query());
            auto graphSize = numVertices(graph());

            if (queryTSize() && graphTSize()) {
              // both queryT(s) and graphT(s) are not empty
              // P(s) = queryT(s) x { min graphT(s) }
              while (ui < querySize && !isInQueryT(ui)) {
                ++ui;
                vi = 0;
              }
              while (vi < graphSize && !isInGraphT(vi))
                ++vi;
            } else {
              // P(s) = ( queryN - queryM ) x { min ( graphN - graphM ) }
              while (ui < querySize && isInQueryM(ui)) {
                ++ui;
                vi = 0;
              }
              while (vi < graphSize && isInGraphM(vi))
                ++vi;
            }

            if (ui < querySize && vi < graphSize) {
              u = getVertex(query(), ui);
              v = getVertex(graph(), vi);

              if (isFeasiblePair(u, v)) {
                addPair(u, v);
                return true;
              }

              return nextPair(u, v);
            }

            u = NoIndex();
            v = NoIndex();

            return false;
          }

          bool isFeasiblePair(QueryVertex u, GraphVertex v)
          {
            //std::cout <<"isFeasiblePair(" << u.index() << ", " << v.index() << ")" << std::endl;

            // compare vertex labels if there is a vertex matcher
            if (m_vertexMatcher && !m_vertexMatcher(u, v))
              return false;

            auto ui = getVertexIndex(query(), u);
            auto vi = getVertexIndex(graph(), v);

            // the number of nbrs u that has in query T should not be larger
            // than the number of nbrs v has in graph T
            int queryNbrTSize = 0;
            for (auto w : getAdjacent(query(), u))
              if (isInQueryT(getVertexIndex(query(), w)))
                ++queryNbrTSize;
            int graphNbrTSize = 0;
            for (auto w : getAdjacent(graph(), v))
              if (isInGraphT(getVertexIndex(graph(), w)))
                ++graphNbrTSize;

            if (queryNbrTSize > graphNbrTSize)
              return false;

            // for each nbr of u that is in query M, there should be a matching
            // edge in the graph
            for (auto e : getIncident(query(), u)) {
              auto w = getOther(query(), e, u);
              auto wi = getVertexIndex(query(), w);
              if (!isInQueryM(wi))
                continue;

              auto wGraph = getVertex(graph(), m_queryMap[wi]);
              auto eGraph = getEdge(graph(), v, wGraph);
              if (!isValidEdge(graph(), eGraph))
                return false;

              if (m_edgeMatcher && !m_edgeMatcher(e, eGraph))
                return false;
            }

            return true;
          }

          void addPair(QueryVertex u, GraphVertex v)
          {
            //std::cout <<"addPair(" << getVertexIndex(query(), u) << ", " << getVertexIndex(graph(), v) << ")" << std::endl;

            auto ui = getVertexIndex(query(), u);
            auto vi = getVertexIndex(graph(), v);

            // add (u, v) to mapping
            ++m_mapSize;
            m_queryMap[ui] = vi;
            m_graphMap[vi] = ui;

            // add u to query T U M (if needed)
            if (!m_queryTUM[ui]) {
              m_queryTUM[ui] = m_mapSize;
              ++m_queryTUMSize;
            }

            // add nbrs of u to query T U M (if needed)
            for (auto w : getAdjacent(query(), u)) {
              auto wi = getVertexIndex(query(), w);
              if (!m_queryTUM[wi]) {
                m_queryTUM[wi] = m_mapSize;
                ++m_queryTUMSize;
              }
            }

            // add v to graph T U M (if needed)
            if (!m_graphTUM[vi]) {
              m_graphTUM[vi] = m_mapSize;
              ++m_graphTUMSize;
            }

            // add nbrs of v to graph T U M (if needed)
            for (auto w : getAdjacent(graph(), v)) {
              auto wi = getVertexIndex(graph(), w);
              if (!m_graphTUM[wi]) {
                m_graphTUM[wi] = m_mapSize;
                ++m_graphTUMSize;
              }
            }
          }

          void removePair(QueryVertex u, GraphVertex v)
          {
            //std::cout <<"removePair(" << u.index() << ", " << v.index() << ")" << std::endl;

            auto ui = getVertexIndex(query(), u);
            auto vi = getVertexIndex(graph(), v);

            // remove u from query T U M (if needed)
            if (m_queryTUM[ui] == m_mapSize) {
              m_queryTUM[ui] = 0;
              --m_queryTUMSize;
            }

            // remove nbrs of u from query T U M (if needed)
            for (auto w : getAdjacent(query(), u)) {
              auto wi = getVertexIndex(query(), w);
              if (m_queryTUM[wi] == m_mapSize) {
                m_queryTUM[wi] = 0;
                --m_queryTUMSize;
              }
            }

            // remove v from graph T U M (if needed)
            if (m_graphTUM[vi] == m_mapSize) {
              m_graphTUM[vi] = 0;
              --m_graphTUMSize;
            }

            // remoeve nbrs of v from graph T U M (if needed)
            for (auto w : getAdjacent(graph(), v)) {
              auto wi = getVertexIndex(graph(), w);
              if (m_graphTUM[wi] == m_mapSize) {
                m_graphTUM[wi] = 0;
                --m_graphTUMSize;
              }
            }

            // remove (u, v) from mapping
            --m_mapSize;
            m_queryMap[ui] = NoIndex();
            m_graphMap[vi] = NoIndex();
          }

          struct LocalState
          {
            QueryVertex u;
            GraphVertex v;
          };

          static LocalState local()
          {
            return LocalState{nullVertex<Query>(), nullVertex<Graph>()};
          }

          bool isGoal() const
          {
            return m_mapSize == numVertices(query());
          }

          bool isDead() const
          {
            return queryTSize() > graphTSize();
          }

          bool next(LocalState &local)
          {
            return nextPair(local.u, local.v);
          }

          void backtrack(const LocalState &local)
          {
            removePair(local.u, local.v);
          }

          Solution solution() const
          {
            VertexPropertyMap<Query, GraphVertex> map(query());
            for (auto v : getVertices(query()))
              map[v] = getVertex(graph(), m_queryMap[getVertexIndex(query(), v)]);
            return map;
          }

        private:
          const Query *m_query;
          const Graph *m_graph;
          VertexMatcher m_vertexMatcher;
          EdgeMatcher m_edgeMatcher;
          std::vector<VertexIndex> m_queryMap;
          std::vector<VertexIndex> m_graphMap;
          std::vector<VertexIndex> m_queryTUM;
          std::vector<VertexIndex> m_graphTUM;
          unsigned int m_mapSize;
          unsigned int m_queryTUMSize;
          unsigned int m_graphTUMSize;
      };

    } // namespace impl

  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_VF2STATE_H
