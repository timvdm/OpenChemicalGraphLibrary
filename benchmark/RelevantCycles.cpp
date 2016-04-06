#include <benchmark/benchmark.h>

#include <ocgl/algorithm/RelevantCycles.h>
#include <ocgl/GraphStringParser.h>
#include <ocgl/model/IndexGraph.h>

#include "nanotube_6n_6m_20A.h"
#include "nanotube_6n_6m_40A.h"
#include "nanotube_6n_6m_60A.h"
#include "nanotube_6n_6m_80A.h"

#include "nanotube_9n_9m_20A.h"
#include "nanotube_9n_9m_40A.h"
#include "nanotube_9n_9m_60A.h"
#include "nanotube_9n_9m_80A.h"

#include "pdb_2r4s.h"

#define RELEVANT_CYCLES_BENCHMARK(function, name) \
  template<typename Graph> \
  static void function##_##name(benchmark::State& state) \
  { \
    auto g = name<Graph>(); \
    while (state.KeepRunning()) \
      ocgl::algorithm::function(g); \
  } \
  BENCHMARK_TEMPLATE(function##_##name, ocgl::model::IndexGraph);

/*
RELEVANT_CYCLES_BENCHMARK(relevantCycles, nanotube_6n_6m_20A);
RELEVANT_CYCLES_BENCHMARK(relevantCycles, nanotube_6n_6m_40A);
RELEVANT_CYCLES_BENCHMARK(relevantCycles, nanotube_6n_6m_60A);
RELEVANT_CYCLES_BENCHMARK(relevantCycles, nanotube_6n_6m_80A);

RELEVANT_CYCLES_BENCHMARK(relevantCycles, nanotube_9n_9m_20A);
RELEVANT_CYCLES_BENCHMARK(relevantCycles, nanotube_9n_9m_40A);
RELEVANT_CYCLES_BENCHMARK(relevantCycles, nanotube_9n_9m_60A);
RELEVANT_CYCLES_BENCHMARK(relevantCycles, nanotube_9n_9m_80A);
*/

RELEVANT_CYCLES_BENCHMARK(relevantCycles, pdb_2r4s);
RELEVANT_CYCLES_BENCHMARK(relevantCyclesSubgraphs, pdb_2r4s);

BENCHMARK_MAIN();
