#ifndef OCGL_GRAPH_STRING_PARSER_H
#define OCGL_GRAPH_STRING_PARSER_H

#include <ocgl/GraphTraits.h>

#include <vector>
#include <string>
#include <map>
#include <stdexcept>

/**
 * @file GraphStringParser.h
 * @brief Parser for SMILES-like graph strings.
 */

namespace ocgl {

  /**
   * @class GraphStringParser GraphStringParser.h <ocgl/GraphStringParser.h>
   * @brief Parser for SMILES-like graph strings.
   */
  template<typename Graph>
  struct GraphStringParser
  {

    /**
     * @brief Parse SMILES-like graph-string.
     *
     * Vertices are represented as '*'. When chained, vertices are connected
     * to the previous vertex using an edge. Using a '.' between vertices will
     * not result in an edge between these two vertices. Branches can be
     * achieved using '(' to start a branch and ')' to close it again.
     * Finally, back edges can be encoded using digits 0-9.
     *
     * Examples:
     * @li chain of 3 vertices: <tt>***</tt>
     * @li central vertex with 3 adjacent vertices: <tt>**(*)*</tt>
     * @li cycle with 4 vertices: <tt>*1***1</tt>
     * @li two disconnected vertices: <tt>*.*</tt>
     *
     * This functions throws a std::runtime_error exception if the input isn't
     * valid. The following errors are possible:
     * @li Invalid character in graph string
     * @li Back edge digit can only be placed after vertex
     * @li Unmatched ')' in graph string
     * @li Unmatched '(' in graph string
     * @li Unmatched back edge in graph string
     *
     * @param str The input grah string.
     *
     * @return The created graph.
     */
    static Graph parse(const std::string &str)
    {
      using Vertex = typename GraphTraits<Graph>::Vertex;

      Graph g;
      std::vector<Vertex> prev(1, nullVertex<Graph>());
      std::map<int, Vertex> backEdges;

      for (auto i = 0; i < str.size(); ++i) {
        auto c = str[i];

        switch (c) {
          case '*':
            {
              // add new vertex
              auto v = addVertex(g);
              // add edge to previous (if needed)
              if (isValid(g, prev.back()))
                addEdge(g, prev.back(), v);
              // set this vertex as previous
              prev.back() = v;
            }
            break;
          case '(':
            // start branch
            prev.push_back(prev.back());
            break;
          case ')':
            // end branch
            if (prev.size() == 1)
              throw std::runtime_error("Unmatched ')' in graph string");
            prev.pop_back();
            break;
          case '.':
            // start new component
            if (prev.size() != 1)
              throw std::runtime_error("Unmatched '(' in graph string");
            prev.clear();
            prev.resize(1, nullVertex<Graph>());
            break;
          case '%':
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            {
              // handle back edge
              if (isNull(g, prev.back()))
                throw std::runtime_error("Back edge number can only be placed after vertex");

              int n = c - '0';
              if (c == '%') {
                if (!std::isdigit(str[i + 1]) || !std::isdigit(str[i + 2]))
                  throw std::runtime_error("Expected two digits after back edge number specifier '%'");

                n = 10 * (str[i + 1] - '0') + str[i + 2] - '0';
                i += 2;
              }

              auto it = backEdges.find(n);
              if (it == backEdges.end()) {
                backEdges[n] = prev.back();
              } else {
                // add edge
                addEdge(g, it->second, prev.back());
                backEdges.erase(it);
              }
            }
            break;
          default:
            throw std::runtime_error("Invalid character in graph string");
        }
      }

      if (prev.size() != 1)
        throw std::runtime_error("Unmatched '(' in graph string");

      if (backEdges.size())
        throw std::runtime_error("Unmatched back edge in graph string");

      return g;
    }

  };

} // namespace ocgl

#endif // OCGL_GRAPH_STRING_PARSER_H
