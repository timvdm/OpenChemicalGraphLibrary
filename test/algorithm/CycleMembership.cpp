#include <ocgl/algorithm/CycleMembership.h>

#include "../test.h"

GRAPH_TYPED_TEST(CycleMembershipTest);

TYPED_TEST(CycleMembershipTest, CycleMembership1)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("***");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  auto isCyclic = ocgl::algorithm::cycleMembership(g);

  EXPECT_EQ(0, isCyclic.vertices[V[0]]);
  EXPECT_EQ(0, isCyclic.vertices[V[1]]);
  EXPECT_EQ(0, isCyclic.vertices[V[2]]);

  EXPECT_EQ(0, isCyclic.edges[E[0]]);
  EXPECT_EQ(0, isCyclic.edges[E[1]]);
}

TYPED_TEST(CycleMembershipTest, CycleMembership2)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*1**1");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  auto isCyclic = ocgl::algorithm::cycleMembership(g);

  EXPECT_EQ(1, isCyclic.vertices[V[0]]);
  EXPECT_EQ(1, isCyclic.vertices[V[1]]);
  EXPECT_EQ(1, isCyclic.vertices[V[2]]);

  EXPECT_EQ(1, isCyclic.edges[E[0]]);
  EXPECT_EQ(1, isCyclic.edges[E[1]]);
  EXPECT_EQ(1, isCyclic.edges[E[2]]);
}

TYPED_TEST(CycleMembershipTest, CycleMembership3)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*1**1*2**2");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  auto isCyclic = ocgl::algorithm::cycleMembership(g);

  EXPECT_EQ(1, isCyclic.vertices[V[0]]);
  EXPECT_EQ(1, isCyclic.vertices[V[1]]);
  EXPECT_EQ(1, isCyclic.vertices[V[2]]);
  EXPECT_EQ(1, isCyclic.vertices[V[3]]);
  EXPECT_EQ(1, isCyclic.vertices[V[4]]);
  EXPECT_EQ(1, isCyclic.vertices[V[5]]);

  EXPECT_EQ(1, isCyclic.edges[E[0]]);
  EXPECT_EQ(1, isCyclic.edges[E[1]]);
  EXPECT_EQ(1, isCyclic.edges[E[2]]);
  EXPECT_EQ(0, isCyclic.edges[E[3]]);
  EXPECT_EQ(1, isCyclic.edges[E[4]]);
  EXPECT_EQ(1, isCyclic.edges[E[5]]);
  EXPECT_EQ(1, isCyclic.edges[E[6]]);
}

TYPED_TEST(CycleMembershipTest, CycleMembership4)
{
  //         3
  //         |
  // 0---1---2---4---5
  //     |       |
  //     +-------+
  auto g = ocgl::GraphStringParser<TypeParam>::parse("**1*(*)*1*");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  auto isCyclic = ocgl::algorithm::cycleMembership(g);

  EXPECT_EQ(0, isCyclic.vertices[V[0]]);
  EXPECT_EQ(1, isCyclic.vertices[V[1]]);
  EXPECT_EQ(1, isCyclic.vertices[V[2]]);
  EXPECT_EQ(0, isCyclic.vertices[V[3]]);
  EXPECT_EQ(1, isCyclic.vertices[V[4]]);
  EXPECT_EQ(0, isCyclic.vertices[V[5]]);

  EXPECT_EQ(0, isCyclic.edges[E[0]]);
  EXPECT_EQ(1, isCyclic.edges[E[1]]);
  EXPECT_EQ(0, isCyclic.edges[E[2]]);
  EXPECT_EQ(1, isCyclic.edges[E[3]]);
  EXPECT_EQ(1, isCyclic.edges[E[4]]);
  EXPECT_EQ(0, isCyclic.edges[E[5]]);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
