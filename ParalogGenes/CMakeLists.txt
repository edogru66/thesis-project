cmake_minimum_required(VERSION 3.12)
project(ParalogGenes)

set(CMAKE_CXX_STANDARD 14)
find_package(PkgConfig)
find_package(Boost REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )

add_executable(ParalogGenes Cpp/main.cpp Cpp/DnaSeq.cpp H/DnaSeq.h Cpp/SegmentalDuplication.cpp H/SegmentalDuplication.h Cpp/Gene.cpp H/Gene.h Cpp/Utility.cpp H/Utility.h H/TypeDefs.h)

TARGET_LINK_LIBRARIES( ParalogGenes LINK_PUBLIC ${Boost_LIBRARIES} )
