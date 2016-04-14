#include <ocgl/algorithm/Isomorphisms.h>

#include "../test.h"

GRAPH_TYPED_TEST(IsomorphismsTest);

/*
std::ostream& operator<<(std::ostream &os, const Mapping<AdjListGraph, AdjListGraph> &mapping)
{
  for (Size i = 0; i < mapping.size(); ++i)
    os << mapping.queryMap()[i] << " ";
  return os;
}
*/

template<typename Graph>
int countIsomorphisms(const std::string &queryGS, const std::string &graphGS)
{
  auto query = ocgl::GraphStringParser<Graph>::parse(queryGS);
  auto graph = ocgl::GraphStringParser<Graph>::parse(graphGS);

  int count = 0;
  auto visitor = [&count] (const ocgl::VertexPropertyMap<Graph, typename ocgl::GraphTraits<Graph>::Vertex>&) -> bool { ++count; return false; };

  ocgl::algorithm::isomorphisms(query, graph, visitor);

  return count;
}

template<typename Graph>
int countIsomorphisms(const std::string &graphGS)
{
  return countIsomorphisms<Graph>(graphGS, graphGS);
}

TYPED_TEST(IsomorphismsTest, CountIsomorphisms)
{
  EXPECT_EQ(1, countIsomorphisms<TypeParam>("*", "*"));
  EXPECT_EQ(2, countIsomorphisms<TypeParam>("*", "**"));
  EXPECT_EQ(3, countIsomorphisms<TypeParam>("*", "***"));
  
  EXPECT_EQ(2, countIsomorphisms<TypeParam>("**", "**"));
  EXPECT_EQ(4, countIsomorphisms<TypeParam>("**", "***"));
  EXPECT_EQ(6, countIsomorphisms<TypeParam>("**", "*1**1"));

  EXPECT_EQ(6, countIsomorphisms<TypeParam>("**(*)*", "**(*)*"));
  EXPECT_EQ(24, countIsomorphisms<TypeParam>("**(*)*", "**(*)(*)*"));

  EXPECT_EQ(8, countIsomorphisms<TypeParam>("*1***1", "*1***1"));
  EXPECT_EQ(8, countIsomorphisms<TypeParam>("*1**1*2**2", "*1**1*2**2"));
  EXPECT_EQ(12, countIsomorphisms<TypeParam>("****", "*1***1*"));

  EXPECT_EQ(2, countIsomorphisms<TypeParam>("*.*", "**"));
  EXPECT_EQ(6, countIsomorphisms<TypeParam>("*.*", "***"));
  EXPECT_EQ(4, countIsomorphisms<TypeParam>("**.*", "***"));
  
  EXPECT_EQ(0, countIsomorphisms<TypeParam>("*", ""));
  EXPECT_EQ(0, countIsomorphisms<TypeParam>("**", "*"));
  EXPECT_EQ(0, countIsomorphisms<TypeParam>("**", "*.*"));
  EXPECT_EQ(0, countIsomorphisms<TypeParam>("*1***1", "****"));
  
  EXPECT_EQ(0, countIsomorphisms<TypeParam>("*.*", "*"));
  EXPECT_EQ(0, countIsomorphisms<TypeParam>("**.*", "**"));
  EXPECT_EQ(0, countIsomorphisms<TypeParam>("**.**", "***"));

  EXPECT_EQ(200, countIsomorphisms<TypeParam>("*1****1.*.*1****1"));
  EXPECT_EQ(200, countIsomorphisms<TypeParam>("*12*3*4*5*16.*2345623456.*12*3*4*5*16"));
}





int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
