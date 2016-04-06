// examples/algorithm/CycleMembership.cpp
#include <ocgl/model/IndexGraph.h>
#include <ocgl/GraphStringParser.h>
#include <ocgl/algorithm/CycleMembership.h>

#include <iostream>

using Graph = ocgl::model::IndexGraph;

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <graph_string>" << std::endl;
    return -1;
  }

  std::cout << "graph string: " << argv[1] << std::endl;

  // parse graph string (e.g. *1***1*)
  auto g = ocgl::GraphStringParser<Graph>::parse(argv[1]);

  // determine cycle membership...
  // type: ocgl::VertexEdgePropertyMap<Graph, bool>
  auto isCyclic = ocgl::algorithm::cycleMembership(g);

  // print acylic vertices
  std::cout << "acylic vertex indices: ";
  for (auto v : ocgl::getVertices(g))
    if (!isCyclic.vertices[v])
      std::cout << ocgl::getVertexIndex(g, v) << " ";
  std::cout << std::endl;

  // print acylic edges
  std::cout << "acylic edge indices  : ";
  for (auto e : ocgl::getEdges(g))
    if (!isCyclic.edges[e])
      std::cout << ocgl::getEdgeIndex(g, e) << " ";
  std::cout << std::endl;

  // print cylic vertices
  std::cout << "cylic vertex indices : ";
  for (auto v : ocgl::getVertices(g))
    if (isCyclic.vertices[v])
      std::cout << ocgl::getVertexIndex(g, v) << " ";
  std::cout << std::endl;

  // print cylic vertices
  std::cout << "cylic edge indices   : ";
  for (auto e : ocgl::getEdges(g))
    if (isCyclic.edges[e])
      std::cout << ocgl::getEdgeIndex(g, e) << " ";
  std::cout << std::endl;
}
