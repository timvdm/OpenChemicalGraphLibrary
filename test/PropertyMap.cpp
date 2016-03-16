#include <ocgl/PropertyMap.h>
#include <ocgl/model/PointerGraph.h>

#include <gtest/gtest.h>

TEST(PropertyMapTest, VertexPropertyMap)
{
  using Graph = ocgl::model::PointerGraph;
  using Vertex = typename ocgl::GraphTraits<Graph>::Vertex;

  Graph g;

  std::vector<Vertex> v;
  for (int i = 0; i < 5; ++i) {
    v.push_back(ocgl::addVertex(g));
    auto w = ocgl::addVertex(g);
    ocgl::removeVertex(g, w);
  }

  ocgl::VertexPropertyMap<Graph, int> pmap(g);

  pmap[v[0]] = 1;
  pmap[v[1]] = 3;
  pmap[v[2]] = 5;
  pmap[v[3]] = 7;
  pmap[v[4]] = 11;

  EXPECT_EQ(1, pmap[v[0]]);
  EXPECT_EQ(3, pmap[v[1]]);
  EXPECT_EQ(5, pmap[v[2]]);
  EXPECT_EQ(7, pmap[v[3]]);
  EXPECT_EQ(11, pmap[v[4]]);
}

TEST(PropertyMapTest, EdgePropertyMap)
{
  using Graph = ocgl::model::PointerGraph;

  Graph g;

  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);
  auto v4 = ocgl::addVertex(g);
  auto v5 = ocgl::addVertex(g);
  auto v6 = ocgl::addVertex(g);

  auto e1 = ocgl::addEdge(g, v1, v2);
  ocgl::removeEdge(g, ocgl::addEdge(g, v1, v6));
  auto e2 = ocgl::addEdge(g, v2, v3);
  ocgl::removeEdge(g, ocgl::addEdge(g, v1, v6));
  auto e3 = ocgl::addEdge(g, v3, v4);
  ocgl::removeEdge(g, ocgl::addEdge(g, v1, v6));
  auto e4 = ocgl::addEdge(g, v4, v5);
  ocgl::removeEdge(g, ocgl::addEdge(g, v1, v6));
  auto e5 = ocgl::addEdge(g, v5, v6);

  ocgl::EdgePropertyMap<Graph, double> pmap(g);

  pmap[e1] = 1.0;
  pmap[e2] = 1.5;
  pmap[e3] = 2.0;
  pmap[e4] = 2.5;
  pmap[e5] = 3.0;

  EXPECT_EQ(1.0, pmap[e1]);
  EXPECT_EQ(1.5, pmap[e2]);
  EXPECT_EQ(2.0, pmap[e3]);
  EXPECT_EQ(2.5, pmap[e4]);
  EXPECT_EQ(3.0, pmap[e5]);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

