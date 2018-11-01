
# output variables
set(GEO3DML_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE PATH "")
set(GEO3DML_LIBRARIES libGeo3DML CACHE STRING "")

aux_source_directory(. Geo3DML_SOURCES)
list(APPEND GEO3DML_HEADERS
	${PROJECT_SOURCE_DIR}/include/geo3dml/Geo3DML.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Project.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Model.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/FeatureClass.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Feature.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/ObjectFactory.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Geometry.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Shape.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/TIN.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/CornerPointGrid.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/UniformGrid.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Context.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/SceneStyle.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Color.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Light.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Field.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/FieldValue.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/ShapeProperty.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/LineString.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Point.h
)
include_directories(${GEO3DML_INCLUDE_DIRS})
add_library(${GEO3DML_LIBRARIES} STATIC
    ${Geo3DML_SOURCES}
    ${GEO3DML_HEADERS}
    uuid.h
)
