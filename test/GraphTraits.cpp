#include <ocgl/GraphTraits.h>

#include <gtest/gtest.h>

struct IdGraph
{
  using Vertex = int;
  using Edge = int;
  using VertexIter = char;
  using EdgeIter = short;
  using IncidentIter = float;
  using AdjacentIter = double;

  static Vertex nullVertex()
  {
    return -1;
  }

  static Edge nullEdge()
  {
    return -1;
  }
};

TEST(GraphTraitsTest, IdGraph)
{
  using Graph = IdGraph;

  // check for correct associated types
  EXPECT_TRUE((std::is_same<Graph::Vertex, ocgl::GraphTraits<Graph>::Vertex>::value));
  EXPECT_TRUE((std::is_same<Graph::Edge, ocgl::GraphTraits<Graph>::Edge>::value));
  EXPECT_TRUE((std::is_same<Graph::VertexIter, ocgl::GraphTraits<Graph>::VertexIter>::value));
  EXPECT_TRUE((std::is_same<Graph::EdgeIter, ocgl::GraphTraits<Graph>::EdgeIter>::value));
  EXPECT_TRUE((std::is_same<Graph::IncidentIter, ocgl::GraphTraits<Graph>::IncidentIter>::value));
  EXPECT_TRUE((std::is_same<Graph::AdjacentIter, ocgl::GraphTraits<Graph>::AdjacentIter>::value));

  // test null
  EXPECT_EQ(-1, ocgl::GraphTraits<Graph>::nullVertex());
  EXPECT_EQ(-1, ocgl::GraphTraits<Graph>::nullEdge());

  // check isNull/isValid
  Graph g;
  EXPECT_TRUE(ocgl::isNullVertex(g, -1));
  EXPECT_TRUE(ocgl::isNullEdge(g, -1));
  EXPECT_FALSE(ocgl::isNullVertex(g, 0));
  EXPECT_FALSE(ocgl::isNullEdge(g, 0));
  EXPECT_FALSE(ocgl::isValidVertex(g, -1));
  EXPECT_FALSE(ocgl::isValidEdge(g, -1));
  EXPECT_TRUE(ocgl::isValidVertex(g, 0));
  EXPECT_TRUE(ocgl::isValidEdge(g, 0));
}

struct PointerVertex {};
struct PointerEdge {};

struct PointerGraph
{
  using Vertex = PointerVertex*;
  using Edge = PointerEdge*;
  using VertexIter = char;
  using EdgeIter = short;
  using IncidentIter = float;
  using AdjacentIter = double;

  static Vertex nullVertex()
  {
    return nullptr;
  }

  static Edge nullEdge()
  {
    return nullptr;
  }
};

TEST(GraphTraitsTest, PointerGraph)
{
  using Graph = PointerGraph;

  static_assert(!std::is_same<ocgl::GraphTraits<Graph>::Vertex, ocgl::GraphTraits<Graph>::Edge>::value, "");

  // check for correct associated types
  EXPECT_TRUE((std::is_same<Graph::Vertex, ocgl::GraphTraits<Graph>::Vertex>::value));
  EXPECT_TRUE((std::is_same<Graph::Edge, ocgl::GraphTraits<Graph>::Edge>::value));
  EXPECT_TRUE((std::is_same<Graph::VertexIter, ocgl::GraphTraits<Graph>::VertexIter>::value));
  EXPECT_TRUE((std::is_same<Graph::EdgeIter, ocgl::GraphTraits<Graph>::EdgeIter>::value));
  EXPECT_TRUE((std::is_same<Graph::IncidentIter, ocgl::GraphTraits<Graph>::IncidentIter>::value));
  EXPECT_TRUE((std::is_same<Graph::AdjacentIter, ocgl::GraphTraits<Graph>::AdjacentIter>::value));

  // test null
  EXPECT_EQ(nullptr, ocgl::GraphTraits<Graph>::nullVertex());
  EXPECT_EQ(nullptr, ocgl::GraphTraits<Graph>::nullEdge());

  // check isNull/isValid
  Graph g;
  EXPECT_TRUE(ocgl::isNullVertex(g, nullptr));
  EXPECT_TRUE(ocgl::isNullEdge(g, nullptr));
  EXPECT_FALSE(ocgl::isNullVertex(g, new PointerVertex));
  EXPECT_FALSE(ocgl::isNullEdge(g, new PointerEdge));
  EXPECT_FALSE(ocgl::isValidVertex(g, nullptr));
  EXPECT_FALSE(ocgl::isValidEdge(g, nullptr));
  EXPECT_TRUE(ocgl::isValidVertex(g, new PointerVertex));
  EXPECT_TRUE(ocgl::isValidEdge(g, new PointerEdge));
}

struct ObjectVertex
{
  bool null;

  bool operator==(const ObjectVertex &other) const
  {
    return null == other.null;
  }
};

struct ObjectEdge
{
  bool null;

  bool operator==(const ObjectEdge &other) const
  {
    return null == other.null;
  }
};

struct ObjectGraph
{
  using Vertex = ObjectVertex;
  using Edge = ObjectEdge;
  using VertexIter = char;
  using EdgeIter = short;
  using IncidentIter = float;
  using AdjacentIter = double;

  static Vertex nullVertex()
  {
    return ObjectVertex{true};
  }

  static Edge nullEdge()
  {
    return ObjectEdge{true};
  }
};


TEST(GraphTraitsTest, ObjectGraph)
{
  using Graph = ObjectGraph;

  static_assert(!std::is_same<ocgl::GraphTraits<Graph>::Vertex, ocgl::GraphTraits<Graph>::Edge>::value, "");

  // check for correct associated types
  EXPECT_TRUE((std::is_same<Graph::Vertex, ocgl::GraphTraits<Graph>::Vertex>::value));
  EXPECT_TRUE((std::is_same<Graph::Edge, ocgl::GraphTraits<Graph>::Edge>::value));
  EXPECT_TRUE((std::is_same<Graph::VertexIter, ocgl::GraphTraits<Graph>::VertexIter>::value));
  EXPECT_TRUE((std::is_same<Graph::EdgeIter, ocgl::GraphTraits<Graph>::EdgeIter>::value));
  EXPECT_TRUE((std::is_same<Graph::IncidentIter, ocgl::GraphTraits<Graph>::IncidentIter>::value));
  EXPECT_TRUE((std::is_same<Graph::AdjacentIter, ocgl::GraphTraits<Graph>::AdjacentIter>::value));

  // test null
  EXPECT_EQ(ObjectVertex{true}, ocgl::GraphTraits<Graph>::nullVertex());
  EXPECT_EQ(ObjectEdge{true}, ocgl::GraphTraits<Graph>::nullEdge());

  // check isNull/isValid
  Graph g;
  EXPECT_TRUE(ocgl::isNullVertex(g, ObjectVertex{true}));
  EXPECT_TRUE(ocgl::isNullEdge(g, ObjectEdge{true}));
  EXPECT_FALSE(ocgl::isNullVertex(g, ObjectVertex{false}));
  EXPECT_FALSE(ocgl::isNullEdge(g, ObjectEdge{false}));
  EXPECT_FALSE(ocgl::isValidVertex(g, ObjectVertex{true}));
  EXPECT_FALSE(ocgl::isValidEdge(g, ObjectEdge{true}));
  EXPECT_TRUE(ocgl::isValidVertex(g, ObjectVertex{false}));
  EXPECT_TRUE(ocgl::isValidEdge(g, ObjectEdge{false}));
}

using GraphModels = ::testing::Types<IdGraph, PointerGraph, ObjectGraph>;

template<typename T> class Tag2TypeTest : public ::testing::Test {};

TYPED_TEST_CASE(Tag2TypeTest, GraphModels);

TYPED_TEST(Tag2TypeTest, Main)
{
  using Graph = TypeParam;

  using Vertex = typename ocgl::GraphTraits<Graph>::Vertex;
  using Edge = typename ocgl::GraphTraits<Graph>::Edge;

  // VertexTag -> typename GraphTraits<Graph>::Vertex
  static_assert(std::is_same<Vertex, typename ocgl::impl::Tag2Type<Graph, ocgl::impl::VertexTag>::Type>::value, "");
  // EdgeTag -> typename GraphTraits<Graph>::Edge
  static_assert(std::is_same<Edge, typename ocgl::impl::Tag2Type<Graph, ocgl::impl::EdgeTag>::Type>::value, "");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

