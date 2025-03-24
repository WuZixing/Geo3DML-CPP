add_subdirectory(geo3dml)
add_subdirectory(g3dxml)

set(USE_G3DVTK_LIBRARIES OFF CACHE BOOL "Whether the G3DVTK library which depends on the VTK library should be included or not.")
if(USE_G3DVTK_LIBRARIES)
    add_subdirectory(g3dvtk)
endif()

set(USE_G3DSQLITE_LIBRARIES OFF CACHE BOOL "Whether the G3DSQLITE library which depends on SQLiteCPP should be included or not.")
if(USE_G3DSQLITE_LIBRARIES)
    add_subdirectory(g3dsqlite)
endif()

if(${Build_Geo3DML_CPP_Test})
  add_subdirectory(test)
endif()