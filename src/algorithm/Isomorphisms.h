#ifndef OCGL_ALGORITHM_ISOMORPHISM_H
#define OCGL_ALGORITHM_ISOMORPHISM_H

#include <ocgl/algorithm/VF2State.h>
#include <ocgl/algorithm/Backtrack.h>

namespace ocgl {

  namespace algorithm {

    namespace impl {

      template<typename Query, typename Graph>
      void isomorphisms(const Query &query, const Graph &graph, std::function<bool(const VertexPropertyMap<Query, typename GraphTraits<Graph>::Vertex>&)> visitor)
      {
        impl::VF2State<Query, Graph> state(query, graph);
        backtrack(state, visitor);
      }

    } // namespace impl

    template<typename Query, typename Graph, typename Visitor>
    void isomorphisms(const Query &query, const Graph &graph, Visitor visitor)
    {
      impl::isomorphisms<Query, Graph>(query, graph, visitor);
    }

  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_ISOMORPHISM_H

