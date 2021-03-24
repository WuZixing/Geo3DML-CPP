# Geo3DML SDK
find_file(GEO3DML_HEADER "geo3dml/ObjectFactory.h" PATHS ${GEO3DML_INCLUDE_DIRS})
if(NOT GEO3DML_HEADER)
	message(SEND_ERROR "Can not find Geo3DML headers. Please set GEO3DML_INCLUDE_DIRS to the directory that contains file geo3dml/ObjectFactory.h.")
endif()

# SQLiteCpp
find_package(SQLiteCpp CONFIG REQUIRED)

# output variables
set(G3DSQLITE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE PATH "")
set(G3DSQLITE_LIBRARIES libG3DSqlite CACHE STRING "")

aux_source_directory(. G3DSQLITE_SOURCES)
list(APPEND G3DSQLITE_HEADERS
	${PROJECT_SOURCE_DIR}/include/g3dsqlite/Reader.h
)

include_directories(${G3DSQLITE_INCLUDE_DIRS})
add_library(${G3DSQLITE_LIBRARIES}
	${G3DSQLITE_SOURCES}
	${G3DSQLITE_HEADERS}
)
target_link_libraries(${G3DSQLITE_LIBRARIES} PRIVATE SQLiteCpp)
