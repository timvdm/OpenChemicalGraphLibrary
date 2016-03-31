#include <ocgl/Path.h>

#include "test.h"

GRAPH_TYPED_TEST(PathTest);

TYPED_TEST(PathTest, CommonVertex)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);

  auto e0 = ocgl::addEdge(g, v0, v1);
  auto e1 = ocgl::addEdge(g, v0, v2);
  auto e2 = ocgl::addEdge(g, v3, v0);
  auto e3 = ocgl::addEdge(g, v1, v2);

  // source(a) == source(b)
  EXPECT_EQ(v0, ocgl::commonVertex(g, e0, e1));

  // source(a) == target(b)
  EXPECT_EQ(v0, ocgl::commonVertex(g, e0, e2));
  EXPECT_EQ(v0, ocgl::commonVertex(g, e1, e2));

  // target(a) == source(b)
  EXPECT_EQ(v1, ocgl::commonVertex(g, e0, e3));

  // target(a) == target(b)
  EXPECT_EQ(v2, ocgl::commonVertex(g, e1, e3));

  // no common vertex
  EXPECT_EQ(ocgl::nullVertex<Graph>(), ocgl::commonVertex(g, e2, e3));
}


TYPED_TEST(PathTest, IsVertexPath)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);

  ocgl::addEdge(g, v0, v1);
  ocgl::addEdge(g, v2, v3);

  // g:
  //
  // v0 ---- v1     v2 ---- v3


  // [] is a path
  ocgl::VertexList<Graph> p1;
  EXPECT_TRUE(ocgl::isVertexPath(g, p1));

  // [ v0 ] is a path
  ocgl::VertexList<Graph> p2{v0};
  EXPECT_TRUE(ocgl::isVertexPath(g, p2));

  // [ v0 v1 ] is a path
  ocgl::VertexList<Graph> p3{v0, v1};
  EXPECT_TRUE(ocgl::isVertexPath(g, p3));

  // [ v0 v1 v2 ] is not a path
  ocgl::VertexList<Graph> p4{v0, v1, v2};
  EXPECT_FALSE(ocgl::isVertexPath(g, p4));

  // [ v0 v1 v2 v3 ] is not a path
  ocgl::VertexList<Graph> p5{v0, v1, v2, v3};
  EXPECT_FALSE(ocgl::isVertexPath(g, p5));

  ocgl::addEdge(g, v1, v2);

  // g:
  //
  // v0 ---- v1 ---- v2 ---- v3

  // [ v0 v1 v2 v3 ] is a path
  ocgl::VertexList<Graph> p6{v0, v1, v2, v3};
  EXPECT_TRUE(ocgl::isVertexPath(g, p6));

  // [ v3 v2 v1 v0 ] is a path
  ocgl::VertexList<Graph> p7{v3, v2, v1, v0};
  EXPECT_TRUE(ocgl::isVertexPath(g, p7));

  // [ v0 v1 v2 ] is a path
  ocgl::VertexList<Graph> p8{v0, v1, v2};
  EXPECT_TRUE(ocgl::isVertexPath(g, p8));

  // [ v1 v2 v3 ] is a path
  ocgl::VertexList<Graph> p9{v1, v2, v3};
  EXPECT_TRUE(ocgl::isVertexPath(g, p9));

  // [ v0 v1 v3 ] is a not path
  ocgl::VertexList<Graph> p10{v0, v1, v3};
  EXPECT_FALSE(ocgl::isVertexPath(g, p10));
}

TYPED_TEST(PathTest, IsEdgePath)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);

  auto e0 = ocgl::addEdge(g, v0, v1);
  auto e1 = ocgl::addEdge(g, v2, v3);

  // g:
  //     e0             e1
  // v0 ---- v1     v2 ---- v3


  // [] is a path
  ocgl::EdgeList<Graph> p1;
  EXPECT_TRUE(ocgl::isEdgePath(g, p1));

  // [ e0 ] is a path
  ocgl::EdgeList<Graph> p2{e0};
  EXPECT_TRUE(ocgl::isEdgePath(g, p2));

  // [ e1 ] is a path
  ocgl::EdgeList<Graph> p3{e1};
  EXPECT_TRUE(ocgl::isEdgePath(g, p3));

  // [ e0 e1 ] is not a path
  ocgl::EdgeList<Graph> p4{e0, e1};
  EXPECT_FALSE(ocgl::isEdgePath(g, p4));

  auto e2 = ocgl::addEdge(g, v1, v2);

  // g:
  //     e0      e2      e1
  // v0 ---- v1 ---- v2 ---- v3

  // [ e0 e2 e1 ] is a path
  ocgl::EdgeList<Graph> p6{e0, e2, e1};
  EXPECT_TRUE(ocgl::isEdgePath(g, p6));

  // [ e1 e2 e0 ] is a path
  ocgl::EdgeList<Graph> p7{e1, e2, e0};
  EXPECT_TRUE(ocgl::isEdgePath(g, p7));

  // [ e0 e2 ] is a path
  ocgl::EdgeList<Graph> p8{e0, e2};
  EXPECT_TRUE(ocgl::isEdgePath(g, p8));

  // [ e2 e1 ] is a path
  ocgl::EdgeList<Graph> p9{e2, e1};
  EXPECT_TRUE(ocgl::isEdgePath(g, p9));

  // [ e0 e1 e2 ] is a not path
  ocgl::EdgeList<Graph> p10{e0, e1, e2};
  EXPECT_FALSE(ocgl::isEdgePath(g, p10));
}

TYPED_TEST(PathTest, VertexPathDefaultConstructor)
{
  using Graph = TypeParam;
  ocgl::VertexPath<Graph> path;
  EXPECT_EQ(0, path.size());
}

TYPED_TEST(PathTest, VertexPathVertexListCopyConstructor)
{
  using Graph = TypeParam;
  Graph g;

  ocgl::VertexList<Graph> vertices;
  vertices.push_back(ocgl::addVertex(g));
  vertices.push_back(ocgl::addVertex(g));
  vertices.push_back(ocgl::addVertex(g));

  ocgl::addEdge(g, vertices[0], vertices[1]);
  ocgl::addEdge(g, vertices[1], vertices[2]);

  ocgl::VertexPath<Graph> path(vertices);
  ASSERT_EQ(3, path.size());
  EXPECT_EQ(vertices[0], path[0]);
  EXPECT_EQ(vertices[1], path[1]);
  EXPECT_EQ(vertices[2], path[2]);
}

TYPED_TEST(PathTest, VertexPathVertexListMoveConstructor)
{
  using Graph = TypeParam;
  Graph g;

  ocgl::VertexList<Graph> vertices;
  vertices.push_back(ocgl::addVertex(g));
  vertices.push_back(ocgl::addVertex(g));
  vertices.push_back(ocgl::addVertex(g));

  ocgl::addEdge(g, vertices[0], vertices[1]);
  ocgl::addEdge(g, vertices[1], vertices[2]);

  // copy vertices
  ocgl::VertexList<Graph> verticesCopy(vertices);

  ocgl::VertexPath<Graph> path(std::move(verticesCopy));
  ASSERT_EQ(3, path.size());
  EXPECT_EQ(vertices[0], path[0]);
  EXPECT_EQ(vertices[1], path[1]);
  EXPECT_EQ(vertices[2], path[2]);
}

TYPED_TEST(PathTest, VertexPathToEdgePath)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);

  auto e0 = ocgl::addEdge(g, v0, v1);
  auto e1 = ocgl::addEdge(g, v1, v2);
  auto e2 = ocgl::addEdge(g, v2, v3);

  // from empty vertex path
  ocgl::VertexPath<Graph> vertices1;
  ocgl::EdgePath<Graph> edges1 = vertices1.edges(g);
  EXPECT_EQ(0, edges1.size());

  // from single vertex path
  ocgl::VertexPath<Graph> vertices2{v0};
  ocgl::EdgePath<Graph> edges2 = vertices2.edges(g);
  EXPECT_EQ(0, edges2.size());

  // from 4 vertices
  ocgl::VertexPath<Graph> vertices3{v0, v1, v2, v3};
  ocgl::EdgePath<Graph> edges3 = vertices3.edges(g);
  ASSERT_EQ(3, edges3.size());
  EXPECT_EQ(e0, edges3[0]);
  EXPECT_EQ(e1, edges3[1]);
  EXPECT_EQ(e2, edges3[2]);
}

TYPED_TEST(PathTest, EdgePathDefaultConstructor)
{
  using Graph = TypeParam;
  ocgl::EdgePath<Graph> path;
  EXPECT_EQ(0, path.size());
}

TYPED_TEST(PathTest, EdgePathEdgeListCopyConstructor)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);

  ocgl::EdgeList<Graph> edges;
  edges.push_back(ocgl::addEdge(g, v0, v1));
  edges.push_back(ocgl::addEdge(g, v1, v2));

  ocgl::EdgePath<Graph> path(edges);
  ASSERT_EQ(2, path.size());
  EXPECT_EQ(edges[0], path[0]);
  EXPECT_EQ(edges[1], path[1]);
}

TYPED_TEST(PathTest, EdgePathEdgeListMoveConstructor)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);

  ocgl::EdgeList<Graph> edges;
  edges.push_back(ocgl::addEdge(g, v0, v1));
  edges.push_back(ocgl::addEdge(g, v1, v2));

  // copy edges
  ocgl::EdgeList<Graph> edgesCopy(edges);

  ocgl::EdgePath<Graph> path(std::move(edgesCopy));
  ASSERT_EQ(2, path.size());
  EXPECT_EQ(edges[0], path[0]);
  EXPECT_EQ(edges[1], path[1]);
}

TYPED_TEST(PathTest, EdgePathToVertexPath)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);

  auto e0 = ocgl::addEdge(g, v0, v1);
  auto e1 = ocgl::addEdge(g, v1, v2);
  auto e2 = ocgl::addEdge(g, v2, v3);

  // from empty edge path
  ocgl::EdgePath<Graph> edges1;
  ocgl::VertexPath<Graph> vertices1 = edges1.vertices(g);
  EXPECT_EQ(0, vertices1.size());

  // from single edge path
  ocgl::EdgePath<Graph> edges2{e1};
  ocgl::VertexPath<Graph> vertices2 = edges2.vertices(g);
  ASSERT_EQ(2, vertices2.size());
  EXPECT_EQ(v1, vertices2[0]);
  EXPECT_EQ(v2, vertices2[1]);

  // from 3 edges
  ocgl::EdgePath<Graph> edges3{e0, e1, e2};
  ocgl::VertexPath<Graph> vertices3 = edges3.vertices(g);
  ASSERT_EQ(4, vertices3.size());
  EXPECT_EQ(v0, vertices3[0]);
  EXPECT_EQ(v1, vertices3[1]);
  EXPECT_EQ(v2, vertices3[2]);
  EXPECT_EQ(v3, vertices3[3]);
}

TYPED_TEST(PathTest, EdgePathSourceTarget)
{
  using Graph = TypeParam;
  Graph g;

  auto v0 = ocgl::addVertex(g);
  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);

  auto e0 = ocgl::addEdge(g, v1, v0);
  auto e1 = ocgl::addEdge(g, v1, v2);
  auto e2 = ocgl::addEdge(g, v2, v3);

  // from empty edge path
  ocgl::EdgePath<Graph> edges1;
  EXPECT_EQ(ocgl::nullVertex<Graph>(), edges1.source(g));
  EXPECT_EQ(ocgl::nullVertex<Graph>(), edges1.target(g));

  // from single edge path
  ocgl::EdgePath<Graph> edges2{e1};
  EXPECT_EQ(v1, edges2.source(g));
  EXPECT_EQ(v2, edges2.target(g));

  // from [ e0 e1 e2 ]
  ocgl::EdgePath<Graph> edges3{e0, e1, e2};
  EXPECT_EQ(v0, edges3.source(g));
  EXPECT_EQ(v3, edges3.target(g));

  // from [ e2 e1 e0 ]
  ocgl::EdgePath<Graph> edges4{e2, e1, e0};
  EXPECT_EQ(v3, edges4.source(g));
  EXPECT_EQ(v0, edges4.target(g));
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
