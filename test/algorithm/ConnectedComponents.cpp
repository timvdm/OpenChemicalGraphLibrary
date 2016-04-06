#include <ocgl/algorithm/ConnectedComponents.h>

#include "../test.h"

GRAPH_TYPED_TEST(ConnectedComponentsTest);

TYPED_TEST(ConnectedComponentsTest, Components1)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*");
  auto V = ocgl::getVertices(g).toVector();

  EXPECT_EQ(1, ocgl::algorithm::numConnectedComponents(g));

  auto components = ocgl::algorithm::connectedComponents(g);
  EXPECT_EQ(1, ocgl::algorithm::numConnectedComponents(components));
  EXPECT_EQ(0, components.vertices[V[0]]);
}

TYPED_TEST(ConnectedComponentsTest, Components2)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*.*");
  auto V = ocgl::getVertices(g).toVector();

  EXPECT_EQ(2, ocgl::algorithm::numConnectedComponents(g));

  auto components = ocgl::algorithm::connectedComponents(g);
  EXPECT_EQ(2, ocgl::algorithm::numConnectedComponents(components));
  EXPECT_EQ(0, components.vertices[V[0]]);
  EXPECT_EQ(1, components.vertices[V[1]]);
}

TYPED_TEST(ConnectedComponentsTest, Components3)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("***");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  EXPECT_EQ(1, ocgl::algorithm::numConnectedComponents(g));

  auto components = ocgl::algorithm::connectedComponents(g);
  EXPECT_EQ(1, ocgl::algorithm::numConnectedComponents(components));
  EXPECT_EQ(0, components.vertices[V[0]]);
  EXPECT_EQ(0, components.vertices[V[1]]);
  EXPECT_EQ(0, components.vertices[V[2]]);
  EXPECT_EQ(0, components.edges[E[0]]);
  EXPECT_EQ(0, components.edges[E[1]]);
}

TYPED_TEST(ConnectedComponentsTest, Components4)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("***.**");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  EXPECT_EQ(2, ocgl::algorithm::numConnectedComponents(g));

  auto components = ocgl::algorithm::connectedComponents(g);
  EXPECT_EQ(2, ocgl::algorithm::numConnectedComponents(components));
  EXPECT_EQ(0, components.vertices[V[0]]);
  EXPECT_EQ(0, components.vertices[V[1]]);
  EXPECT_EQ(0, components.vertices[V[2]]);
  EXPECT_EQ(1, components.vertices[V[3]]);
  EXPECT_EQ(1, components.vertices[V[4]]);
  EXPECT_EQ(0, components.edges[E[0]]);
  EXPECT_EQ(0, components.edges[E[1]]);
  EXPECT_EQ(1, components.edges[E[2]]);
}

TYPED_TEST(ConnectedComponentsTest, Components5)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*1**1.*1**1");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  EXPECT_EQ(2, ocgl::algorithm::numConnectedComponents(g));

  auto components = ocgl::algorithm::connectedComponents(g);
  EXPECT_EQ(2, ocgl::algorithm::numConnectedComponents(components));
  EXPECT_EQ(0, components.vertices[V[0]]);
  EXPECT_EQ(0, components.vertices[V[1]]);
  EXPECT_EQ(0, components.vertices[V[2]]);
  EXPECT_EQ(1, components.vertices[V[3]]);
  EXPECT_EQ(1, components.vertices[V[4]]);
  EXPECT_EQ(1, components.vertices[V[5]]);
  EXPECT_EQ(0, components.edges[E[0]]);
  EXPECT_EQ(0, components.edges[E[1]]);
  EXPECT_EQ(0, components.edges[E[2]]);
  EXPECT_EQ(1, components.edges[E[3]]);
  EXPECT_EQ(1, components.edges[E[4]]);
  EXPECT_EQ(1, components.edges[E[5]]);
}

TYPED_TEST(ConnectedComponentsTest, ConnectedComponentSubgraphs1)
{
  using Graph = TypeParam;
  auto g = ocgl::GraphStringParser<Graph>::parse("*.**(*)*.**");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  auto components = ocgl::algorithm::connectedComponents(g);

  std::vector<typename ocgl::Subgraph<Graph>::Type> subgraphs = ocgl::algorithm::connectedComponentsSubgraphs(g, components);

  ASSERT_EQ(3, subgraphs.size());

  // subgraph 0
  const typename ocgl::Subgraph<Graph>::Type &subg0 = subgraphs[0];
  ASSERT_EQ(1, ocgl::numVertices(subg0));
  ASSERT_EQ(0, ocgl::numEdges(subg0));

  EXPECT_EQ(V[0], ocgl::getVertex(subg0, 0));

  // subgraph 1
  const typename ocgl::Subgraph<Graph>::Type &subg1 = subgraphs[1];
  ASSERT_EQ(4, ocgl::numVertices(subg1));
  ASSERT_EQ(3, ocgl::numEdges(subg1));

  EXPECT_EQ(V[1], ocgl::getVertex(subg1, 0));
  EXPECT_EQ(V[2], ocgl::getVertex(subg1, 1));
  EXPECT_EQ(V[3], ocgl::getVertex(subg1, 2));
  EXPECT_EQ(V[4], ocgl::getVertex(subg1, 3));

  EXPECT_EQ(E[0], ocgl::getEdge(subg1, 0));
  EXPECT_EQ(E[1], ocgl::getEdge(subg1, 1));
  EXPECT_EQ(E[2], ocgl::getEdge(subg1, 2));

  // subgraph 2
  const typename ocgl::Subgraph<Graph>::Type &subg2 = subgraphs[2];
  ASSERT_EQ(2, ocgl::numVertices(subg2));
  ASSERT_EQ(1, ocgl::numEdges(subg2));

  EXPECT_EQ(V[5], ocgl::getVertex(subg2, 0));
  EXPECT_EQ(V[6], ocgl::getVertex(subg2, 1));

  EXPECT_EQ(E[3], ocgl::getEdge(subg2, 0));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

