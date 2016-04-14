#include <ocgl/algorithm/VF2State.h>
#include <ocgl/model/IndexGraph.h>

#include <gtest/gtest.h>



using Query = ocgl::model::IndexGraph;
using Graph = ocgl::model::IndexGraph;



// query
//
//     2
//     |
// 1---0----3
//     
// graph:
//
//     2
//     |
// 0---1---3
//     |
//     4
class VF2StateTest : public ::testing::Test
{
  protected:
    void SetUp()
    {
      auto u0 = ocgl::addVertex(query);
      auto u1 = ocgl::addVertex(query);
      auto u2 = ocgl::addVertex(query);
      auto u3 = ocgl::addVertex(query);
      ocgl::addEdge(query, u0, u1);
      ocgl::addEdge(query, u0, u2);
      ocgl::addEdge(query, u0, u3);

      auto v0 = ocgl::addVertex(graph);
      auto v1 = ocgl::addVertex(graph);
      auto v2 = ocgl::addVertex(graph);
      auto v3 = ocgl::addVertex(graph);
      auto v4 = ocgl::addVertex(graph);
      ocgl::addEdge(graph, v0, v1);
      ocgl::addEdge(graph, v1, v2);
      ocgl::addEdge(graph, v1, v3);
      ocgl::addEdge(graph, v1, v4);
    }

    Query query;
    Graph graph;
};



TEST_F(VF2StateTest, Constuctor)
{
  ocgl::algorithm::impl::VF2State<Query, Graph> s(query, graph);

  EXPECT_EQ(0, s.queryTSize());
  EXPECT_EQ(0, s.graphTSize());
  EXPECT_EQ(false, s.isGoal());

  EXPECT_EQ(false, s.isInQueryM(0));
  EXPECT_EQ(false, s.isInQueryM(1));
  EXPECT_EQ(false, s.isInQueryM(2));
  EXPECT_EQ(false, s.isInQueryM(3));

  EXPECT_EQ(false, s.isInGraphM(0));
  EXPECT_EQ(false, s.isInGraphM(1));
  EXPECT_EQ(false, s.isInGraphM(2));
  EXPECT_EQ(false, s.isInGraphM(3));
  EXPECT_EQ(false, s.isInGraphM(4));

  EXPECT_EQ(false, s.isInQueryT(0));
  EXPECT_EQ(false, s.isInQueryT(1));
  EXPECT_EQ(false, s.isInQueryT(2));
  EXPECT_EQ(false, s.isInQueryT(3));

  EXPECT_EQ(false, s.isInGraphT(0));
  EXPECT_EQ(false, s.isInGraphT(1));
  EXPECT_EQ(false, s.isInGraphT(2));
  EXPECT_EQ(false, s.isInGraphT(3));
  EXPECT_EQ(false, s.isInGraphT(4));
}

TEST_F(VF2StateTest, AddPair)
{
  ocgl::algorithm::impl::VF2State<Query, Graph> s(query, graph);

  // add 0 -> 1
  s.addPair(ocgl::getVertex(query, 0), ocgl::getVertex(graph, 1));

  // query M = { 0 }
  // query T = { 1, 2, 3 }
  // graph M = { 1 }
  // graph T = { 0, 2, 3, 4 }

  EXPECT_EQ(3, s.queryTSize());
  EXPECT_EQ(4, s.graphTSize());
  EXPECT_EQ(false, s.isGoal());

  EXPECT_EQ(true, s.isInQueryM(0));
  EXPECT_EQ(false, s.isInQueryM(1));
  EXPECT_EQ(false, s.isInQueryM(2));
  EXPECT_EQ(false, s.isInQueryM(3));

  EXPECT_EQ(false, s.isInGraphM(0));
  EXPECT_EQ(true, s.isInGraphM(1));
  EXPECT_EQ(false, s.isInGraphM(2));
  EXPECT_EQ(false, s.isInGraphM(3));
  EXPECT_EQ(false, s.isInGraphM(4));

  EXPECT_EQ(false, s.isInQueryT(0));
  EXPECT_EQ(true, s.isInQueryT(1));
  EXPECT_EQ(true, s.isInQueryT(2));
  EXPECT_EQ(true, s.isInQueryT(3));

  EXPECT_EQ(true, s.isInGraphT(0));
  EXPECT_EQ(false, s.isInGraphT(1));
  EXPECT_EQ(true, s.isInGraphT(2));
  EXPECT_EQ(true, s.isInGraphT(3));
  EXPECT_EQ(true, s.isInGraphT(4));
  
  // add 1 -> 0
  s.addPair(ocgl::getVertex(query, 1), ocgl::getVertex(graph, 0));

  // query M = { 0, 1 }
  // query T = { 2, 3 }
  // graph M = { 1, 0 }
  // graph T = { 2, 3, 4 }

  EXPECT_EQ(2, s.queryTSize());
  EXPECT_EQ(3, s.graphTSize());
  EXPECT_EQ(false, s.isGoal());

  EXPECT_EQ(true, s.isInQueryM(0));
  EXPECT_EQ(true, s.isInQueryM(1));
  EXPECT_EQ(false, s.isInQueryM(2));
  EXPECT_EQ(false, s.isInQueryM(3));

  EXPECT_EQ(true, s.isInGraphM(0));
  EXPECT_EQ(true, s.isInGraphM(1));
  EXPECT_EQ(false, s.isInGraphM(2));
  EXPECT_EQ(false, s.isInGraphM(3));
  EXPECT_EQ(false, s.isInGraphM(4));

  EXPECT_EQ(false, s.isInQueryT(0));
  EXPECT_EQ(false, s.isInQueryT(1));
  EXPECT_EQ(true, s.isInQueryT(2));
  EXPECT_EQ(true, s.isInQueryT(3));

  EXPECT_EQ(false, s.isInGraphT(0));
  EXPECT_EQ(false, s.isInGraphT(1));
  EXPECT_EQ(true, s.isInGraphT(2));
  EXPECT_EQ(true, s.isInGraphT(3));
  EXPECT_EQ(true, s.isInGraphT(4));
  
  // add 2 -> 2
  s.addPair(ocgl::getVertex(query, 2), ocgl::getVertex(graph, 2));

  // query M = { 0, 1, 2 }
  // query T = { 3 }
  // graph M = { 1, 0, 2 }
  // graph T = { 3, 4 }

  EXPECT_EQ(1, s.queryTSize());
  EXPECT_EQ(2, s.graphTSize());
  EXPECT_EQ(false, s.isGoal());

  EXPECT_EQ(true, s.isInQueryM(0));
  EXPECT_EQ(true, s.isInQueryM(1));
  EXPECT_EQ(true, s.isInQueryM(2));
  EXPECT_EQ(false, s.isInQueryM(3));

  EXPECT_EQ(true, s.isInGraphM(0));
  EXPECT_EQ(true, s.isInGraphM(1));
  EXPECT_EQ(true, s.isInGraphM(2));
  EXPECT_EQ(false, s.isInGraphM(3));
  EXPECT_EQ(false, s.isInGraphM(4));

  EXPECT_EQ(false, s.isInQueryT(0));
  EXPECT_EQ(false, s.isInQueryT(1));
  EXPECT_EQ(false, s.isInQueryT(2));
  EXPECT_EQ(true, s.isInQueryT(3));

  EXPECT_EQ(false, s.isInGraphT(0));
  EXPECT_EQ(false, s.isInGraphT(1));
  EXPECT_EQ(false, s.isInGraphT(2));
  EXPECT_EQ(true, s.isInGraphT(3));
  EXPECT_EQ(true, s.isInGraphT(4));

  // add 3 -> 4
  s.addPair(ocgl::getVertex(query, 3), ocgl::getVertex(graph, 4));

  // query M = { 0, 1, 2, 3 }
  // query T = { }
  // graph M = { 1, 0, 2, 4 }
  // graph T = { 3 }

  EXPECT_EQ(0, s.queryTSize());
  EXPECT_EQ(1, s.graphTSize());
  EXPECT_EQ(true, s.isGoal());

  EXPECT_EQ(true, s.isInQueryM(0));
  EXPECT_EQ(true, s.isInQueryM(1));
  EXPECT_EQ(true, s.isInQueryM(2));
  EXPECT_EQ(true, s.isInQueryM(3));

  EXPECT_EQ(true, s.isInGraphM(0));
  EXPECT_EQ(true, s.isInGraphM(1));
  EXPECT_EQ(true, s.isInGraphM(2));
  EXPECT_EQ(false, s.isInGraphM(3));
  EXPECT_EQ(true, s.isInGraphM(4));

  EXPECT_EQ(false, s.isInQueryT(0));
  EXPECT_EQ(false, s.isInQueryT(1));
  EXPECT_EQ(false, s.isInQueryT(2));
  EXPECT_EQ(false, s.isInQueryT(3));

  EXPECT_EQ(false, s.isInGraphT(0));
  EXPECT_EQ(false, s.isInGraphT(1));
  EXPECT_EQ(false, s.isInGraphT(2));
  EXPECT_EQ(true, s.isInGraphT(3));
  EXPECT_EQ(false, s.isInGraphT(4));
}

TEST_F(VF2StateTest, RemovePair)
{
  ocgl::algorithm::impl::VF2State<Query, Graph> s(query, graph);
  
  s.addPair(ocgl::getVertex(query, 0), ocgl::getVertex(graph, 1));
  s.addPair(ocgl::getVertex(query, 1), ocgl::getVertex(graph, 0));
  s.addPair(ocgl::getVertex(query, 2), ocgl::getVertex(graph, 2));
  s.addPair(ocgl::getVertex(query, 3), ocgl::getVertex(graph, 4));

  // remove 3 -> 4
  s.removePair(ocgl::getVertex(query, 3), ocgl::getVertex(graph, 4));

  // query M = { 0, 1, 2 }
  // query T = { 3 }
  // graph M = { 1, 0, 2 }
  // graph T = { 3, 4 }

  EXPECT_EQ(1, s.queryTSize());
  EXPECT_EQ(2, s.graphTSize());
  EXPECT_EQ(false, s.isGoal());

  EXPECT_EQ(true, s.isInQueryM(0));
  EXPECT_EQ(true, s.isInQueryM(1));
  EXPECT_EQ(true, s.isInQueryM(2));
  EXPECT_EQ(false, s.isInQueryM(3));

  EXPECT_EQ(true, s.isInGraphM(0));
  EXPECT_EQ(true, s.isInGraphM(1));
  EXPECT_EQ(true, s.isInGraphM(2));
  EXPECT_EQ(false, s.isInGraphM(3));
  EXPECT_EQ(false, s.isInGraphM(4));

  EXPECT_EQ(false, s.isInQueryT(0));
  EXPECT_EQ(false, s.isInQueryT(1));
  EXPECT_EQ(false, s.isInQueryT(2));
  EXPECT_EQ(true, s.isInQueryT(3));

  EXPECT_EQ(false, s.isInGraphT(0));
  EXPECT_EQ(false, s.isInGraphT(1));
  EXPECT_EQ(false, s.isInGraphT(2));
  EXPECT_EQ(true, s.isInGraphT(3));
  EXPECT_EQ(true, s.isInGraphT(4));

  // remove 2 -> 2
  s.removePair(ocgl::getVertex(query, 2), ocgl::getVertex(graph, 2));

  // query M = { 0, 1 }
  // query T = { 2, 3 }
  // graph M = { 1, 0 }
  // graph T = { 2, 3, 4 }

  EXPECT_EQ(2, s.queryTSize());
  EXPECT_EQ(3, s.graphTSize());
  EXPECT_EQ(false, s.isGoal());

  EXPECT_EQ(true, s.isInQueryM(0));
  EXPECT_EQ(true, s.isInQueryM(1));
  EXPECT_EQ(false, s.isInQueryM(2));
  EXPECT_EQ(false, s.isInQueryM(3));

  EXPECT_EQ(true, s.isInGraphM(0));
  EXPECT_EQ(true, s.isInGraphM(1));
  EXPECT_EQ(false, s.isInGraphM(2));
  EXPECT_EQ(false, s.isInGraphM(3));
  EXPECT_EQ(false, s.isInGraphM(4));

  EXPECT_EQ(false, s.isInQueryT(0));
  EXPECT_EQ(false, s.isInQueryT(1));
  EXPECT_EQ(true, s.isInQueryT(2));
  EXPECT_EQ(true, s.isInQueryT(3));

  EXPECT_EQ(false, s.isInGraphT(0));
  EXPECT_EQ(false, s.isInGraphT(1));
  EXPECT_EQ(true, s.isInGraphT(2));
  EXPECT_EQ(true, s.isInGraphT(3));
  EXPECT_EQ(true, s.isInGraphT(4));

  // remove 1 -> 0
  s.removePair(ocgl::getVertex(query, 1), ocgl::getVertex(graph, 0));

  // query M = { 0 }
  // query T = { 1, 2, 3 }
  // graph M = { 1 }
  // graph T = { 0, 2, 3, 4 }

  EXPECT_EQ(3, s.queryTSize());
  EXPECT_EQ(4, s.graphTSize());
  EXPECT_EQ(false, s.isGoal());

  EXPECT_EQ(true, s.isInQueryM(0));
  EXPECT_EQ(false, s.isInQueryM(1));
  EXPECT_EQ(false, s.isInQueryM(2));
  EXPECT_EQ(false, s.isInQueryM(3));

  EXPECT_EQ(false, s.isInGraphM(0));
  EXPECT_EQ(true, s.isInGraphM(1));
  EXPECT_EQ(false, s.isInGraphM(2));
  EXPECT_EQ(false, s.isInGraphM(3));
  EXPECT_EQ(false, s.isInGraphM(4));

  EXPECT_EQ(false, s.isInQueryT(0));
  EXPECT_EQ(true, s.isInQueryT(1));
  EXPECT_EQ(true, s.isInQueryT(2));
  EXPECT_EQ(true, s.isInQueryT(3));

  EXPECT_EQ(true, s.isInGraphT(0));
  EXPECT_EQ(false, s.isInGraphT(1));
  EXPECT_EQ(true, s.isInGraphT(2));
  EXPECT_EQ(true, s.isInGraphT(3));
  EXPECT_EQ(true, s.isInGraphT(4));

  // remove 0 -> 1
  s.removePair(ocgl::getVertex(query, 0), ocgl::getVertex(graph, 1));

  // query M = { }
  // query T = { }
  // graph M = { }
  // graph T = { }
  
  EXPECT_EQ(0, s.queryTSize());
  EXPECT_EQ(0, s.graphTSize());
  EXPECT_EQ(false, s.isGoal());

  EXPECT_EQ(false, s.isInQueryM(0));
  EXPECT_EQ(false, s.isInQueryM(1));
  EXPECT_EQ(false, s.isInQueryM(2));
  EXPECT_EQ(false, s.isInQueryM(3));

  EXPECT_EQ(false, s.isInGraphM(0));
  EXPECT_EQ(false, s.isInGraphM(1));
  EXPECT_EQ(false, s.isInGraphM(2));
  EXPECT_EQ(false, s.isInGraphM(3));
  EXPECT_EQ(false, s.isInGraphM(4));

  EXPECT_EQ(false, s.isInQueryT(0));
  EXPECT_EQ(false, s.isInQueryT(1));
  EXPECT_EQ(false, s.isInQueryT(2));
  EXPECT_EQ(false, s.isInQueryT(3));

  EXPECT_EQ(false, s.isInGraphT(0));
  EXPECT_EQ(false, s.isInGraphT(1));
  EXPECT_EQ(false, s.isInGraphT(2));
  EXPECT_EQ(false, s.isInGraphT(3));
  EXPECT_EQ(false, s.isInGraphT(4));
}

TEST_F(VF2StateTest, NextPair)
{
  ocgl::algorithm::impl::VF2State<Query, Graph> s(query, graph);

  auto u = ocgl::nullVertex<Query>();
  auto v = ocgl::nullVertex<Graph>();

  s.nextPair(u, v);
  EXPECT_TRUE(ocgl::isValidVertex(query, u));
  EXPECT_TRUE(ocgl::isValidVertex(graph, v));
  EXPECT_EQ(0, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(0, ocgl::getVertexIndex(graph, v));

  // add 0 -> 0
  //
  // query M = { 0 }
  // query T = { 1, 2, 3 }
  // graph M = { 0 }
  // graph T = { 1 }
  EXPECT_TRUE(s.isDead()); // queryTSize > graphTSize
  s.removePair(u, v);

  s.nextPair(u, v);
  EXPECT_EQ(0, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(1, ocgl::getVertexIndex(graph, v));
  
  // add 0 -> 1
  //
  // query M = { 0 }
  // query T = { 1, 2, 3 }
  // graph M = { 1 }
  // graph T = { 0, 2, 3, 4 }
  EXPECT_EQ(false, s.isDead());
  
  s.nextPair(u, v);
  EXPECT_EQ(1, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(0, ocgl::getVertexIndex(graph, v));
  
  // add 1 -> 0
  //
  // query M = { 0, 1 }
  // query T = { 2, 3 }
  // graph M = { 1, 0 }
  // graph T = { 2, 3, 4 }
  EXPECT_EQ(false, s.isDead());

  s.nextPair(u, v);
  EXPECT_EQ(2, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(2, ocgl::getVertexIndex(graph, v));
  
  // add 2 -> 2
  //
  // query M = { 0, 1, 2 }
  // query T = { 3 }
  // graph M = { 1, 0, 2 }
  // graph T = { 3, 4 }
  EXPECT_EQ(false, s.isDead());
  
  s.nextPair(u, v);
  EXPECT_EQ(3, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(3, ocgl::getVertexIndex(graph, v));
  
  // add 3 -> 3
  //
  // query M = { 0, 1, 2, 3 }
  // query T = { }
  // graph M = { 1, 0, 2, 3 }
  // graph T = { 4 }
  EXPECT_EQ(true, s.isGoal());
  s.removePair(u, v);
  
  s.nextPair(u, v);
  EXPECT_EQ(3, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(4, ocgl::getVertexIndex(graph, v));
  
  // add 3 -> 4
  //
  // query M = { 0, 1, 2, 3 }
  // query T = { }
  // graph M = { 1, 0, 2, 4 }
  // graph T = { 3 }
  EXPECT_EQ(true, s.isGoal());
  s.removePair(u, v);
  
  EXPECT_EQ(false, s.nextPair(u, v));
  u = ocgl::getVertex(query, 2);
  v = ocgl::getVertex(graph, 2);
  s.removePair(u, v);
  
  s.nextPair(u, v);
  EXPECT_EQ(2, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(3, ocgl::getVertexIndex(graph, v));
  
  // add 2 -> 3
  //
  // query M = { 0, 1, 2 }
  // query T = { 3 }
  // graph M = { 1, 0, 3 }
  // graph T = { 2, 4 }
  EXPECT_EQ(false, s.isGoal());

  s.nextPair(u, v);
  EXPECT_EQ(3, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(2, ocgl::getVertexIndex(graph, v));
  
  // add 3 -> 2
  //
  // query M = { 0, 1, 2, 3 }
  // query T = { }
  // graph M = { 1, 0, 3, 2 }
  // graph T = { 4 }
  EXPECT_EQ(true, s.isGoal());
  s.removePair(u, v);

  s.nextPair(u, v);
  EXPECT_EQ(3, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(4, ocgl::getVertexIndex(graph, v));
  
  // add 3 -> 4
  //
  // query M = { 0, 1, 2, 3 }
  // query T = { }
  // graph M = { 1, 0, 3, 4 }
  // graph T = { 2 }
  EXPECT_EQ(true, s.isGoal());
  s.removePair(u, v);

  EXPECT_EQ(false, s.nextPair(u, v));
  u = ocgl::getVertex(query, 2);
  v = ocgl::getVertex(graph, 3);
  s.removePair(u, v);

  s.nextPair(u, v);
  EXPECT_EQ(2, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(4, ocgl::getVertexIndex(graph, v));
  
  // add 2 -> 4
  //
  // query M = { 0, 1, 2 }
  // query T = { 3 }
  // graph M = { 1, 0, 4 }
  // graph T = { 2, 3 }
  EXPECT_EQ(false, s.isGoal());
  
  s.nextPair(u, v);
  EXPECT_EQ(3, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(2, ocgl::getVertexIndex(graph, v));

  // add 3 -> 2
  //
  // query M = { 0, 1, 2, 3 }
  // query T = { }
  // graph M = { 1, 0, 4, 2 }
  // graph T = { 3 }
  EXPECT_EQ(true, s.isGoal());
  s.removePair(u, v);
  
  s.nextPair(u, v);
  EXPECT_EQ(3, ocgl::getVertexIndex(query, u));
  EXPECT_EQ(3, ocgl::getVertexIndex(graph, v));

  // add 3 -> 3
  //
  // query M = { 0, 1, 2, 3 }
  // query T = { }
  // graph M = { 1, 0, 4, 3 }
  // graph T = { 2 }
  EXPECT_EQ(true, s.isGoal());

  EXPECT_EQ(false, s.nextPair(u, v));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

