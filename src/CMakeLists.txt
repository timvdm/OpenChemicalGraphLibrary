set(OCGL_HDRS
  Contract.h
  Range.h
  GraphTraits.h
  #AdjacentIterator.h
  #PropertyMap.h

  #model/PointerGraph.h
)

copy_headers("${OCGL_HDRS}" ocgl)
