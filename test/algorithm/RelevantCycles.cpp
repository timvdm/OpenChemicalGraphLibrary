#include <ocgl/algorithm/RelevantCycles.h>

#include "../test.h"

GRAPH_TYPED_TEST(RelevantCyclesTest);

struct TestCycle
{
  TestCycle(std::initializer_list<unsigned int> edges_)
    : edges(edges_)
  {
  }

  std::vector<unsigned int> edges;
};

std::ostream& operator<<(std::ostream &os, const TestCycle &cycle)
{
  os << "Cycle [ ";
  for (auto e : cycle.edges)
    os << e << " ";
  os << "]";
  return os;
}

template<typename Graph>
bool isSameCycle(const Graph &g, const TestCycle &testCycle,
    const std::vector<typename ocgl::GraphTraits<Graph>::Vertex> &cycle)
{
  if (testCycle.edges.size() != cycle.size())
    return false;

  auto edgeCycle = ocgl::edgeCycleFromVertexCycle(g, cycle);

  for (auto e : edgeCycle)
    if (std::find(testCycle.edges.begin(), testCycle.edges.end(), e) == testCycle.edges.end())
      return false;

  return true;
}

template<typename Graph>
bool testRelevantCycles(const std::string &str, std::initializer_list<TestCycle> testCycles)
{
  auto g = ocgl::GraphStringParser<Graph>::parse(str);
  auto cycles = ocgl::algorithm::relevantCycles(g);

  std::cout << "# test cycles: " << testCycles.size() << std::endl;
  std::cout << "# relevant cycles: " << cycles.size() << std::endl;

  std::cout << "test cycles:" << std::endl;
  for (auto &cycle : testCycles)
    std::cout << "    " << cycle << std::endl;

  std::cout << "relevant cycles:" << std::endl;
  for (auto &cycle : cycles) {
    std::cout << "    Cycle [ ";
    for (auto e : cycle)
      std::cout << ocgl::getIndex(g, e) << " ";
    std::cout << "]" << std::endl;
  }

  if (testCycles.size() != cycles.size())
    return false;

  for (auto &testCycle : testCycles) {
    bool found = false;
    for (auto &cycle : cycles)
      if (isSameCycle(g, testCycle, cycle))
        found = true;

    if (!found) {
      std::cout << "not found: " << testCycle << std::endl;
      return false;
    }
  }

  return true;
}


TYPED_TEST(RelevantCyclesTest, Figueras1)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*1*****1", {
        TestCycle({0, 1, 2, 3, 4, 5})
  }));
}
  
TYPED_TEST(RelevantCyclesTest, Figueras2)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*1**2***3*4****4***3*2**1", {
        TestCycle({0, 1, 16, 17, 18, 19}),
        TestCycle({2, 3, 4, 14, 15, 16}),
        TestCycle({5, 10, 11, 12, 13, 14}),
        TestCycle({6, 7, 8, 9, 10})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras3)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*1**2***3***4***5***6***1*7*6*5*4*3*27", {
        TestCycle({0, 1, 17, 18, 28, 29}),
        TestCycle({2, 3, 4, 26, 27, 28}),
        TestCycle({5, 6, 7, 24, 25, 26}),
        TestCycle({8, 9, 10, 22, 23, 24}),
        TestCycle({11, 12, 13, 20, 21, 22}),
        TestCycle({14, 15, 16, 18, 19, 20}),
        TestCycle({19, 21, 23, 25, 27, 29})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras4)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*12***(*2)**1", {
        TestCycle({0, 1, 2, 3, 4}),
        TestCycle({3, 4, 5, 6, 7})
  }));
}
  
TYPED_TEST(RelevantCyclesTest, Figueras5)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*123***(**2)(**3)**1", {
        TestCycle({0, 1, 2, 3, 4, 5}),
        TestCycle({0, 1, 2, 6, 7, 8}),
        TestCycle({0, 1, 2, 9, 10, 11}),
        TestCycle({3, 4, 5, 6, 7, 8}),
        TestCycle({3, 4, 5, 9, 10, 11}),
        TestCycle({6, 7, 8, 9, 10, 11})
  }));
}



TYPED_TEST(RelevantCyclesTest, Figueras6)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*1*****1***2*****2", {
        TestCycle({0, 1, 2, 3, 4, 5}),
        TestCycle({9, 10, 11, 12, 13, 14})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras7)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*1*(*2)*3*(*4)*5*(**6)***6*5*4*3*2*1", {
      TestCycle({0, 1, 20, 21, 22}),
      TestCycle({1, 2, 18, 19, 20}),
      TestCycle({3, 4, 16, 17, 18}),
      TestCycle({4, 5, 14, 15, 16}),
      TestCycle({6, 7, 8, 12, 13, 14}),
      TestCycle({6, 9, 10, 11, 13, 14}),
      TestCycle({7, 8, 9, 10, 11, 12})
  }));
}


TYPED_TEST(RelevantCyclesTest, Figueras8)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*12***(*1)***2", {
        TestCycle({0, 1, 2, 3, 4}),
        TestCycle({3, 4, 5, 6, 7, 8})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras9)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*12***(**1)****2", {
        TestCycle({0, 1, 2, 3, 4, 5}),
        TestCycle({3, 4, 5, 6, 7, 8, 9, 10}),
        TestCycle({0, 1, 2, 6, 7, 8, 9, 10})
  }));
}


TYPED_TEST(RelevantCyclesTest, Figueras10)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*12***(*3**1)*3**2", {
        TestCycle({0, 1, 2, 7, 9, 10, 11}),
        TestCycle({3, 7, 8}),
        TestCycle({4, 5, 6, 8, 9, 10, 11}),
        TestCycle({0, 1, 2, 3, 4, 5, 6})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras11)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*1*2*3****3*(*2)**1", {
        TestCycle({0, 8, 9, 10, 11, 12}),
        TestCycle({1, 6, 7, 8, 9}),
        TestCycle({2, 3, 4, 5, 6})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras12)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*1***2*3****(**4)*3**2*41", {
        TestCycle({0, 1, 2, 14, 15, 17}),
        TestCycle({3, 11, 12, 13, 14}),
        TestCycle({4, 5, 6, 7, 10, 11}),
        TestCycle({8, 9, 10, 12, 13, 15, 16})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras13)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*1*23**34**421", {
        TestCycle({0, 7, 8}),
        TestCycle({1, 2, 3}),
        TestCycle({3, 6, 7}),
        TestCycle({4, 5, 6})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras14)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*17*2*3*4*5*1*6*5*4*3*2*67", {
        TestCycle({0, 1, 2, 3, 4, 5}),
        TestCycle({7, 9, 11, 13, 15, 16}),
        TestCycle({0, 14, 15, 17}),
        TestCycle({1, 12, 13, 14}),
        TestCycle({2, 10, 11, 12}),
        TestCycle({3, 8, 9, 10}),
        TestCycle({4, 6, 7, 8}),
        TestCycle({5, 6, 16, 17})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras15)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*12*3*4*1*5*4*3*25", {
        TestCycle({0, 8, 9, 10}),
        TestCycle({1, 6, 7, 8}),
        TestCycle({2, 4, 5, 6}),
        TestCycle({3, 4, 10, 11}),
        TestCycle({0, 1, 2, 3}),
        TestCycle({5, 7, 9, 11})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras16)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*12*3*4*5*6*1*27*65*437", {
        TestCycle({0, 7, 13, 14}),
        TestCycle({1, 12, 13}),
        TestCycle({2, 10, 11, 12}),
        TestCycle({3, 9, 10}),
        TestCycle({4, 6, 8, 9}),
        TestCycle({5, 6, 7}),
        TestCycle({8, 11, 14})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras17)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*12*3*4*5*6*1*2*(*65)*43", {
        TestCycle({0, 7, 8, 12, 14}),
        TestCycle({2, 9, 11, 12, 13}),
        TestCycle({4, 6, 8, 9, 10}),
        TestCycle({1, 13, 14}),
        TestCycle({3, 10, 11}),
        TestCycle({5, 6, 7})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras18)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*12*3*4*1*56*47****37*25***6", {
        TestCycle({0, 11, 13, 14}),
        TestCycle({1, 6, 11, 12}),
        TestCycle({2, 4, 5, 6}),
        TestCycle({3, 4, 14, 15}),
        TestCycle({0, 1, 2, 3}),
        TestCycle({5, 12, 13, 15}),
        TestCycle({7, 8, 9, 10, 12}),
        TestCycle({15, 16, 17, 18, 19})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras19)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*1**2**3****(*4)*3*5*2*6*1**7*8*6*9*5*4***9**8***7", {
      TestCycle({0, 1, 13, 14, 15, 16}),
      TestCycle({2, 3, 10, 11, 12, 13}),
      TestCycle({4, 5, 6, 7, 9, 10}),
      TestCycle({8, 9, 11, 24, 25, 26}),
      TestCycle({12, 14, 21, 22, 23, 24}),
      TestCycle({15, 17, 18, 19, 20, 21}),
      TestCycle({19, 33, 34, 35, 36, 37}),
      TestCycle({20, 22, 30, 31, 32, 33}),
      TestCycle({23, 25, 27, 28, 29, 30})
  }));
}

TYPED_TEST(RelevantCyclesTest, Figueras20)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*1*2*3*4**5*46*37*28*1**8*7*6*5", {
        TestCycle({0, 10, 11, 12}),
        TestCycle({1, 8, 9, 10}),
        TestCycle({2, 6, 7, 8}),
        TestCycle({3, 4, 5, 6}),
        TestCycle({5, 19, 20, 21}),
        TestCycle({7, 17, 18, 19}),
        TestCycle({9, 15, 16, 17}),
        TestCycle({11, 13, 14, 15})
  }));
}

TYPED_TEST(RelevantCyclesTest, VismaraPage7)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*1*(**2)***2****(**3)***31", {
      TestCycle({1, 2, 3, 4, 5, 6}),
      TestCycle({11, 12, 13, 14, 15, 16}),
      TestCycle({0, 1, 2, 6, 7, 8, 9, 10, 11, 12, 16, 17}),
      TestCycle({0, 1, 2, 6, 7, 8, 9, 10, 13, 14, 15, 17}),
      TestCycle({0, 3, 4, 5, 7, 8, 9, 10, 11, 12, 16, 17}),
      TestCycle({0, 3, 4, 5, 7, 8, 9, 10, 13, 14, 15, 17})
  }));
}


TYPED_TEST(RelevantCyclesTest, HortonFig1)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
        "*123*45*67*18*69*741*52*1983", {
        TestCycle({0, 10, 11}),
        TestCycle({8, 9, 10}),
        TestCycle({1, 7, 8}),
        TestCycle({5, 6, 7}),
        TestCycle({2, 4, 5}),
        TestCycle({4, 14, 15}),
        TestCycle({3, 15, 16}),
        TestCycle({11, 12, 16}),
        TestCycle({9, 12, 13}),
        TestCycle({6, 13, 14})
  }));
}


TYPED_TEST(RelevantCyclesTest, BergerFig2a)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*1*23**24**45**531", {
      TestCycle({0, 10, 11}),
      TestCycle({1, 2, 3}),
      TestCycle({4, 5, 6}),
      TestCycle({7, 8, 9}),
      TestCycle({3, 6, 9, 10})
  }));
}

TYPED_TEST(RelevantCyclesTest, BergerFig2b)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*1*23*45**67*18*69*74*52*389", {
      TestCycle({0, 5, 15, 16}),
      TestCycle({1, 12, 13}),
      TestCycle({2, 3, 9, 10}),
      TestCycle({4, 6, 7}),
      TestCycle({7, 8, 9}),
      TestCycle({10, 11, 12}),
      TestCycle({13, 14, 15}),
      TestCycle({6, 16, 17}),
      TestCycle({8, 11, 14, 17})
  }));
}

TYPED_TEST(RelevantCyclesTest, BergerFig4a)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*1*23*4*5*16*7*2*8*7*6*5*4*38", {
      TestCycle({0, 1, 2, 3, 4}),
      TestCycle({0, 4, 5, 6, 7}),
      TestCycle({1, 16, 17, 18}),
      TestCycle({2, 14, 15, 16}),
      TestCycle({3, 12, 13, 14}),
      TestCycle({5, 10, 11, 12}),
      TestCycle({6, 8, 9, 10}),
      TestCycle({7, 8, 18, 19})
  }));
}

/*
TYPED_TEST(RelevantCyclesTest, BergerFig4b)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*1*234*56*78*19%10*%11%12*2%13*%11%14*%129*%107*85*63*4%13%14", {
      TestCycle({0, 1, 2, 3, 4}),
      TestCycle({0, 4, 5, 6, 7}),
      TestCycle({1, 20, 21}),
      TestCycle({21, 22, 23}),
      TestCycle({2, 17, 18}),
      TestCycle({18, 19, 20}),
      TestCycle({3, 14, 15}),
      TestCycle({15, 16, 17}),
      TestCycle({5, 11, 12}),
      TestCycle({12, 13, 14}),
      TestCycle({6, 8, 9}),
      TestCycle({9, 10, 11}),
      TestCycle({7, 23, 24}),
      TestCycle({8, 24, 25})
  }));
}
*/

TYPED_TEST(RelevantCyclesTest, BergerFig5a)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*12*34*1*25*6*5*67*3*74", {
      TestCycle({0, 1, 2}),
      TestCycle({2, 3, 4}),
      TestCycle({5, 6, 7}),
      TestCycle({6, 8, 9}),
      TestCycle({10, 12, 13}),
      TestCycle({11, 12, 14}),
      TestCycle({0, 4, 5, 9, 13, 14}),
      TestCycle({0, 4, 5, 9, 10, 11}),
      TestCycle({0, 4, 7, 8, 13, 14}),
      TestCycle({0, 4, 7, 8, 10, 11}),
      TestCycle({1, 3, 5, 9, 13, 14}),
      TestCycle({1, 3, 5, 9, 10, 11}),
      TestCycle({1, 3, 7, 8, 13, 14}),
      TestCycle({1, 3, 7, 8, 10, 11})
  }));
}

TYPED_TEST(RelevantCyclesTest, BergerFig5b)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*123*4*1**45*6*5*67*2*73", {
      TestCycle({0, 1, 2}),
      TestCycle({1, 3, 4, 5}),
      TestCycle({6, 7, 8}),
      TestCycle({7, 9, 10}),
      TestCycle({11, 13, 14}),
      TestCycle({12, 13, 15}),
      TestCycle({0, 5, 8, 9, 11, 12}),
      TestCycle({0, 5, 8, 9, 14, 15}),
      TestCycle({0, 5, 6, 10, 11, 12}),
      TestCycle({0, 5, 6, 10, 14, 15})
  }));
}

TYPED_TEST(RelevantCyclesTest, BergerFig7a)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*12***3*1***32", {
      TestCycle({3, 4, 8, 9}),
      TestCycle({0, 1, 2, 3, 4}),
      TestCycle({0, 1, 2, 8, 9}),
      TestCycle({3, 5, 6, 7, 8}),
      TestCycle({4, 5, 6, 7, 9})
  }));
}

TYPED_TEST(RelevantCyclesTest, BergerFig7b)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*12**3**4**(*1)*56*47*38*25*9**8**7**6*9", {
      TestCycle({0, 1, 12, 13, 14}),
      TestCycle({2, 3, 10, 11, 12}),
      TestCycle({4, 5, 8, 9, 10}),
      TestCycle({6, 7, 8, 14, 15}),
      TestCycle({9, 22, 23, 24, 25}),
      TestCycle({11, 19, 20, 21, 22}),
      TestCycle({13, 16, 17, 18, 19}),
      TestCycle({15, 16, 25, 26, 27}),
      TestCycle({9, 11, 13, 15})
  }));
}

TYPED_TEST(RelevantCyclesTest, BergerFig8a)
{
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*12*3*4**5**6**1*7*6*5*4**3**2*7", {
      TestCycle({0, 18, 19, 20, 21}),
      TestCycle({1, 15, 16, 17, 18}),
      TestCycle({2, 3, 13, 14, 15}),
      TestCycle({4, 5, 11, 12, 13}),
      TestCycle({6, 7, 9, 10, 11}),
      TestCycle({8, 9, 21, 22, 23}),
      TestCycle({0, 1, 8, 9, 10, 12, 14, 15})
  }));
}

TYPED_TEST(RelevantCyclesTest, BergerFig8b)
{
  // tests isCycleSetComplete
  EXPECT_TRUE(testRelevantCycles<TypeParam>(
      "*12****3*4*1*56**47**38**2(*5)*876", {
      TestCycle({0, 1, 2, 3, 4, 5, 6}),
      TestCycle({4, 10, 11, 12, 13}),
      TestCycle({4, 10, 13, 20, 21}),
      TestCycle({5, 7, 8, 9, 10}),
      TestCycle({5, 7, 10, 21, 22}),
      TestCycle({6, 7, 16, 17, 18}),
      TestCycle({6, 7, 16, 19, 22}),
      TestCycle({8, 9, 21, 22}),
      TestCycle({11, 12, 20, 21}),
      TestCycle({14, 15, 19, 20}),
      TestCycle({17, 18, 19, 22})
  }));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

