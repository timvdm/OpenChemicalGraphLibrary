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
)

set(OCGL_PREDICATE_HDRS
  predicate/HasProperty.h
  predicate/HasIndex.h
  predicate/HasDegree.h
)

set(OCGL_MODEL_HDRS
  #PointerGraph.h
  #IdGraph.h
  #ObjectGraph.h
  model/IndexGraph.h
)

set(OCGL_ALGORITHM_HDRS
  algorithm/DFS.h
  algorithm/ConnectedComponents.h
  algorithm/Dijkstra.h
  algorithm/CycleMembership.h
  algorithm/RelevantCycles.h
  algorithm/Backtrack.h
  algorithm/VF2State.h
  algorithm/Isomorphisms.h
  algorithm/ExtendedConnectivities.h
)

copy_headers("${OCGL_HDRS}" ocgl)
copy_headers("${OCGL_PREDICATE_HDRS}" ocgl)
copy_headers("${OCGL_MODEL_HDRS}" ocgl)
copy_headers("${OCGL_ALGORITHM_HDRS}" ocgl)

install(FILES ${OCGL_HDRS} DESTINATION include/ocgl)
install(FILES ${OCGL_PREDICATE_HDRS} DESTINATION include/ocgl/predicate)
install(FILES ${OCGL_MODEL_HDRS} DESTINATION include/ocgl/model)
install(FILES ${OCGL_ALGORITHM_HDRS} DESTINATION include/ocgl/algorithm)
