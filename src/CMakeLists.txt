add_subdirectory(geo3dml)
add_subdirectory(g3dxml)

set(USE_G3DVTK_LIBRARIES OFF CACHE BOOL "Whether the G3DVTK library should be included or not.")
if(USE_G3DVTK_LIBRARIES)
	add_subdirectory(g3dvtk)
endif()
