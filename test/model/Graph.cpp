#include <ocgl/GraphTraits.h>

#include "../test.h"

GRAPH_TYPED_TEST(GraphTest);

// test:
//   addVertex
//   numVertices
//   getIndex
TYPED_TEST(GraphTest, addVertex)
{
  TypeParam g;

  EXPECT_EQ(0, ocgl::numVertices(g));

  auto v1 = ocgl::addVertex(g);
  EXPECT_EQ(1, ocgl::numVertices(g));
  EXPECT_EQ(0, ocgl::getIndex(g, v1));

  auto v2 = ocgl::addVertex(g);
  EXPECT_EQ(2, ocgl::numVertices(g));
  EXPECT_EQ(1, ocgl::getIndex(g, v2));

  auto v3 = ocgl::addVertex(g);
  EXPECT_EQ(3, ocgl::numVertices(g));
  EXPECT_EQ(2, ocgl::getIndex(g, v3));
}

// test:
//   addEdge
//   numEdges
//   getIndex
//   getSource
//   getTarget
//   getOther
TYPED_TEST(GraphTest, addEdge)
{
  TypeParam g;

  EXPECT_EQ(0, ocgl::numEdges(g));

  auto v1 = ocgl::addVertex(g);
  auto v2 = ocgl::addVertex(g);
  auto v3 = ocgl::addVertex(g);
  auto v4 = ocgl::addVertex(g);

  auto e1 = ocgl::addEdge(g, v1, v2);
  EXPECT_EQ(1, ocgl::numEdges(g));
  EXPECT_GE(0, ocgl::getIndex(g, e1));
  EXPECT_EQ(v1, ocgl::getSource(g, e1));
  EXPECT_EQ(v2, ocgl::getTarget(g, e1));
  EXPECT_EQ(v2, ocgl::getOther(g, e1, v1));
  EXPECT_EQ(v1, ocgl::getOther(g, e1, v2));

  auto e2 = ocgl::addEdge(g, v2, v3);
  EXPECT_EQ(2, ocgl::numEdges(g));
  EXPECT_GE(1, ocgl::getIndex(g, e2));
  EXPECT_EQ(v2, ocgl::getSource(g, e2));
  EXPECT_EQ(v3, ocgl::getTarget(g, e2));
  EXPECT_EQ(v3, ocgl::getOther(g, e2, v2));
  EXPECT_EQ(v2, ocgl::getOther(g, e2, v3));

  auto e3 = ocgl::addEdge(g, v3, v4);
  EXPECT_EQ(3, ocgl::numEdges(g));
  EXPECT_GE(2, ocgl::getIndex(g, e3));
  EXPECT_EQ(v3, ocgl::getSource(g, e3));
  EXPECT_EQ(v4, ocgl::getTarget(g, e3));
  EXPECT_EQ(v4, ocgl::getOther(g, e3, v3));
  EXPECT_EQ(v3, ocgl::getOther(g, e3, v4));
}


//    3  6
//    |  |
// 2--0--1--5
//    |  |
//    4  7
template<typename Graph>
Graph makeTestGraph()
{
  using Vertex = typename ocgl::GraphTraits<Graph>::Vertex;
  using Edge = typename ocgl::GraphTraits<Graph>::Edge;
  Graph g;

  std::vector<Vertex> v;
  for (int i = 0; i < 8; ++i) {
    v.push_back(ocgl::addVertex(g));
    // make "id gap" in vertices
    auto w = ocgl::addVertex(g);
    ocgl::removeVertex(g, w);
  }

  std::vector<Edge> e(7);
  e[0] = ocgl::addEdge(g, v[0], v[1]);
  e[1] = ocgl::addEdge(g, v[0], v[2]);
  e[2] = ocgl::addEdge(g, v[0], v[3]);
  e[3] = ocgl::addEdge(g, v[0], v[4]);
  e[4] = ocgl::addEdge(g, v[1], v[5]);
  e[5] = ocgl::addEdge(g, v[1], v[6]);
  e[6] = ocgl::addEdge(g, v[1], v[7]);

  return g;
}

TYPED_TEST(GraphTest, numVertices)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  EXPECT_EQ(8, ocgl::numVertices(g));
}

TYPED_TEST(GraphTest, numEdges)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  EXPECT_EQ(7, ocgl::numEdges(g));
}

TYPED_TEST(GraphTest, getVertices)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  auto V = ocgl::getVertices(g).toVector();

  EXPECT_EQ(ocgl::numVertices(g), V.size());
}

TYPED_TEST(GraphTest, getEdges)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  auto E = ocgl::getEdges(g).toVector();

  EXPECT_EQ(ocgl::numEdges(g), E.size());
}

TYPED_TEST(GraphTest, getVertex)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  auto V = ocgl::getVertices(g).toVector();

  EXPECT_EQ(V[0], ocgl::getVertex(g, 0));
  EXPECT_EQ(V[1], ocgl::getVertex(g, 1));
  EXPECT_EQ(V[2], ocgl::getVertex(g, 2));
  EXPECT_EQ(V[3], ocgl::getVertex(g, 3));
  EXPECT_EQ(V[4], ocgl::getVertex(g, 4));
  EXPECT_EQ(V[5], ocgl::getVertex(g, 5));
  EXPECT_EQ(V[6], ocgl::getVertex(g, 6));
  EXPECT_EQ(V[7], ocgl::getVertex(g, 7));
}

TYPED_TEST(GraphTest, getEdge1)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  auto E = ocgl::getEdges(g).toVector();

  EXPECT_EQ(E[0], ocgl::getEdge(g, 0));
  EXPECT_EQ(E[1], ocgl::getEdge(g, 1));
  EXPECT_EQ(E[2], ocgl::getEdge(g, 2));
  EXPECT_EQ(E[3], ocgl::getEdge(g, 3));
  EXPECT_EQ(E[4], ocgl::getEdge(g, 4));
  EXPECT_EQ(E[5], ocgl::getEdge(g, 5));
  EXPECT_EQ(E[6], ocgl::getEdge(g, 6));
}

TYPED_TEST(GraphTest, getDegree)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  auto V = ocgl::getVertices(g).toVector();

  EXPECT_EQ(4, ocgl::getDegree(g, V[0]));
  EXPECT_EQ(4, ocgl::getDegree(g, V[1]));
  EXPECT_EQ(1, ocgl::getDegree(g, V[2]));
  EXPECT_EQ(1, ocgl::getDegree(g, V[3]));
  EXPECT_EQ(1, ocgl::getDegree(g, V[4]));
  EXPECT_EQ(1, ocgl::getDegree(g, V[5]));
  EXPECT_EQ(1, ocgl::getDegree(g, V[6]));
  EXPECT_EQ(1, ocgl::getDegree(g, V[7]));
}

TYPED_TEST(GraphTest, getIncident)
{
  using Graph = TypeParam;
  using Edge = typename ocgl::GraphTraits<Graph>::Edge;
  auto g = makeTestGraph<Graph>();

  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  std::vector<Edge> incident0(ocgl::getIncident(g, V[0]).begin(), ocgl::getIncident(g, V[0]).end());
  ASSERT_EQ(4, incident0.size());
  EXPECT_EQ(E[0], incident0[0]);
  EXPECT_EQ(E[1], incident0[1]);
  EXPECT_EQ(E[2], incident0[2]);
  EXPECT_EQ(E[3], incident0[3]);

  std::vector<Edge> incident1(ocgl::getIncident(g, V[1]).begin(), ocgl::getIncident(g, V[1]).end());
  ASSERT_EQ(4, incident1.size());
  EXPECT_EQ(E[0], incident1[0]);
  EXPECT_EQ(E[4], incident1[1]);
  EXPECT_EQ(E[5], incident1[2]);
  EXPECT_EQ(E[6], incident1[3]);

  std::vector<Edge> incident2(ocgl::getIncident(g, V[2]).begin(), ocgl::getIncident(g, V[2]).end());
  ASSERT_EQ(1, incident2.size());
  EXPECT_EQ(E[1], incident2[0]);

  std::vector<Edge> incident3(ocgl::getIncident(g, V[3]).begin(), ocgl::getIncident(g, V[3]).end());
  ASSERT_EQ(1, incident3.size());
  EXPECT_EQ(E[2], incident3[0]);

  std::vector<Edge> incident4(ocgl::getIncident(g, V[4]).begin(), ocgl::getIncident(g, V[4]).end());
  ASSERT_EQ(1, incident4.size());
  EXPECT_EQ(E[3], incident4[0]);

  std::vector<Edge> incident5(ocgl::getIncident(g, V[5]).begin(), ocgl::getIncident(g, V[5]).end());
  ASSERT_EQ(1, incident5.size());
  EXPECT_EQ(E[4], incident5[0]);

  std::vector<Edge> incident6(ocgl::getIncident(g, V[6]).begin(), ocgl::getIncident(g, V[6]).end());
  ASSERT_EQ(1, incident6.size());
  EXPECT_EQ(E[5], incident6[0]);

  std::vector<Edge> incident7(ocgl::getIncident(g, V[7]).begin(), ocgl::getIncident(g, V[7]).end());
  ASSERT_EQ(1, incident7.size());
  EXPECT_EQ(E[6], incident7[0]);
}

TYPED_TEST(GraphTest, getAdjacent)
{
  using Graph = TypeParam;
  using Vertex = typename ocgl::GraphTraits<Graph>::Vertex;
  auto g = makeTestGraph<Graph>();

  auto V = ocgl::getVertices(g).toVector();

  std::vector<Vertex> adjacent0(ocgl::getAdjacent(g, V[0]).begin(), ocgl::getAdjacent(g, V[0]).end());
  EXPECT_EQ(4, adjacent0.size());
  EXPECT_EQ(V[1], adjacent0[0]);
  EXPECT_EQ(V[2], adjacent0[1]);
  EXPECT_EQ(V[3], adjacent0[2]);
  EXPECT_EQ(V[4], adjacent0[3]);

  std::vector<Vertex> adjacent1(ocgl::getAdjacent(g, V[1]).begin(), ocgl::getAdjacent(g, V[1]).end());
  EXPECT_EQ(4, adjacent1.size());
  EXPECT_EQ(V[0], adjacent1[0]);
  EXPECT_EQ(V[5], adjacent1[1]);
  EXPECT_EQ(V[6], adjacent1[2]);
  EXPECT_EQ(V[7], adjacent1[3]);

  std::vector<Vertex> adjacent2(ocgl::getAdjacent(g, V[2]).begin(), ocgl::getAdjacent(g, V[2]).end());
  EXPECT_EQ(1, adjacent2.size());
  EXPECT_EQ(V[0], adjacent2[0]);

  std::vector<Vertex> adjacent3(ocgl::getAdjacent(g, V[3]).begin(), ocgl::getAdjacent(g, V[3]).end());
  EXPECT_EQ(1, adjacent3.size());
  EXPECT_EQ(V[0], adjacent3[0]);

  std::vector<Vertex> adjacent4(ocgl::getAdjacent(g, V[4]).begin(), ocgl::getAdjacent(g, V[4]).end());
  EXPECT_EQ(1, adjacent4.size());
  EXPECT_EQ(V[0], adjacent4[0]);

  std::vector<Vertex> adjacent5(ocgl::getAdjacent(g, V[5]).begin(), ocgl::getAdjacent(g, V[5]).end());
  EXPECT_EQ(1, adjacent5.size());
  EXPECT_EQ(V[1], adjacent5[0]);

  std::vector<Vertex> adjacent6(ocgl::getAdjacent(g, V[6]).begin(), ocgl::getAdjacent(g, V[6]).end());
  EXPECT_EQ(1, adjacent6.size());
  EXPECT_EQ(V[1], adjacent6[0]);

  std::vector<Vertex> adjacent7(ocgl::getAdjacent(g, V[7]).begin(), ocgl::getAdjacent(g, V[7]).end());
  EXPECT_EQ(1, adjacent7.size());
  EXPECT_EQ(V[1], adjacent7[0]);
}

TYPED_TEST(GraphTest, getEdge2)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  EXPECT_EQ(E[0], ocgl::getEdge(g, V[0], V[1]));
  EXPECT_EQ(E[0], ocgl::getEdge(g, V[1], V[0]));

  EXPECT_EQ(E[1], ocgl::getEdge(g, V[0], V[2]));
  EXPECT_EQ(E[1], ocgl::getEdge(g, V[2], V[0]));
  EXPECT_EQ(E[2], ocgl::getEdge(g, V[0], V[3]));
  EXPECT_EQ(E[2], ocgl::getEdge(g, V[3], V[0]));
  EXPECT_EQ(E[3], ocgl::getEdge(g, V[0], V[4]));
  EXPECT_EQ(E[3], ocgl::getEdge(g, V[4], V[0]));

  EXPECT_EQ(E[4], ocgl::getEdge(g, V[1], V[5]));
  EXPECT_EQ(E[4], ocgl::getEdge(g, V[5], V[1]));
  EXPECT_EQ(E[5], ocgl::getEdge(g, V[1], V[6]));
  EXPECT_EQ(E[5], ocgl::getEdge(g, V[6], V[1]));
  EXPECT_EQ(E[6], ocgl::getEdge(g, V[1], V[7]));
  EXPECT_EQ(E[6], ocgl::getEdge(g, V[7], V[1]));

  EXPECT_EQ(ocgl::nullEdge<Graph>(), ocgl::getEdge(g, V[0], V[5]));
  EXPECT_EQ(ocgl::nullEdge<Graph>(), ocgl::getEdge(g, V[0], V[6]));
  EXPECT_EQ(ocgl::nullEdge<Graph>(), ocgl::getEdge(g, V[0], V[7]));

  EXPECT_EQ(ocgl::nullEdge<Graph>(), ocgl::getEdge(g, V[1], V[2]));
  EXPECT_EQ(ocgl::nullEdge<Graph>(), ocgl::getEdge(g, V[1], V[3]));
  EXPECT_EQ(ocgl::nullEdge<Graph>(), ocgl::getEdge(g, V[1], V[4]));
}

TYPED_TEST(GraphTest, isConnected)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  auto V = ocgl::getVertices(g).toVector();

  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[1]));
  EXPECT_TRUE(ocgl::isConnected(g, V[1], V[0]));

  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[2]));
  EXPECT_TRUE(ocgl::isConnected(g, V[2], V[0]));
  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[3]));
  EXPECT_TRUE(ocgl::isConnected(g, V[3], V[0]));
  EXPECT_TRUE(ocgl::isConnected(g, V[0], V[4]));
  EXPECT_TRUE(ocgl::isConnected(g, V[4], V[0]));

  EXPECT_TRUE(ocgl::isConnected(g, V[1], V[5]));
  EXPECT_TRUE(ocgl::isConnected(g, V[5], V[1]));
  EXPECT_TRUE(ocgl::isConnected(g, V[1], V[6]));
  EXPECT_TRUE(ocgl::isConnected(g, V[6], V[1]));
  EXPECT_TRUE(ocgl::isConnected(g, V[1], V[7]));
  EXPECT_TRUE(ocgl::isConnected(g, V[7], V[1]));

  EXPECT_FALSE(ocgl::isConnected(g, V[0], V[5]));
  EXPECT_FALSE(ocgl::isConnected(g, V[0], V[6]));
  EXPECT_FALSE(ocgl::isConnected(g, V[0], V[7]));

  EXPECT_FALSE(ocgl::isConnected(g, V[1], V[2]));
  EXPECT_FALSE(ocgl::isConnected(g, V[1], V[3]));
  EXPECT_FALSE(ocgl::isConnected(g, V[1], V[4]));
}


TYPED_TEST(GraphTest, clear)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  ocgl::clearGraph(g);

  EXPECT_EQ(0, ocgl::numVertices(g));
  EXPECT_EQ(0, ocgl::numEdges(g));

  auto V = ocgl::getVertices(g).toVector();
  auto E = ocgl::getEdges(g).toVector();

  EXPECT_EQ(0, V.size());
  EXPECT_EQ(0, E.size());
}

TYPED_TEST(GraphTest, removeEdge)
{
  using Graph = TypeParam;
  auto g = makeTestGraph<Graph>();

  while (ocgl::numEdges(g)) {
    auto e = *ocgl::getEdges(g).begin();
    auto v = ocgl::getSource(g, e);
    auto w = ocgl::getTarget(g, e);

    auto numEdgesBefore = ocgl::numEdges(g);
    auto vDegreeBefore = ocgl::getDegree(g, v);
    auto wDegreeBefore = ocgl::getDegree(g, w);

    ocgl::removeEdge(g, e);

    EXPECT_EQ(numEdgesBefore - 1, ocgl::numEdges(g));
    EXPECT_EQ(vDegreeBefore - 1, ocgl::getDegree(g, v));
    EXPECT_EQ(wDegreeBefore - 1, ocgl::getDegree(g, w));
  }
}

TYPED_TEST(GraphTest, removeVertex)
{
  using Graph = TypeParam;
  using Vertex  = typename ocgl::GraphTraits<Graph>::Vertex;
  auto g = makeTestGraph<Graph>();

  while (ocgl::numVertices(g)) {
    auto v = ocgl::getVertex(g, ocgl::numVertices(g) - 1);

    auto numVerticesBefore = ocgl::numVertices(g);
    auto numEdgesBefore = ocgl::numEdges(g);
    auto degree = ocgl::getDegree(g, v);

    std::vector<Vertex> nbrs(ocgl::getAdjacent(g, v).begin(), ocgl::getAdjacent(g, v).end());
    std::vector<unsigned int> nbrsDegree;
    for (auto w : nbrs)
      nbrsDegree.push_back(ocgl::getDegree(g, w));

    ocgl::removeVertex(g, v);

    EXPECT_EQ(numVerticesBefore - 1, ocgl::numVertices(g));
    EXPECT_EQ(numEdgesBefore - degree, ocgl::numEdges(g));

    for (std::size_t i = 0; i < nbrs.size(); ++i)
      EXPECT_EQ(nbrsDegree[i] - 1, ocgl::getDegree(g, nbrs[i]));
  }
}



int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
