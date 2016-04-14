set(OCGL_HDRS
  Unused.h
  Contract.h
  Range.h
  GraphTraits.h
  Predicates.h
  AdjacentIterator.h
  FilterIterator.h
  PropertyMap.h
  GraphStringParser.h
  BitMatrix.h
  Path.h
  Cycle.h
  CycleSpace.h
  Subgraph.h

  predicate/HasProperty.h
  predicate/HasIndex.h
  predicate/HasDegree.h

  #model/PointerGraph.h
  #model/IdGraph.h
  #model/ObjectGraph.h
  model/IndexGraph.h

  algorithm/DFS.h
  algorithm/ConnectedComponents.h
  algorithm/Dijkstra.h
  algorithm/CycleMembership.h
  algorithm/RelevantCycles.h
  algorithm/Backtrack.h
  algorithm/VF2State.h
  algorithm/Isomorphisms.h
)

copy_headers("${OCGL_HDRS}" ocgl)
