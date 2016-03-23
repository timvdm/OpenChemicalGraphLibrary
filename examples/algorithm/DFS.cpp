// examples/algorithm/DFS.cpp
#include <ocgl/model/IndexGraph.h>
#include <ocgl/GraphStringParser.h>
#include <ocgl/algorithm/DFS.h>

#include <iostream>

using Graph = ocgl::model::IndexGraph;

struct MyDFSVisitor : public ocgl::algorithm::DFSVisitor<Graph>
{
  void vertex(const Graph &g, Vertex v)
  {
    std::cout << "vertex with index " << ocgl::getIndex(g, v) << std::endl;
  }
};


int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <graph_string>" << std::endl;
    return -1;
  }
  
  std::cout << "graph string: " << argv[1] << std::endl;

  // parse graph string (e.g. **.**.*)
  auto g = ocgl::GraphStringParser<ocgl::model::IndexGraph>::parse(argv[1]);

  // create the DFS visitor
  MyDFSVisitor visitor;

  // perform DFS
  ocgl::algorithm::dfs(g, visitor);
}
