#include <ocgl/Predicates.h>
#include <ocgl/algorithm/CycleMembership.h>

#include "../test.h"

GRAPH_TYPED_TEST(HasPropertyTest);

TYPED_TEST(HasPropertyTest, HasProperty)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*****");
  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  auto v1 = V[0]; auto v2 = V[1]; auto v3 = V[2]; auto v4 = V[3]; auto v5 = V[4];
  auto e1 = E[0]; auto e2 = E[1]; auto e3 = E[2]; auto e4 = E[3];

  ocgl::VertexEdgePropertyMap<TypeParam, int> props(g);

  props.vertices[v1] = 1;
  props.vertices[v2] = 2;
  props.vertices[v3] = 2;
  props.vertices[v4] = 3;
  props.vertices[v5] = 4;

  props.edges[e1] = 8;
  props.edges[e2] = 7;
  props.edges[e3] = 6;
  props.edges[e4] = 5;

  // EQ
  auto equal_to_2 = ocgl::HasPropertyEQ(props.vertices, 2);
  auto equal_to_6 = ocgl::HasPropertyEQ(props.edges, 6);

  EXPECT_FALSE(equal_to_2(g, v1));
  EXPECT_TRUE(equal_to_2(g, v2));
  EXPECT_TRUE(equal_to_2(g, v3));
  EXPECT_FALSE(equal_to_2(g, v4));
  EXPECT_FALSE(equal_to_2(g, v5));

  EXPECT_FALSE(equal_to_6(g, e1));
  EXPECT_FALSE(equal_to_6(g, e2));
  EXPECT_TRUE(equal_to_6(g, e3));
  EXPECT_FALSE(equal_to_6(g, e4));

  // NE
  auto not_equal_to_2 = ocgl::HasPropertyNE(props.vertices, 2);
  auto not_equal_to_6 = ocgl::HasPropertyNE(props.edges, 6);

  EXPECT_TRUE(not_equal_to_2(g, v1));
  EXPECT_FALSE(not_equal_to_2(g, v2));
  EXPECT_FALSE(not_equal_to_2(g, v3));
  EXPECT_TRUE(not_equal_to_2(g, v4));
  EXPECT_TRUE(not_equal_to_2(g, v5));

  EXPECT_TRUE(not_equal_to_6(g, e1));
  EXPECT_TRUE(not_equal_to_6(g, e2));
  EXPECT_FALSE(not_equal_to_6(g, e3));
  EXPECT_TRUE(not_equal_to_6(g, e4));

  // LT
  auto less_3 = ocgl::HasPropertyLT(props.vertices, 3);
  auto less_7 = ocgl::HasPropertyLT(props.edges, 7);

  EXPECT_TRUE(less_3(g, v1));
  EXPECT_TRUE(less_3(g, v2));
  EXPECT_TRUE(less_3(g, v3));
  EXPECT_FALSE(less_3(g, v4));
  EXPECT_FALSE(less_3(g, v5));

  EXPECT_FALSE(less_7(g, e1));
  EXPECT_FALSE(less_7(g, e2));
  EXPECT_TRUE(less_7(g, e3));
  EXPECT_TRUE(less_7(g, e4));

  // GT
  auto greater_3 = ocgl::HasPropertyGT(props.vertices, 3);
  auto greater_7 = ocgl::HasPropertyGT(props.edges, 7);

  EXPECT_FALSE(greater_3(g, v1));
  EXPECT_FALSE(greater_3(g, v2));
  EXPECT_FALSE(greater_3(g, v3));
  EXPECT_FALSE(greater_3(g, v4));
  EXPECT_TRUE(greater_3(g, v5));

  EXPECT_TRUE(greater_7(g, e1));
  EXPECT_FALSE(greater_7(g, e2));
  EXPECT_FALSE(greater_7(g, e3));
  EXPECT_FALSE(greater_7(g, e4));

  // LE
  auto less_equal_3 = ocgl::HasPropertyLE(props.vertices, 3);
  auto less_equal_7 = ocgl::HasPropertyLE(props.edges, 7);

  EXPECT_TRUE(less_equal_3(g, v1));
  EXPECT_TRUE(less_equal_3(g, v2));
  EXPECT_TRUE(less_equal_3(g, v3));
  EXPECT_TRUE(less_equal_3(g, v4));
  EXPECT_FALSE(less_equal_3(g, v5));

  EXPECT_FALSE(less_equal_7(g, e1));
  EXPECT_TRUE(less_equal_7(g, e2));
  EXPECT_TRUE(less_equal_7(g, e3));
  EXPECT_TRUE(less_equal_7(g, e4));

  // GT
  auto greater_equal_3 = ocgl::HasPropertyGE(props.vertices, 3);
  auto greater_equal_7 = ocgl::HasPropertyGE(props.edges, 7);

  EXPECT_FALSE(greater_equal_3(g, v1));
  EXPECT_FALSE(greater_equal_3(g, v2));
  EXPECT_FALSE(greater_equal_3(g, v3));
  EXPECT_TRUE(greater_equal_3(g, v4));
  EXPECT_TRUE(greater_equal_3(g, v5));

  EXPECT_TRUE(greater_equal_7(g, e1));
  EXPECT_TRUE(greater_equal_7(g, e2));
  EXPECT_FALSE(greater_equal_7(g, e3));
  EXPECT_FALSE(greater_equal_7(g, e4));
}

template<typename Graph>
void testIsCyclic(const std::string &input)
{
  std::cout << "testIsCyclic(" << input << ")" << std::endl;

  auto g = ocgl::GraphStringParser<Graph>::parse(input);

  auto cycleMembership = ocgl::algorithm::cycleMembership(g);

  auto isCyclicVertex = ocgl::IsCyclic(cycleMembership.vertices);
  auto isAcyclicVertex = ocgl::IsAcyclic(cycleMembership.vertices);

  for (auto v : ocgl::getVertices(g)) {
    if (cycleMembership.vertices[v]) {
      EXPECT_TRUE(isCyclicVertex(g, v));
      EXPECT_FALSE(isAcyclicVertex(g, v));
    } else {
      EXPECT_FALSE(isCyclicVertex(g, v));
      EXPECT_TRUE(isAcyclicVertex(g, v));
    }
  }

  auto isCyclicEdge = ocgl::IsCyclic(cycleMembership.edges);
  auto isAcyclicEdge = ocgl::IsAcyclic(cycleMembership.edges);

  for (auto e : ocgl::getEdges(g)) {
    if (cycleMembership.edges[e]) {
      EXPECT_TRUE(isCyclicEdge(g, e));
      EXPECT_FALSE(isAcyclicEdge(g, e));
    } else {
      EXPECT_FALSE(isCyclicEdge(g, e));
      EXPECT_TRUE(isAcyclicEdge(g, e));
    }
  }
}

TYPED_TEST(HasPropertyTest, IsCyclic)
{
  testIsCyclic<TypeParam>("***");
  testIsCyclic<TypeParam>("*1**1");
  testIsCyclic<TypeParam>("*1**1***2***2");
  testIsCyclic<TypeParam>("**1*(*)*1*");
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
