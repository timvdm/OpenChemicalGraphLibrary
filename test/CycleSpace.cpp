#include <ocgl/CycleSpace.h>

#include "test.h"

GRAPH_TYPED_TEST(CycleSpaceTest);

TYPED_TEST(CycleSpaceTest, CycleSpace1)
{
  using Graph = TypeParam;
  Graph g;

  //        e2
  //    v0 ---- v2
  //    |  \     |
  // e3 | e0 \   | e1
  //    |      \ |
  //    v3 ---- v1
  //        e4
  //

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);

  auto e0 = ocgl::addEdge(g, v0, v1);
  auto e1 = ocgl::addEdge(g, v1, v2);
  auto e2 = ocgl::addEdge(g, v2, v0);
  auto e3 = ocgl::addEdge(g, v0, v3);
  auto e4 = ocgl::addEdge(g, v3, v1);

  ocgl::EdgeCycle<Graph> c1({e0, e1, e2});
  ocgl::EdgeCycle<Graph> c2({e0, e3, e4});
  ocgl::EdgeCycle<Graph> c3({e1, e2, e3, e4});

  ocgl::CycleSpace<Graph> sp(g);

  EXPECT_FALSE(sp.contains(c1));
  EXPECT_FALSE(sp.contains(c2));
  EXPECT_FALSE(sp.contains(c3));
  EXPECT_FALSE(sp.isBasis());

  sp.add(c1);

  EXPECT_TRUE(sp.contains(c1));
  EXPECT_FALSE(sp.contains(c2));
  EXPECT_FALSE(sp.contains(c3));
  EXPECT_FALSE(sp.isBasis());

  sp.add(c2);

  EXPECT_TRUE(sp.contains(c1));
  EXPECT_TRUE(sp.contains(c2));
  EXPECT_TRUE(sp.contains(c3));
  EXPECT_TRUE(sp.isBasis());

}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
