if(MSVC)
  add_compile_options(/utf-8)
endif()

# output variables
set(GEO3DML_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE PATH "")
set(GEO3DML_LIBRARIES libGeo3DML CACHE STRING "")

aux_source_directory(. Geo3DML_SOURCES)
aux_source_directory(default-objects Geo3DML_SOURCES)
aux_source_directory(feature-relation Geo3DML_SOURCES)
file(GLOB DEFAULT_OBJECT_SOURCES false default-objects/*.h)
list(APPEND GEO3DML_HEADERS
	${PROJECT_SOURCE_DIR}/LICENSE
	${PROJECT_SOURCE_DIR}/README.md
	${PROJECT_SOURCE_DIR}/include/geo3dml/Geo3DML.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Project.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Model.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/FeatureClass.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Feature.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/ObjectFactory.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Geometry.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/TIN.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/CornerPointGrid.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Context.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/SceneStyle.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Color.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Light.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Field.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/FieldValue.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/ShapeProperty.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/LineString.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Point.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/MultiPoint.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Map.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Layer.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/PBRMaterial.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Symbolizer.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/PointSymbolizer.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/LineSymbolizer.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/SurfaceSymbolizer.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Style.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/FeatureTypeStyle.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/StyleRule.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/StyleRuleEqualTo.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Actor.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/GeoDiscreteCoverageSymbolizer.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Annotation.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Utils.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Box3D.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Point3D.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/MultiLineString.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Volume.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/TriangularPrismVolume.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/RectifiedGrid.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Vector3D.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Matrix3x3.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Matrix4x4.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/CuboidVolume.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/TetrahedronVolume.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/Texture.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/AbstractMetadata.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/ModelMetadata.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/ProjectMetadata.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/TruncatedRegularGrid.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/DefaultObjectFactory.h
	${PROJECT_SOURCE_DIR}/include/geo3dml/FeatureRelation.h
	${DEFAULT_OBJECT_SOURCES}
)
include_directories(${GEO3DML_INCLUDE_DIRS})
add_library(${GEO3DML_LIBRARIES} STATIC
    ${Geo3DML_SOURCES}
    ${GEO3DML_HEADERS}
    uuid.h
)
