#include <ocgl/GraphStringParser.h>

//#include <ocgl/model/PointerGraph.h>
//#include <ocgl/model/IdGraph.h>
//#include <ocgl/model/ObjectGraph.h>
#include <ocgl/model/IndexGraph.h>

#include <gtest/gtest.h>

using GraphModels = ::testing::Types<
//  ocgl::model::PointerGraph,
//  ocgl::model::IdGraph,
//  ocgl::model::ObjectGraph
    ocgl::model::IndexGraph
>;

#define GRAPH_TYPED_TEST(name) \
  template<typename T> class name : public ::testing::Test {}; \
  TYPED_TEST_CASE(name, GraphModels);

