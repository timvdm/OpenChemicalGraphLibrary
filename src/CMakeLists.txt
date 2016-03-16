set(OCGL_HDRS
  Contract.h
  Range.h
  GraphTraits.h
  AdjacentIterator.h
  PropertyMap.h

  #model/PointerGraph.h
  #model/IdGraph.h
  #model/ObjectGraph.h
)

copy_headers("${OCGL_HDRS}" ocgl)
