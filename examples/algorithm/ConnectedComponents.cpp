// examples/algorithm/ConnectedComponents.cpp
#include <ocgl/model/IndexGraph.h>
#include <ocgl/GraphStringParser.h>
#include <ocgl/algorithm/ConnectedComponents.h>

#include <iostream>

using Graph = ocgl::model::IndexGraph;

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <graph_string>" << std::endl;
    return -1;
  }
  
  std::cout << "graph string: " << argv[1] << std::endl;

  // parse graph string (e.g. **.**.*)
  auto g = ocgl::GraphStringParser<Graph>::parse(argv[1]);

  // determine the components...
  // type: ocgl::VertexEdgePropertyMap<Graph, unsigned int>
  //       map vertices and edges to component index
  auto components = ocgl::algorithm::connectedComponents(g);

  // print the number of components
  auto numComponents = ocgl::algorithm::numConnectedComponents(components);
  std::cout << "# components: " << numComponents << std::endl;

  // print the vertex and edge ids for each component
  for (auto c = 0; c < numComponents; ++c) {
    // component index
    std::cout << "component index: " << c << std::endl;

    // vertex ids
    std::cout << "  vertex indices: ";
    for (auto v : ocgl::getVertices(g))
      if (components.vertices[v] == c)
        std::cout << ocgl::getIndex(g, v) << " ";
    std::cout << std::endl;

    // vertex ids
    std::cout << "  edge indices: ";
    for (auto e : ocgl::getEdges(g))
      if (components.edges[e] == c)
        std::cout << ocgl::getIndex(g, e) << " ";
    std::cout << std::endl;
  }
}
