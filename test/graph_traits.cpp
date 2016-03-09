#include <ocgl/graph_traits.h>

#include <gtest/gtest.h>

struct index_graph
{
  using vertex = int;
  using edge = int;
  using vertex_iter = char;
  using edge_iter = short;
  using incident_iter = float;
  using adjacent_iter = double;

  static vertex null_vertex()
  {
    return -1;
  }

  static edge null_edge()
  {
    return -1;
  }
};

TEST(graph_traits_test, index_graph)
{
  using Graph = index_graph;

  // check for correct associated types
  EXPECT_TRUE((std::is_same<Graph::vertex, ocgl::graph_traits<Graph>::vertex>::value));
  EXPECT_TRUE((std::is_same<Graph::edge, ocgl::graph_traits<Graph>::edge>::value));
  EXPECT_TRUE((std::is_same<Graph::vertex_iter, ocgl::graph_traits<Graph>::vertex_iter>::value));
  EXPECT_TRUE((std::is_same<Graph::edge_iter, ocgl::graph_traits<Graph>::edge_iter>::value));
  EXPECT_TRUE((std::is_same<Graph::incident_iter, ocgl::graph_traits<Graph>::incident_iter>::value));
  EXPECT_TRUE((std::is_same<Graph::adjacent_iter, ocgl::graph_traits<Graph>::adjacent_iter>::value));

  // test null_vertex() and null_edge() explicitly
  EXPECT_EQ(-1, ocgl::graph_traits<Graph>::null_vertex());
  EXPECT_EQ(-1, ocgl::graph_traits<Graph>::null_edge());

  // check is_null/is_valid
  Graph g;
  EXPECT_TRUE(ocgl::is_null(g, -1));
  EXPECT_FALSE(ocgl::is_null(g, 0));
  EXPECT_FALSE(ocgl::is_valid(g, -1));
  EXPECT_TRUE(ocgl::is_valid(g, 0));
}

struct pointer_vertex {};
struct pointer_edge {};

struct pointer_graph
{
  using vertex = pointer_vertex*;
  using edge = pointer_edge*;
  using vertex_iter = char;
  using edge_iter = short;
  using incident_iter = float;
  using adjacent_iter = double;

  static vertex null_vertex()
  {
    return nullptr;
  }

  static edge null_edge()
  {
    return nullptr;
  }
};

TEST(graph_traits_test, pointer_graph)
{
  using Graph = pointer_graph;

  static_assert(!std::is_same<ocgl::graph_traits<Graph>::vertex, ocgl::graph_traits<Graph>::edge>::value, "");

  // check for correct associated types
  EXPECT_TRUE((std::is_same<Graph::vertex, ocgl::graph_traits<Graph>::vertex>::value));
  EXPECT_TRUE((std::is_same<Graph::edge, ocgl::graph_traits<Graph>::edge>::value));
  EXPECT_TRUE((std::is_same<Graph::vertex_iter, ocgl::graph_traits<Graph>::vertex_iter>::value));
  EXPECT_TRUE((std::is_same<Graph::edge_iter, ocgl::graph_traits<Graph>::edge_iter>::value));
  EXPECT_TRUE((std::is_same<Graph::incident_iter, ocgl::graph_traits<Graph>::incident_iter>::value));
  EXPECT_TRUE((std::is_same<Graph::adjacent_iter, ocgl::graph_traits<Graph>::adjacent_iter>::value));

  // test null_vertex() and null_edge() explicitly
  EXPECT_EQ(nullptr, ocgl::graph_traits<Graph>::null_vertex());
  EXPECT_EQ(nullptr, ocgl::graph_traits<Graph>::null_edge());

  // check is_null/is_valid
  Graph g;
  EXPECT_TRUE(ocgl::is_null(g, nullptr));
  EXPECT_FALSE(ocgl::is_null(g, new pointer_vertex));
  EXPECT_FALSE(ocgl::is_null(g, new pointer_edge));
  EXPECT_FALSE(ocgl::is_valid(g, nullptr));
  EXPECT_TRUE(ocgl::is_valid(g, new pointer_vertex));
  EXPECT_TRUE(ocgl::is_valid(g, new pointer_edge));
}

struct object_vertex
{
  bool null;

  bool operator==(const object_vertex &other) const
  {
    return null == other.null;
  }
};

struct object_edge
{
  bool null;

  bool operator==(const object_edge &other) const
  {
    return null == other.null;
  }
};

struct object_graph
{
  using vertex = object_vertex;
  using edge = object_edge;
  using vertex_iter = char;
  using edge_iter = short;
  using incident_iter = float;
  using adjacent_iter = double;

  static vertex null_vertex()
  {
    return object_vertex{true};
  }

  static edge null_edge()
  {
    return object_edge{true};
  }
};

TEST(graph_traits_test, object_graph)
{
  using Graph = object_graph;

  static_assert(!std::is_same<ocgl::graph_traits<Graph>::vertex, ocgl::graph_traits<Graph>::edge>::value, "");

  // check for correct associated types
  EXPECT_TRUE((std::is_same<Graph::vertex, ocgl::graph_traits<Graph>::vertex>::value));
  EXPECT_TRUE((std::is_same<Graph::edge, ocgl::graph_traits<Graph>::edge>::value));
  EXPECT_TRUE((std::is_same<Graph::vertex_iter, ocgl::graph_traits<Graph>::vertex_iter>::value));
  EXPECT_TRUE((std::is_same<Graph::edge_iter, ocgl::graph_traits<Graph>::edge_iter>::value));
  EXPECT_TRUE((std::is_same<Graph::incident_iter, ocgl::graph_traits<Graph>::incident_iter>::value));
  EXPECT_TRUE((std::is_same<Graph::adjacent_iter, ocgl::graph_traits<Graph>::adjacent_iter>::value));

  // test null_vertex() and null_edge() explicitly
  EXPECT_EQ(object_vertex{true}, ocgl::graph_traits<Graph>::null_vertex());
  EXPECT_EQ(object_edge{true}, ocgl::graph_traits<Graph>::null_edge());

  // check is_null/is_valid
  Graph g;
  EXPECT_TRUE(ocgl::is_null(g, object_vertex{true}));
  EXPECT_TRUE(ocgl::is_null(g, object_edge{true}));
  EXPECT_FALSE(ocgl::is_null(g, object_vertex{false}));
  EXPECT_FALSE(ocgl::is_null(g, object_edge{false}));
  EXPECT_FALSE(ocgl::is_valid(g, object_vertex{true}));
  EXPECT_FALSE(ocgl::is_valid(g, object_edge{true}));
  EXPECT_TRUE(ocgl::is_valid(g, object_vertex{false}));
  EXPECT_TRUE(ocgl::is_valid(g, object_edge{false}));
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

