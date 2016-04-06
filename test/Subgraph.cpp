#include <ocgl/Subgraph.h>
#include <ocgl/algorithm/CycleMembership.h>
#include <ocgl/algorithm/ConnectedComponents.h>
#include <ocgl/algorithm/RelevantCycles.h>

#include "test.h"

GRAPH_TYPED_TEST(SubgraphTest);

TYPED_TEST(SubgraphTest, Subgraph1)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);
  auto v4 = ocgl::addVertex(g);

  auto e0 = ocgl::addEdge(g, v0, v1);
  auto e1 = ocgl::addEdge(g, v1, v2);
  auto e2 = ocgl::addEdge(g, v2, v3);
  auto e3 = ocgl::addEdge(g, v3, v4);

  ocgl::VertexEdgePropertyMap<Graph, bool> mask(g);

  mask.vertices[v0] = true;
  mask.vertices[v1] = true;
  mask.vertices[v2] = false;
  mask.vertices[v3] = true;
  mask.vertices[v4] = true;

  mask.edges[e0] = true;
  mask.edges[e1] = false;
  mask.edges[e2] = false;
  mask.edges[e3] = true;

  ocgl::Subgraph<Graph> subg(g, mask);

  // numVertices & numEdges
  EXPECT_EQ(4, ocgl::numVertices(subg));
  EXPECT_EQ(2, ocgl::numEdges(subg));

  // getVertices
  auto V = ocgl::getVertices(subg).toVector();
  ASSERT_EQ(4, V.size());
  EXPECT_EQ(v0, V[0]);
  EXPECT_EQ(v1, V[1]);
  EXPECT_EQ(v3, V[2]);
  EXPECT_EQ(v4, V[3]);

  // getEdges
  auto E = ocgl::getEdges(subg).toVector();
  ASSERT_EQ(2, E.size());
  EXPECT_EQ(e0, E[0]);
  EXPECT_EQ(e3, E[1]);

  // getVertex
  EXPECT_EQ(v0, ocgl::getVertex(subg, 0));
  EXPECT_EQ(v1, ocgl::getVertex(subg, 1));
  EXPECT_EQ(v3, ocgl::getVertex(subg, 2));
  EXPECT_EQ(v4, ocgl::getVertex(subg, 3));

  // getEdge
  EXPECT_EQ(e0, ocgl::getEdge(subg, 0));
  EXPECT_EQ(e3, ocgl::getEdge(subg, 1));

  // getVertexIndex
  EXPECT_EQ(0, ocgl::getVertexIndex(subg, v0));
  EXPECT_EQ(1, ocgl::getVertexIndex(subg, v1));
  EXPECT_EQ(2, ocgl::getVertexIndex(subg, v3));
  EXPECT_EQ(3, ocgl::getVertexIndex(subg, v4));

  // getEdgeIndex
  EXPECT_EQ(0, ocgl::getEdgeIndex(subg, e0));
  EXPECT_EQ(1, ocgl::getEdgeIndex(subg, e3));

  // getDegree
  EXPECT_EQ(1, ocgl::getDegree(subg, v0));
  EXPECT_EQ(1, ocgl::getDegree(subg, v1));
  EXPECT_EQ(1, ocgl::getDegree(subg, v3));
  EXPECT_EQ(1, ocgl::getDegree(subg, v4));

  // getIncident
  auto incident0 = ocgl::getIncident(subg, v0).toVector();
  ASSERT_EQ(1, incident0.size());
  EXPECT_EQ(e0, incident0[0]);

  auto incident1 = ocgl::getIncident(subg, v1).toVector();
  ASSERT_EQ(1, incident1.size());
  EXPECT_EQ(e0, incident1[0]);

  auto incident3 = ocgl::getIncident(subg, v3).toVector();
  ASSERT_EQ(1, incident3.size());
  EXPECT_EQ(e3, incident3[0]);

  auto incident4 = ocgl::getIncident(subg, v4).toVector();
  ASSERT_EQ(1, incident4.size());
  EXPECT_EQ(e3, incident4[0]);

  // getAdjacent
  auto adjacent0 = ocgl::getAdjacent(subg, v0).toVector();
  ASSERT_EQ(1, adjacent0.size());
  EXPECT_EQ(v1, adjacent0[0]);

  auto adjacent1 = ocgl::getAdjacent(subg, v1).toVector();
  ASSERT_EQ(1, adjacent1.size());
  EXPECT_EQ(v0, adjacent1[0]);

  auto adjacent3 = ocgl::getAdjacent(subg, v3).toVector();
  ASSERT_EQ(1, adjacent3.size());
  EXPECT_EQ(v4, adjacent3[0]);

  auto adjacent4 = ocgl::getAdjacent(subg, v4).toVector();
  ASSERT_EQ(1, adjacent4.size());
  EXPECT_EQ(v3, adjacent4[0]);

  // getSource
  EXPECT_EQ(v0, ocgl::getSource(subg, e0));
  EXPECT_EQ(v3, ocgl::getSource(subg, e3));

  // getTarget
  EXPECT_EQ(v1, ocgl::getTarget(subg, e0));
  EXPECT_EQ(v4, ocgl::getTarget(subg, e3));
}


template<typename Graph>
std::vector<typename ocgl::Subgraph<Graph>::Type> getSubgraphs(const Graph &g)
{
  return std::vector<typename ocgl::Subgraph<Graph>::Type>();
}

template<typename Graph>
std::vector<typename ocgl::Subgraph<Graph>::Type> getSubgraphs(const Graph &g, const ocgl::VertexPropertyMap<Graph, bool> &props)
{
  return std::vector<typename ocgl::Subgraph<Graph>::Type>();
}

TYPED_TEST(SubgraphTest, SubgraphRecursive)
{
  using Graph = TypeParam;
  auto g = ocgl::GraphStringParser<Graph>::parse("****");

  ocgl::VertexPropertyMap<Graph, bool> vertexMask(g, true);
  ocgl::EdgePropertyMap<Graph, bool> edgeMask(g, true);

  ocgl::Subgraph<Graph> subg0 = ocgl::makeSubgraph<Graph>(g, vertexMask, edgeMask);

  std::vector<typename ocgl::Subgraph<Graph>::Type> subgraphs0 = getSubgraphs(g);

  std::vector<typename ocgl::Subgraph<Graph>::Type> subgraphs1 = getSubgraphs(subg0);

  std::vector<typename ocgl::Subgraph<Graph>::Type> subgraphs2 = getSubgraphs(g, ocgl::VertexPropertyMap<Graph, bool>(g));
  std::vector<typename ocgl::Subgraph<Graph>::Type> subgraphs3 = getSubgraphs(subg0, ocgl::VertexPropertyMap<ocgl::Subgraph<Graph>, bool>(subg0));

}

TYPED_TEST(SubgraphTest, Subgraph2)
{
  using Graph = TypeParam;

  auto g = ocgl::GraphStringParser<Graph>::parse("*1*****1**2*****2");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  EXPECT_EQ(13, ocgl::numVertices(g));
  EXPECT_EQ(14, ocgl::numEdges(g));

  //
  // step 1: create subgraph with only cyclic vertices and edges
  //
  auto cycleMembership = ocgl::algorithm::cycleMembership(g);

  ocgl::Subgraph<Graph> cycleGraph(g, cycleMembership);

  EXPECT_EQ(12, ocgl::numVertices(cycleGraph));
  EXPECT_EQ(12, ocgl::numEdges(cycleGraph));

  //
  // step 2: create subgraphs from cyclic connected components
  //
  std::vector<ocgl::Subgraph<Graph>> cycleSubgraphs = ocgl::algorithm::connectedComponentsSubgraphs(cycleGraph);
  ASSERT_EQ(2, cycleSubgraphs.size());

  // subgraph 1
  const typename ocgl::Subgraph<Graph>::Type &subg0 = cycleSubgraphs[0];
  ASSERT_EQ(6, ocgl::numVertices(subg0));
  ASSERT_EQ(6, ocgl::numEdges(subg0));

  EXPECT_EQ(V[0], ocgl::getVertex(subg0, 0));
  EXPECT_EQ(V[1], ocgl::getVertex(subg0, 1));
  EXPECT_EQ(V[2], ocgl::getVertex(subg0, 2));
  EXPECT_EQ(V[3], ocgl::getVertex(subg0, 3));
  EXPECT_EQ(V[4], ocgl::getVertex(subg0, 4));
  EXPECT_EQ(V[5], ocgl::getVertex(subg0, 5));

  EXPECT_EQ(E[0], ocgl::getEdge(subg0, 0));
  EXPECT_EQ(E[1], ocgl::getEdge(subg0, 1));
  EXPECT_EQ(E[2], ocgl::getEdge(subg0, 2));
  EXPECT_EQ(E[3], ocgl::getEdge(subg0, 3));
  EXPECT_EQ(E[4], ocgl::getEdge(subg0, 4));
  EXPECT_EQ(E[5], ocgl::getEdge(subg0, 5));

  // subgraph 2
  const typename ocgl::Subgraph<Graph>::Type &subg1 = cycleSubgraphs[1];
  ASSERT_EQ(6, ocgl::numVertices(subg1));
  ASSERT_EQ(6, ocgl::numEdges(subg1));

  EXPECT_EQ(V[7], ocgl::getVertex(subg1, 0));
  EXPECT_EQ(V[8], ocgl::getVertex(subg1, 1));
  EXPECT_EQ(V[9], ocgl::getVertex(subg1, 2));
  EXPECT_EQ(V[10], ocgl::getVertex(subg1, 3));
  EXPECT_EQ(V[11], ocgl::getVertex(subg1, 4));
  EXPECT_EQ(V[12], ocgl::getVertex(subg1, 5));

  EXPECT_EQ(E[8], ocgl::getEdge(subg1, 0));
  EXPECT_EQ(E[9], ocgl::getEdge(subg1, 1));
  EXPECT_EQ(E[10], ocgl::getEdge(subg1, 2));
  EXPECT_EQ(E[11], ocgl::getEdge(subg1, 3));
  EXPECT_EQ(E[12], ocgl::getEdge(subg1, 4));
  EXPECT_EQ(E[13], ocgl::getEdge(subg1, 5));

  EXPECT_EQ(0, ocgl::getVertexIndex(subg1, ocgl::getVertex(subg1, 0)));
  EXPECT_EQ(1, ocgl::getVertexIndex(subg1, ocgl::getVertex(subg1, 1)));
  EXPECT_EQ(2, ocgl::getVertexIndex(subg1, ocgl::getVertex(subg1, 2)));
  EXPECT_EQ(3, ocgl::getVertexIndex(subg1, ocgl::getVertex(subg1, 3)));
  EXPECT_EQ(4, ocgl::getVertexIndex(subg1, ocgl::getVertex(subg1, 4)));
  EXPECT_EQ(5, ocgl::getVertexIndex(subg1, ocgl::getVertex(subg1, 5)));

  EXPECT_EQ(7, ocgl::getVertexIndex(g, ocgl::getVertex(subg1, 0)));
  EXPECT_EQ(6, ocgl::getVertexIndex(cycleGraph, ocgl::getVertex(subg1, 0)));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
