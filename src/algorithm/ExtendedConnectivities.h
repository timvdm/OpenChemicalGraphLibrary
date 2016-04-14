#ifndef OCGL_ALGORITHM_EXTENDED_CONNECTIVITIES_H
#define OCGL_ALGORITHM_EXTENDED_CONNECTIVITIES_H

#include <ocgl/PropertyMap.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>

namespace ocgl {

  namespace algorithm {

    namespace impl {

      /**
       * Perform a single Extended Connectivities (EC) iteration.
       */
      template<typename Graph>
      void extendedConnectivitiesIterate(VertexPropertyMap<Graph, unsigned long> &ec)
      {
        VertexPropertyMap<Graph, unsigned long> next = ec;

        for (auto v : getVertices(ec.graph()))
          for (auto w : getAdjacent(ec.graph(), v))
            next[v] += ec[w];

        ec.map().swap(next.map());
      }

      /**
       * Renumber the extended connectivities values to be in the range [0,n-1]
       * where n is the number of unique values.
       */
      template<typename Graph>
      void extendedConnectivitiesRenumber(VertexPropertyMap<Graph, unsigned long> &ec)
      {
        std::set<unsigned long> classes;
        for (auto x : ec.map())
          classes.insert(x);

        unsigned long nextCls = 0;
        for (auto cls : classes) {
          for (auto &x : ec.map())
            if (x == cls)
              x = nextCls;
          ++nextCls;
        }
      }

      template<typename Graph>
      unsigned int numSymmetryClasses(const VertexPropertyMap<Graph, unsigned long> &ec)
      {
        auto values = ec.map();
        std::sort(values.begin(), values.end());
        unsigned int result = 0;
        for (std::size_t i = 1; i < values.size(); ++i)
          if (values[i - 1] != values[i])
            result++;
        return result;
      }

    }

    /**
     * @brief Calculate the Morgan's Extended Connectivities for the specified graph.
     *
     * @param graph The graph.
     * @param vertexInvariant The vertex invariant to use.
     *
     @verbatim
     Morgan, H. L. The Generation of a Unique Machine Description for Chemical
     Structures - A Technique Developed at Chemical Abstracts Service. J. Chem.
     Doc. 1965, 5: 107-112.
     @endverbatim
     *
     * @return The extended connectivities.
     */
    template<typename Graph>
    VertexPropertyMap<Graph, unsigned long> extendedConnectivities(const Graph &g,
        std::function<unsigned long(const typename GraphTraits<Graph>::Vertex &)> vertexInvariant,
        int maxIterations = 100)
    {
      // initial vertex invariants
      VertexPropertyMap<Graph, unsigned long> ec(g);
      for (auto v : getVertices(g))
        ec[v] = vertexInvariant(v);

      // iterate
      unsigned int numClasses = impl::numSymmetryClasses(ec);
      for (int i = 0; i < maxIterations; ++i) { // should never reach 100...
        impl::extendedConnectivitiesIterate(ec);
        unsigned int nextNumClasses = impl::numSymmetryClasses(ec);
        // if the number of unique values didn't change, stop the iteration
        if (numClasses == nextNumClasses)
          break;
        numClasses = nextNumClasses;
      }

      // renumber the EC values
      impl::extendedConnectivitiesRenumber(ec);

      return ec;
    }

  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_EXTENDED_CONNECTIVITIES_H
