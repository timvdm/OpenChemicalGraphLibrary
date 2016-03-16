#include <ocgl/GraphStringParser.h>
#include <ocgl/model/PointerGraph.h>
#include <ocgl/model/IdGraph.h>
#include <ocgl/model/ObjectGraph.h>

#include <gtest/gtest.h>

using GraphModels = ::testing::Types<
  ocgl::model::PointerGraph,
  ocgl::model::IdGraph,
  ocgl::model::ObjectGraph
>;

template<typename T> class GraphStringParserTest : public ::testing::Test {};

TYPED_TEST_CASE(GraphStringParserTest, GraphModels);

TYPED_TEST(GraphStringParserTest, SingleVertex)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*");
  EXPECT_EQ(1, ocgl::numVertices(g));
}

TYPED_TEST(GraphStringParserTest, SingleEdge)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("**");
  EXPECT_EQ(2, ocgl::numVertices(g));
  EXPECT_EQ(1, ocgl::numEdges(g));

  auto V = ocgl::getVertices(g).toVector();

  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[1]));
}

TYPED_TEST(GraphStringParserTest, SingleBranch)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("**(*)*");
  EXPECT_EQ(4, ocgl::numVertices(g));
  EXPECT_EQ(3, ocgl::numEdges(g));

  auto V = ocgl::getVertices(g).toVector();

  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[1]));
  EXPECT_TRUE(ocgl::isConnected(g, V[1], V[2]));
  EXPECT_TRUE(ocgl::isConnected(g, V[1], V[3]));
}

TYPED_TEST(GraphStringParserTest, SingleBackEdge)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*1**1");
  EXPECT_EQ(3, ocgl::numVertices(g));
  EXPECT_EQ(3, ocgl::numEdges(g));

  auto V = ocgl::getVertices(g).toVector();

  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[1]));
  EXPECT_TRUE(ocgl::isConnected(g, V[1], V[2]));
  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[2]));
}

TYPED_TEST(GraphStringParserTest, TwoBackEdges)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("*1**1*1**1");
  EXPECT_EQ(6, ocgl::numVertices(g));
  EXPECT_EQ(7, ocgl::numEdges(g));

  auto V = ocgl::getVertices(g).toVector();

  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[1]));
  EXPECT_TRUE(ocgl::isConnected(g, V[1], V[2]));
  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[2]));
  EXPECT_TRUE(ocgl::isConnected(g, V[2], V[3]));
  EXPECT_TRUE(ocgl::isConnected(g, V[3], V[4]));
  EXPECT_TRUE(ocgl::isConnected(g, V[4], V[5]));
  EXPECT_TRUE(ocgl::isConnected(g, V[5], V[3]));
}

TYPED_TEST(GraphStringParserTest, Components)
{
  auto g = ocgl::GraphStringParser<TypeParam>::parse("**.**.*");
  EXPECT_EQ(5, ocgl::numVertices(g));
  EXPECT_EQ(2, ocgl::numEdges(g));

  auto V = ocgl::getVertices(g).toVector();

  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[1]));
  EXPECT_TRUE(ocgl::isConnected(g, V[2], V[3]));
}

TYPED_TEST(GraphStringParserTest, Errors)
{
  // invalid character
  EXPECT_THROW(ocgl::GraphStringParser<TypeParam>::parse("x"), std::runtime_error);
  // unmatched ')'
  EXPECT_THROW(ocgl::GraphStringParser<TypeParam>::parse("*)*"), std::runtime_error);
  // unmatched '('
  EXPECT_THROW(ocgl::GraphStringParser<TypeParam>::parse("*(*"), std::runtime_error);
  EXPECT_THROW(ocgl::GraphStringParser<TypeParam>::parse("*(*.*)*"), std::runtime_error);
  // unmatched back edge
  EXPECT_THROW(ocgl::GraphStringParser<TypeParam>::parse("*1*"), std::runtime_error);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
