#include <ocgl/Cycle.h>

#include "test.h"

GRAPH_TYPED_TEST(CycleTest);

TYPED_TEST(CycleTest, VertexCycleDefaultConstructor)
{
  using Graph = TypeParam;
  ocgl::VertexCycle<Graph> cycle;
  EXPECT_EQ(0, cycle.size());
}

TYPED_TEST(CycleTest, VertexCycleVertexListCopyConstructor)
{
  using Graph = TypeParam;
  Graph g;

  ocgl::VertexList<Graph> vertices;
  vertices.push_back(ocgl::addVertex(g));
  vertices.push_back(ocgl::addVertex(g));
  vertices.push_back(ocgl::addVertex(g));

  ocgl::addEdge(g, vertices[0], vertices[1]);
  ocgl::addEdge(g, vertices[1], vertices[2]);
  ocgl::addEdge(g, vertices[2], vertices[0]);

  ocgl::VertexCycle<Graph> cycle(vertices);
  ASSERT_EQ(3, cycle.size());
  EXPECT_EQ(vertices[0], cycle[0]);
  EXPECT_EQ(vertices[1], cycle[1]);
  EXPECT_EQ(vertices[2], cycle[2]);
}

TYPED_TEST(CycleTest, VertexCycleVertexListMoveConstructor)
{
  using Graph = TypeParam;
  Graph g;

  ocgl::VertexList<Graph> vertices;
  vertices.push_back(ocgl::addVertex(g));
  vertices.push_back(ocgl::addVertex(g));
  vertices.push_back(ocgl::addVertex(g));

  ocgl::addEdge(g, vertices[0], vertices[1]);
  ocgl::addEdge(g, vertices[1], vertices[2]);
  ocgl::addEdge(g, vertices[2], vertices[0]);

  // copy vertices
  ocgl::VertexList<Graph> verticesCopy(vertices);

  ocgl::VertexCycle<Graph> cycle(std::move(verticesCopy));
  ASSERT_EQ(3, cycle.size());
  EXPECT_EQ(vertices[0], cycle[0]);
  EXPECT_EQ(vertices[1], cycle[1]);
  EXPECT_EQ(vertices[2], cycle[2]);
}

TYPED_TEST(CycleTest, VertexCycleToEdgeCycle)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);

  auto e0 = ocgl::addEdge(g, v0, v1);
  auto e1 = ocgl::addEdge(g, v1, v2);
  auto e2 = ocgl::addEdge(g, v2, v0);

  // from 0 vertices
  ocgl::VertexCycle<Graph> vertices1;
  ocgl::EdgeCycle<Graph> edges1 = ocgl::vertexCycleToEdgeCycle(g, vertices1);
  EXPECT_EQ(0, edges1.size());

  // from 1 vertices
  ocgl::VertexCycle<Graph> vertices2{v0};
  ocgl::EdgeCycle<Graph> edges2 = ocgl::vertexCycleToEdgeCycle(g, vertices2);
  EXPECT_EQ(0, edges2.size());

  // from 2 vertices
  ocgl::VertexCycle<Graph> vertices3{v0, v1};
  ocgl::EdgeCycle<Graph> edges3 = ocgl::vertexCycleToEdgeCycle(g, vertices3);
  EXPECT_EQ(0, edges3.size());

  // from 3 vertices : [ v0 v1 v2 ]
  ocgl::VertexCycle<Graph> vertices4{v0, v1, v2};
  ocgl::EdgeCycle<Graph> edges4 = ocgl::vertexCycleToEdgeCycle(g, vertices4);
  ASSERT_EQ(3, edges4.size());
  EXPECT_EQ(e0, edges4[0]);
  EXPECT_EQ(e1, edges4[1]);
  EXPECT_EQ(e2, edges4[2]);

  // from 3 vertices : [ v2 v0 v1 ]
  ocgl::VertexCycle<Graph> vertices5{v2, v0, v1};
  ocgl::EdgeCycle<Graph> edges5 = ocgl::vertexCycleToEdgeCycle(g, vertices5);
  ASSERT_EQ(3, edges5.size());
  EXPECT_EQ(e2, edges5[0]);
  EXPECT_EQ(e0, edges5[1]);
  EXPECT_EQ(e1, edges5[2]);

}

TYPED_TEST(CycleTest, EdgeCycleDefaultConstructor)
{
  using Graph = TypeParam;
  ocgl::EdgeCycle<Graph> cycle;
  EXPECT_EQ(0, cycle.size());
}

TYPED_TEST(CycleTest, EdgeCycleEdgeListCopyConstructor)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);

  ocgl::EdgeList<Graph> edges;
  edges.push_back(ocgl::addEdge(g, v0, v1));
  edges.push_back(ocgl::addEdge(g, v1, v2));
  edges.push_back(ocgl::addEdge(g, v2, v0));

  ocgl::EdgeCycle<Graph> cycle(edges);
  ASSERT_EQ(3, cycle.size());
  EXPECT_EQ(edges[0], cycle[0]);
  EXPECT_EQ(edges[1], cycle[1]);
  EXPECT_EQ(edges[2], cycle[2]);
}

TYPED_TEST(CycleTest, EdgeCycleEdgeListMoveConstructor)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);

  ocgl::EdgeList<Graph> edges;
  edges.push_back(ocgl::addEdge(g, v0, v1));
  edges.push_back(ocgl::addEdge(g, v1, v2));
  edges.push_back(ocgl::addEdge(g, v2, v0));

  // copy edges
  ocgl::EdgeList<Graph> edgesCopy(edges);

  ocgl::EdgeCycle<Graph> cycle(std::move(edgesCopy));
  ASSERT_EQ(3, cycle.size());
  EXPECT_EQ(edges[0], cycle[0]);
  EXPECT_EQ(edges[1], cycle[1]);
  EXPECT_EQ(edges[2], cycle[2]);
}

TYPED_TEST(CycleTest, EdgeCycleToVertexCycle)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);

  auto e0 = ocgl::addEdge(g, v0, v1);
  auto e1 = ocgl::addEdge(g, v1, v2);
  auto e2 = ocgl::addEdge(g, v2, v0);

  // from 0 edges
  ocgl::EdgeCycle<Graph> edges1;
  ocgl::VertexCycle<Graph> vertices1 = ocgl::edgeCycleToVertexCycle(g, edges1);
  EXPECT_EQ(0, vertices1.size());

  // from 1 edge
  ocgl::EdgeCycle<Graph> edges2{e0};
  ocgl::VertexCycle<Graph> vertices2 = ocgl::edgeCycleToVertexCycle(g, edges2);
  EXPECT_EQ(0, vertices2.size());

  // from 2 edges
  ocgl::EdgeCycle<Graph> edges3{e0, e1};
  ocgl::VertexCycle<Graph> vertices3 = ocgl::edgeCycleToVertexCycle(g, edges3);
  EXPECT_EQ(0, vertices3.size());

  // from 3 edges : [ e0 e1 e2 ]
  ocgl::EdgeCycle<Graph> edges4{e0, e1, e2};
  ocgl::VertexCycle<Graph> vertices4 = ocgl::edgeCycleToVertexCycle(g, edges4);
  ASSERT_EQ(3, vertices4.size());
  EXPECT_EQ(v0, vertices4[0]);
  EXPECT_EQ(v1, vertices4[1]);
  EXPECT_EQ(v2, vertices4[2]);

  // from 3 edges : [ e1 e0 e2 ]
  ocgl::EdgeCycle<Graph> edges5{e1, e0, e2};
  ocgl::VertexCycle<Graph> vertices5 = ocgl::edgeCycleToVertexCycle(g, edges5);
  ASSERT_EQ(3, vertices5.size());
  EXPECT_EQ(v2, vertices5[0]);
  EXPECT_EQ(v1, vertices5[1]);
  EXPECT_EQ(v0, vertices5[2]);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
