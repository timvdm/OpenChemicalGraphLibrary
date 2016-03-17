#include <ocgl/algorithm/DFS.h>
#include <ocgl/GraphStringParser.h>

#include <ocgl/model/PointerGraph.h>
#include <ocgl/model/IdGraph.h>
#include <ocgl/model/ObjectGraph.h>

#include <gtest/gtest.h>

using GraphModels = ::testing::Types<
  ocgl::model::PointerGraph,
  ocgl::model::IdGraph,
  ocgl::model::ObjectGraph
>;

template<typename T> class DFSTest : public ::testing::Test {};

TYPED_TEST_CASE(DFSTest, GraphModels);

template<typename Graph>
struct DFSVisitor : public ocgl::algorithm::DFSVisitor<Graph>
{
  using Vertex = typename ocgl::GraphTraits<Graph>::Vertex;
  using Edge = typename ocgl::GraphTraits<Graph>::Edge;

  DFSVisitor(std::ostream &os_) : os(os_)
  {
  }

  void initialize(const Graph &graph)
  {
    os << "initialize()" << std::endl;
  }

  void component(const Graph &g, int i)
  {
    os << "component(" << i << ")" << std::endl;
  }

  void vertex(const Graph &g, Vertex v)
  {
    os << "vertex(" << ocgl::getId(g, v) << ")" << std::endl;
  }

  void edge(const Graph &g, Edge e)
  {
    os << "edge(" << ocgl::getId(g, e) << ")" << std::endl;
  }

  void backEdge(const Graph &g, Edge e)
  {
    os << "backEdge(" << ocgl::getId(g, e) << ")" << std::endl;
  }

  void finishEdge(const Graph &g, Edge e)
  {
    os << "finishEdge(" << ocgl::getId(g, e) << ")" << std::endl;
  }

  void finishVertex(const Graph &g, Vertex v)
  {
    os << "finishVertex(" << ocgl::getId(g, v) << ")" << std::endl;
  }

  std::ostream &os;
};


template<typename Graph>
std::string dfsTraceGraph(const std::string &str)
{
  auto g = ocgl::GraphStringParser<Graph>::parse(str);

  std::stringstream ss;
  DFSVisitor<Graph> visitor(ss);

  ocgl::algorithm::dfs(g, visitor);

  return ss.str();
}

template<typename Graph>
std::string dfsTraceComponent(const std::string &str, unsigned int vertexIndex)
{
  auto g = ocgl::GraphStringParser<Graph>::parse(str);

  std::stringstream ss;
  DFSVisitor<Graph> visitor(ss);

  auto V = ocgl::getVertices(g).toVector();

  ocgl::algorithm::dfs(g, V[vertexIndex], visitor);

  return ss.str();
}

TYPED_TEST(DFSTest, Chain)
{
  auto trace = dfsTraceGraph<TypeParam>("****");

  std::stringstream correct;
  correct << "initialize()" << std::endl
          << "component(0)" << std::endl
          << "vertex(0)" << std::endl
          << "edge(0)" << std::endl
          << "vertex(1)" << std::endl
          << "edge(1)" << std::endl
          << "vertex(2)" << std::endl
          << "edge(2)" << std::endl
          << "vertex(3)" << std::endl
          << "finishVertex(3)" << std::endl
          << "finishEdge(2)" << std::endl
          << "finishVertex(2)" << std::endl
          << "finishEdge(1)" << std::endl
          << "finishVertex(1)" << std::endl
          << "finishEdge(0)" << std::endl
          << "finishVertex(0)" << std::endl;

  EXPECT_EQ(correct.str(), trace);
}

TYPED_TEST(DFSTest, Components)
{
  auto trace = dfsTraceGraph<TypeParam>("**.**");

  std::stringstream correct;
  correct << "initialize()" << std::endl
          << "component(0)" << std::endl
          << "vertex(0)" << std::endl
          << "edge(0)" << std::endl
          << "vertex(1)" << std::endl
          << "finishVertex(1)" << std::endl
          << "finishEdge(0)" << std::endl
          << "finishVertex(0)" << std::endl
          << "component(1)" << std::endl
          << "vertex(2)" << std::endl
          << "edge(1)" << std::endl
          << "vertex(3)" << std::endl
          << "finishVertex(3)" << std::endl
          << "finishEdge(1)" << std::endl
          << "finishVertex(2)" << std::endl;

  EXPECT_EQ(correct.str(), trace);
}

TYPED_TEST(DFSTest, Cycle)
{
  auto trace = dfsTraceGraph<TypeParam>("*1***1");

  std::stringstream correct;
  correct << "initialize()" << std::endl
          << "component(0)" << std::endl
          << "vertex(0)" << std::endl
          << "edge(0)" << std::endl
          << "vertex(1)" << std::endl
          << "edge(1)" << std::endl
          << "vertex(2)" << std::endl
          << "edge(2)" << std::endl
          << "vertex(3)" << std::endl
          << "backEdge(3)" << std::endl
          << "finishVertex(3)" << std::endl
          << "finishEdge(2)" << std::endl
          << "finishVertex(2)" << std::endl
          << "finishEdge(1)" << std::endl
          << "finishVertex(1)" << std::endl
          << "finishEdge(0)" << std::endl
          << "finishVertex(0)" << std::endl;

  EXPECT_EQ(correct.str(), trace);
}

TYPED_TEST(DFSTest, SingleComponent)
{
  auto trace = dfsTraceComponent<TypeParam>("**.**", 2);

  std::stringstream correct;
  correct << "initialize()" << std::endl
          << "vertex(2)" << std::endl
          << "edge(1)" << std::endl
          << "vertex(3)" << std::endl
          << "finishVertex(3)" << std::endl
          << "finishEdge(1)" << std::endl
          << "finishVertex(2)" << std::endl;

  EXPECT_EQ(correct.str(), trace);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

