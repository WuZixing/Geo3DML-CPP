if(MSVC)
  add_compile_options(/utf-8)
endif()

# Geo3DML SDK
find_file(GEO3DML_HEADER "geo3dml/ObjectFactory.h" PATHS ${GEO3DML_INCLUDE_DIRS})
if(NOT GEO3DML_HEADER)
  message(SEND_ERROR "Can not find Geo3DML headers. Please set GEO3DML_INCLUDE_DIRS to the directory that contains file geo3dml/ObjectFactory.h.")
endif()

# output variables
set(G3DXML_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE PATH "")
set(G3DXML_LIBRARIES libG3DXML CACHE STRING "")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libxml2/include)
add_definitions(-DLIBXML_STATIC)
add_subdirectory(libxml2)

set(g3dlibxml2_la_SOURCES
  libxml2/DOCBparser.c
  libxml2/HTMLparser.c
  libxml2/HTMLtree.c
  libxml2/SAX.c
  libxml2/SAX2.c
  libxml2/c14n.c
  libxml2/catalog.c
  libxml2/chvalid.c
  libxml2/debugXML.c
  libxml2/dict.c
  libxml2/encoding.c
  libxml2/entities.c
  libxml2/error.c
  libxml2/globals.c
  libxml2/hash.c
  libxml2/legacy.c
  libxml2/list.c
  libxml2/nanoftp.c
  libxml2/nanohttp.c
  libxml2/parser.c
  libxml2/parserInternals.c
  libxml2/pattern.c
  libxml2/relaxng.c
  libxml2/schematron.c
  libxml2/threads.c
  libxml2/tree.c
  libxml2/uri.c
  libxml2/valid.c
  libxml2/xinclude.c
  libxml2/xlink.c
  libxml2/xmlIO.c
  libxml2/xmlmemory.c
  libxml2/xmlmodule.c
  libxml2/xmlreader.c
  libxml2/xmlregexp.c
  libxml2/xmlsave.c
  libxml2/xmlschemas.c
  libxml2/xmlschemastypes.c
  libxml2/xmlstring.c
  libxml2/xmlunicode.c
  libxml2/xmlwriter.c
  libxml2/xpath.c
  libxml2/xpointer.c
)

aux_source_directory(. G3DXML_SOURCES)
list(APPEND G3DXML_HEADERS
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLIO.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLReaderHelper.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLProjectReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLModelReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLFeatureClassReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLFeatureReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLGeometryReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLFieldReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLWriter.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLFeatureClassWriter.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLGeometryWriter.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLShapePropertyWriter.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLTINReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLCornerPointGridReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLUniformGridReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLGeoDiscreteCoverageReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLLineStringReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLPointReader.h
    ${PROJECT_SOURCE_DIR}/include/g3dxml/XMLAnnotationReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLMultiPointReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLLayerWriter.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLMapReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLLayerReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLStyleReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLFeatureTypeStyleReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLStyleRuleReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLPointSymbolizerReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLLineSymbolizerReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLSurfaceSymbolizerReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLMaterialReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLGeoDiscreteCoverageSymbolizerReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLGTPVolumeReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLRectifiedGridReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLTetrahedronVolumeReader.h
	${PROJECT_SOURCE_DIR}/include/g3dxml/XMLCuboidVolumeReader.h
)

include_directories(${GEO3DML_INCLUDE_DIRS})
add_library(${G3DXML_LIBRARIES} STATIC
	${g3dlibxml2_la_SOURCES}
	${G3DXML_SOURCES}
	${G3DXML_HEADERS}
)
