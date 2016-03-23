#include <ocgl/Predicates.h>

#include "../test.h"

GRAPH_TYPED_TEST(HasIndexTest);

TYPED_TEST(HasIndexTest, HasIndex)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*****");
  auto V = ocgl::getVertices(g).toVector();

  // HasIndexEQ
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasIndexEQ<TypeParam>(0)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasIndexEQ<TypeParam>(1)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasIndexEQ<TypeParam>(2)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasIndexEQ<TypeParam>(3)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasIndexEQ<TypeParam>(4)).size());

  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasIndexEQ<TypeParam>(0)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasIndexEQ<TypeParam>(1)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasIndexEQ<TypeParam>(2)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasIndexEQ<TypeParam>(3)).size());

  EXPECT_EQ(1, ocgl::getIncident(g, V[1], ocgl::HasIndexEQ<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getIncident(g, V[3], ocgl::HasIndexEQ<TypeParam>(0)).size());

  EXPECT_EQ(1, ocgl::getAdjacent(g, V[1], ocgl::HasIndexEQ<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getAdjacent(g, V[3], ocgl::HasIndexEQ<TypeParam>(0)).size());

  // HasIndexNE
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasIndexNE<TypeParam>(0)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasIndexNE<TypeParam>(1)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasIndexNE<TypeParam>(2)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasIndexNE<TypeParam>(3)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasIndexNE<TypeParam>(4)).size());

  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasIndexNE<TypeParam>(0)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasIndexNE<TypeParam>(1)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasIndexNE<TypeParam>(2)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasIndexNE<TypeParam>(3)).size());

  EXPECT_EQ(1, ocgl::getIncident(g, V[1], ocgl::HasIndexNE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getIncident(g, V[3], ocgl::HasIndexNE<TypeParam>(0)).size());

  EXPECT_EQ(1, ocgl::getAdjacent(g, V[1], ocgl::HasIndexNE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getAdjacent(g, V[3], ocgl::HasIndexNE<TypeParam>(0)).size());

  // HasIndexLT
  EXPECT_EQ(0, ocgl::getVertices(g, ocgl::HasIndexLT<TypeParam>(0)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasIndexLT<TypeParam>(1)).size());
  EXPECT_EQ(2, ocgl::getVertices(g, ocgl::HasIndexLT<TypeParam>(2)).size());
  EXPECT_EQ(3, ocgl::getVertices(g, ocgl::HasIndexLT<TypeParam>(3)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasIndexLT<TypeParam>(4)).size());

  EXPECT_EQ(0, ocgl::getEdges(g, ocgl::HasIndexLT<TypeParam>(0)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasIndexLT<TypeParam>(1)).size());
  EXPECT_EQ(2, ocgl::getEdges(g, ocgl::HasIndexLT<TypeParam>(2)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasIndexLT<TypeParam>(3)).size());

  EXPECT_EQ(0, ocgl::getIncident(g, V[1], ocgl::HasIndexLT<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getIncident(g, V[3], ocgl::HasIndexLT<TypeParam>(0)).size());

  EXPECT_EQ(0, ocgl::getAdjacent(g, V[1], ocgl::HasIndexLT<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getAdjacent(g, V[3], ocgl::HasIndexLT<TypeParam>(0)).size());

  // HasIndexGT
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasIndexGT<TypeParam>(0)).size());
  EXPECT_EQ(3, ocgl::getVertices(g, ocgl::HasIndexGT<TypeParam>(1)).size());
  EXPECT_EQ(2, ocgl::getVertices(g, ocgl::HasIndexGT<TypeParam>(2)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasIndexGT<TypeParam>(3)).size());
  EXPECT_EQ(0, ocgl::getVertices(g, ocgl::HasIndexGT<TypeParam>(4)).size());

  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasIndexGT<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getEdges(g, ocgl::HasIndexGT<TypeParam>(1)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasIndexGT<TypeParam>(2)).size());
  EXPECT_EQ(0, ocgl::getEdges(g, ocgl::HasIndexGT<TypeParam>(3)).size());

  EXPECT_EQ(1, ocgl::getIncident(g, V[1], ocgl::HasIndexGT<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getIncident(g, V[3], ocgl::HasIndexGT<TypeParam>(0)).size());

  EXPECT_EQ(1, ocgl::getAdjacent(g, V[1], ocgl::HasIndexGT<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getAdjacent(g, V[3], ocgl::HasIndexGT<TypeParam>(0)).size());

  // HasIndexLE
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasIndexLE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getVertices(g, ocgl::HasIndexLE<TypeParam>(1)).size());
  EXPECT_EQ(3, ocgl::getVertices(g, ocgl::HasIndexLE<TypeParam>(2)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasIndexLE<TypeParam>(3)).size());
  EXPECT_EQ(5, ocgl::getVertices(g, ocgl::HasIndexLE<TypeParam>(4)).size());

  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasIndexLE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getEdges(g, ocgl::HasIndexLE<TypeParam>(1)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasIndexLE<TypeParam>(2)).size());
  EXPECT_EQ(4, ocgl::getEdges(g, ocgl::HasIndexLE<TypeParam>(3)).size());

  EXPECT_EQ(1, ocgl::getIncident(g, V[1], ocgl::HasIndexLE<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getIncident(g, V[3], ocgl::HasIndexLE<TypeParam>(0)).size());

  EXPECT_EQ(1, ocgl::getAdjacent(g, V[1], ocgl::HasIndexLE<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getAdjacent(g, V[3], ocgl::HasIndexLE<TypeParam>(0)).size());

  // HasIndexGE
  EXPECT_EQ(5, ocgl::getVertices(g, ocgl::HasIndexGE<TypeParam>(0)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasIndexGE<TypeParam>(1)).size());
  EXPECT_EQ(3, ocgl::getVertices(g, ocgl::HasIndexGE<TypeParam>(2)).size());
  EXPECT_EQ(2, ocgl::getVertices(g, ocgl::HasIndexGE<TypeParam>(3)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasIndexGE<TypeParam>(4)).size());

  EXPECT_EQ(4, ocgl::getEdges(g, ocgl::HasIndexGE<TypeParam>(0)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasIndexGE<TypeParam>(1)).size());
  EXPECT_EQ(2, ocgl::getEdges(g, ocgl::HasIndexGE<TypeParam>(2)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasIndexGE<TypeParam>(3)).size());

  EXPECT_EQ(2, ocgl::getIncident(g, V[1], ocgl::HasIndexGE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getIncident(g, V[3], ocgl::HasIndexGE<TypeParam>(0)).size());

  EXPECT_EQ(2, ocgl::getAdjacent(g, V[1], ocgl::HasIndexGE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getAdjacent(g, V[3], ocgl::HasIndexGE<TypeParam>(0)).size());
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
