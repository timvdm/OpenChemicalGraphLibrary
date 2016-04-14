#include <ocgl/algorithm/ExtendedConnectivities.h>

#include "../test.h"

GRAPH_TYPED_TEST(ExtendedConnectivitiesTest);

TYPED_TEST(ExtendedConnectivitiesTest, EC1)
{
  using Graph = TypeParam;
  using Vertex = typename ocgl::GraphTraits<Graph>::Vertex;

  //  2                 0
  //   \                 \
  //    1 -- 3    =>      1 -- 0
  //   /                 /
  //  0                 0
  auto g = ocgl::GraphStringParser<Graph>::parse("**(*)*");

  auto ec = ocgl::algorithm::extendedConnectivities(g, [&g] (const Vertex &v) -> unsigned long { return ocgl::getDegree(g, v); });

  ASSERT_EQ(4, ec.map().size());
  EXPECT_EQ(0, ec[0]);
  EXPECT_EQ(1, ec[1]);
  EXPECT_EQ(0, ec[2]);
  EXPECT_EQ(0, ec[3]);
}

TYPED_TEST(ExtendedConnectivitiesTest, EC2)
{
  using Graph = TypeParam;
  using Vertex = typename ocgl::GraphTraits<Graph>::Vertex;

  //  2        4          1        0
  //   \      /            \      /
  //    1 -- 3      =>      3 -- 2
  //   /                   /
  //  0                   1
  auto g = ocgl::GraphStringParser<Graph>::parse("**(*)**");

  auto ec = ocgl::algorithm::extendedConnectivities(g, [&g] (const Vertex &v) -> unsigned long { return ocgl::getDegree(g, v); });

  ASSERT_EQ(5, ec.map().size());
  EXPECT_EQ(1, ec[0]);
  EXPECT_EQ(3, ec[1]);
  EXPECT_EQ(1, ec[2]);
  EXPECT_EQ(2, ec[3]);
  EXPECT_EQ(0, ec[4]);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
