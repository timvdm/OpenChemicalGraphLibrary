set(OCGL_HDRS
  Contract.h
  Range.h
  GraphTraits.h
  AdjacentIterator.h
  PropertyMap.h
  GraphStringParser.h

  model/PointerGraph.h
  model/IdGraph.h
  model/ObjectGraph.h

  algorithm/DFS.h
)

copy_headers("${OCGL_HDRS}" ocgl)
