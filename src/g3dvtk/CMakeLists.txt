if(MSVC)
  add_compile_options(/utf-8)
endif()

# Geo3DML SDK
find_file(GEO3DML_HEADER "geo3dml/ObjectFactory.h" PATHS ${GEO3DML_INCLUDE_DIRS})
if(NOT GEO3DML_HEADER)
  message(SEND_ERROR "Can not find Geo3DML headers. Please set GEO3DML_INCLUDE_DIRS to the directory that contains file geo3dml/ObjectFactory.h.")
endif()

# VTK
#find_package(VTK 9.0 REQUIRED)
find_package(VTK REQUIRED)
if(NOT VTK_FOUND)
  message(FATAL_ERROR "${VTK_NOT_FOUND_MESSAGE}")
endif()
message(STATUS "VTK_VERSION: ${VTK_VERSION}")
if(VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
else()
  include_directories("${VTK_PREFIX_PATH}/include/vtk-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}")
endif()

# output variables
set(G3DVTK_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE PATH "")
set(G3DVTK_LIBRARIES libG3DVTK CACHE STRING "")

aux_source_directory(. G3DVTK_SOURCES)
list(APPEND G3DVTK_HEADERS
	Utils.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/ObjectFactory.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/TIN.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/CornerPointGrid.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/UniformGrid.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/ShapeProperty.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/LineString.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/ShapeHelper.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/Point.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/MultiPoint.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/Actor.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/ColorMap.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/ColorMapCoolToWarm.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/ColorMapPlasma.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/ColorMapViridis.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/ContinuousAttributeColorTransfer.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/DiscreteAttributeColorTransfer.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/Annotation.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/MultiLineString.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/TriangularPrismVolume.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/RectifiedGrid.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/CuboidVolume.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/TetrahedronVolume.h
	${PROJECT_SOURCE_DIR}/include/g3dvtk/TruncatedRegularGrid.h
)

include_directories(${GEO3DML_INCLUDE_DIRS})
add_library(${G3DVTK_LIBRARIES}
	${G3DVTK_SOURCES}
	${G3DVTK_HEADERS}
)
target_link_libraries(${G3DVTK_LIBRARIES} 
  PRIVATE ${GEO3DML_LIBRARIES} ${VTK_LIBRARIES}
)
