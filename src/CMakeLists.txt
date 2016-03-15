set(OCGL_HDRS
  Contract.h
  IterPair.h
  GraphTraits.h
  #AdjacentIterator.h
  #PropertyMap.h

  #model/PointerGraph.h
)

copy_headers("${OCGL_HDRS}" ocgl)
