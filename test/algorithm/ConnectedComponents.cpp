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

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

