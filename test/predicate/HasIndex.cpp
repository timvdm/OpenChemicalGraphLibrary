#include <ocgl/Predicates.h>

#include "../test.h"

GRAPH_TYPED_TEST(HasIndexTest);

TYPED_TEST(HasIndexTest, HasIndex)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*****");
  auto V = ocgl::getVertices(g).toVector();

  // HasVertexIndexEQ
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasVertexIndexEQ<TypeParam>(0)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasVertexIndexEQ<TypeParam>(1)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasVertexIndexEQ<TypeParam>(2)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasVertexIndexEQ<TypeParam>(3)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasVertexIndexEQ<TypeParam>(4)).size());

  EXPECT_EQ(1, ocgl::getAdjacent(g, V[1], ocgl::HasVertexIndexEQ<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getAdjacent(g, V[3], ocgl::HasVertexIndexEQ<TypeParam>(0)).size());

  // HasEdgeIndexEQ
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasEdgeIndexEQ<TypeParam>(0)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasEdgeIndexEQ<TypeParam>(1)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasEdgeIndexEQ<TypeParam>(2)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasEdgeIndexEQ<TypeParam>(3)).size());

  EXPECT_EQ(1, ocgl::getIncident(g, V[1], ocgl::HasEdgeIndexEQ<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getIncident(g, V[3], ocgl::HasEdgeIndexEQ<TypeParam>(0)).size());


  // HasVertexIndexNE
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasVertexIndexNE<TypeParam>(0)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasVertexIndexNE<TypeParam>(1)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasVertexIndexNE<TypeParam>(2)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasVertexIndexNE<TypeParam>(3)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasVertexIndexNE<TypeParam>(4)).size());

  EXPECT_EQ(1, ocgl::getAdjacent(g, V[1], ocgl::HasVertexIndexNE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getAdjacent(g, V[3], ocgl::HasVertexIndexNE<TypeParam>(0)).size());

  // HasEdgeIndexNE
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasEdgeIndexNE<TypeParam>(0)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasEdgeIndexNE<TypeParam>(1)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasEdgeIndexNE<TypeParam>(2)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasEdgeIndexNE<TypeParam>(3)).size());

  EXPECT_EQ(1, ocgl::getIncident(g, V[1], ocgl::HasEdgeIndexNE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getIncident(g, V[3], ocgl::HasEdgeIndexNE<TypeParam>(0)).size());


  // HasVertexIndexLT
  EXPECT_EQ(0, ocgl::getVertices(g, ocgl::HasVertexIndexLT<TypeParam>(0)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasVertexIndexLT<TypeParam>(1)).size());
  EXPECT_EQ(2, ocgl::getVertices(g, ocgl::HasVertexIndexLT<TypeParam>(2)).size());
  EXPECT_EQ(3, ocgl::getVertices(g, ocgl::HasVertexIndexLT<TypeParam>(3)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasVertexIndexLT<TypeParam>(4)).size());

  EXPECT_EQ(0, ocgl::getAdjacent(g, V[1], ocgl::HasVertexIndexLT<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getAdjacent(g, V[3], ocgl::HasVertexIndexLT<TypeParam>(0)).size());

  // HasEdgeIndexLT
  EXPECT_EQ(0, ocgl::getEdges(g, ocgl::HasEdgeIndexLT<TypeParam>(0)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasEdgeIndexLT<TypeParam>(1)).size());
  EXPECT_EQ(2, ocgl::getEdges(g, ocgl::HasEdgeIndexLT<TypeParam>(2)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasEdgeIndexLT<TypeParam>(3)).size());

  EXPECT_EQ(0, ocgl::getIncident(g, V[1], ocgl::HasEdgeIndexLT<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getIncident(g, V[3], ocgl::HasEdgeIndexLT<TypeParam>(0)).size());

  // HasVertexIndexGT
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasVertexIndexGT<TypeParam>(0)).size());
  EXPECT_EQ(3, ocgl::getVertices(g, ocgl::HasVertexIndexGT<TypeParam>(1)).size());
  EXPECT_EQ(2, ocgl::getVertices(g, ocgl::HasVertexIndexGT<TypeParam>(2)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasVertexIndexGT<TypeParam>(3)).size());
  EXPECT_EQ(0, ocgl::getVertices(g, ocgl::HasVertexIndexGT<TypeParam>(4)).size());

  EXPECT_EQ(1, ocgl::getAdjacent(g, V[1], ocgl::HasVertexIndexGT<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getAdjacent(g, V[3], ocgl::HasVertexIndexGT<TypeParam>(0)).size());

  // HasEdgeIndexGT
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasEdgeIndexGT<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getEdges(g, ocgl::HasEdgeIndexGT<TypeParam>(1)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasEdgeIndexGT<TypeParam>(2)).size());
  EXPECT_EQ(0, ocgl::getEdges(g, ocgl::HasEdgeIndexGT<TypeParam>(3)).size());

  EXPECT_EQ(1, ocgl::getIncident(g, V[1], ocgl::HasEdgeIndexGT<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getIncident(g, V[3], ocgl::HasEdgeIndexGT<TypeParam>(0)).size());

  // HasVertexIndexLE
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasVertexIndexLE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getVertices(g, ocgl::HasVertexIndexLE<TypeParam>(1)).size());
  EXPECT_EQ(3, ocgl::getVertices(g, ocgl::HasVertexIndexLE<TypeParam>(2)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasVertexIndexLE<TypeParam>(3)).size());
  EXPECT_EQ(5, ocgl::getVertices(g, ocgl::HasVertexIndexLE<TypeParam>(4)).size());

  EXPECT_EQ(1, ocgl::getAdjacent(g, V[1], ocgl::HasVertexIndexLE<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getAdjacent(g, V[3], ocgl::HasVertexIndexLE<TypeParam>(0)).size());

  // HasEdgeIndexLE
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasEdgeIndexLE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getEdges(g, ocgl::HasEdgeIndexLE<TypeParam>(1)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasEdgeIndexLE<TypeParam>(2)).size());
  EXPECT_EQ(4, ocgl::getEdges(g, ocgl::HasEdgeIndexLE<TypeParam>(3)).size());

  EXPECT_EQ(1, ocgl::getIncident(g, V[1], ocgl::HasEdgeIndexLE<TypeParam>(0)).size());
  EXPECT_EQ(0, ocgl::getIncident(g, V[3], ocgl::HasEdgeIndexLE<TypeParam>(0)).size());

  // HasVertexIndexGE
  EXPECT_EQ(5, ocgl::getVertices(g, ocgl::HasVertexIndexGE<TypeParam>(0)).size());
  EXPECT_EQ(4, ocgl::getVertices(g, ocgl::HasVertexIndexGE<TypeParam>(1)).size());
  EXPECT_EQ(3, ocgl::getVertices(g, ocgl::HasVertexIndexGE<TypeParam>(2)).size());
  EXPECT_EQ(2, ocgl::getVertices(g, ocgl::HasVertexIndexGE<TypeParam>(3)).size());
  EXPECT_EQ(1, ocgl::getVertices(g, ocgl::HasVertexIndexGE<TypeParam>(4)).size());

  EXPECT_EQ(2, ocgl::getAdjacent(g, V[1], ocgl::HasVertexIndexGE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getAdjacent(g, V[3], ocgl::HasVertexIndexGE<TypeParam>(0)).size());

  // HasEdgeIndexGE
  EXPECT_EQ(4, ocgl::getEdges(g, ocgl::HasEdgeIndexGE<TypeParam>(0)).size());
  EXPECT_EQ(3, ocgl::getEdges(g, ocgl::HasEdgeIndexGE<TypeParam>(1)).size());
  EXPECT_EQ(2, ocgl::getEdges(g, ocgl::HasEdgeIndexGE<TypeParam>(2)).size());
  EXPECT_EQ(1, ocgl::getEdges(g, ocgl::HasEdgeIndexGE<TypeParam>(3)).size());

  EXPECT_EQ(2, ocgl::getIncident(g, V[1], ocgl::HasEdgeIndexGE<TypeParam>(0)).size());
  EXPECT_EQ(2, ocgl::getIncident(g, V[3], ocgl::HasEdgeIndexGE<TypeParam>(0)).size());
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
