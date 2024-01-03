gaudi_add_module(llHAna
                 SOURCES src/llHAna.cpp
                 LINK DataHelperLib 
		      k4FWCore::k4FWCore
                      Gaudi::GaudiKernel 
                      Gaudi::GaudiAlgLib
		      EDM4HEP::edm4hep
		      EDM4HEP::edm4hepDict
                      ${CLHEP_LIBRARIES} 
                      ${GSL_LIBRARIES}
                      ${LCIO_LIBRARIES}
                      ${ROOT_LIBRARIES}
)

target_include_directories(llHAna
  PUBLIC ${LCIO_INCLUDE_DIRS})

install(TARGETS llHAna
  EXPORT CEPCSWTargets
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT shlib
  COMPONENT dev)
