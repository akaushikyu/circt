add_circt_dialect_library(HLSInterfaces
        MemoryInterface.cpp
        MemoryDS.cpp
        
        DEPENDS
        MemoryInterfaceIncGen

        LINK_LIBS PUBLIC
        HLSConfig
        CIRCTLoopSchedule
        MLIRIR
        MLIRSupport
        MLIRMemRefDialect
)
