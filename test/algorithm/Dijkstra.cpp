#include <ocgl/algorithm/Dijkstra.h>

#include "../test.h"

GRAPH_TYPED_TEST(DijkstraTest);

TYPED_TEST(DijkstraTest, Dijkstra)
{
  using Graph = TypeParam;
  using Vertex = typename ocgl::GraphTraits<Graph>::Vertex;

  auto g = ocgl::GraphStringParser<Graph>::parse("*1****2*1***2");
  auto V = ocgl::getVertices(g).toVector();

  ocgl::algorithm::Dijkstra<Graph> d(g, V[0]);

  EXPECT_EQ(0, d.distance(V[0]));
  EXPECT_EQ(1, d.distance(V[1]));
  EXPECT_EQ(2, d.distance(V[2]));
  EXPECT_EQ(3, d.distance(V[3]));
  EXPECT_EQ(2, d.distance(V[4]));
  EXPECT_EQ(1, d.distance(V[5]));
  EXPECT_EQ(2, d.distance(V[6]));
  EXPECT_EQ(3, d.distance(V[7]));
  EXPECT_EQ(3, d.distance(V[8]));

  std::vector<Vertex> path;

  path = d.path(V[0]);
  EXPECT_EQ(1, path.size());
  EXPECT_EQ(V[0], path[0]);

  path = d.path(V[1]);
  EXPECT_EQ(2, path.size());
  EXPECT_EQ(V[0], path[0]);
  EXPECT_EQ(V[1], path[1]);

  path = d.path(V[2]);
  EXPECT_EQ(3, path.size());
  EXPECT_EQ(V[0], path[0]);
  EXPECT_EQ(V[1], path[1]);
  EXPECT_EQ(V[2], path[2]);

  path = d.path(V[3]);
  EXPECT_EQ(4, path.size());
  EXPECT_EQ(V[0], path[0]);
  EXPECT_EQ(V[1], path[1]);
  EXPECT_EQ(V[2], path[2]);
  EXPECT_EQ(V[3], path[3]);

  path = d.path(V[4]);
  EXPECT_EQ(3, path.size());
  EXPECT_EQ(V[0], path[0]);
  EXPECT_EQ(V[5], path[1]);
  EXPECT_EQ(V[4], path[2]);

  path = d.path(V[5]);
  EXPECT_EQ(2, path.size());
  EXPECT_EQ(V[0], path[0]);
  EXPECT_EQ(V[5], path[1]);

  path = d.path(V[6]);
  EXPECT_EQ(3, path.size());
  EXPECT_EQ(V[0], path[0]);
  EXPECT_EQ(V[5], path[1]);
  EXPECT_EQ(V[6], path[2]);

  path = d.path(V[7]);
  EXPECT_EQ(4, path.size());
  EXPECT_EQ(V[0], path[0]);
  EXPECT_EQ(V[5], path[1]);
  EXPECT_EQ(V[6], path[2]);
  EXPECT_EQ(V[7], path[3]);

  path = d.path(V[8]);
  EXPECT_EQ(4, path.size());
  EXPECT_EQ(V[0], path[0]);
  EXPECT_EQ(V[5], path[1]);
  EXPECT_EQ(V[4], path[2]);
  EXPECT_EQ(V[8], path[3]);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

