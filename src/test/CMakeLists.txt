if(MSVC)
  add_compile_options(/utf-8)
endif()

# VTK 9.2
find_package(VTK CONFIG REQUIRED)

include_directories(${GEO3DML_INCLUDE_DIRS})
add_executable(libGeo3DMLTest
  main.cpp
)

target_link_libraries(libGeo3DMLTest PRIVATE
  ${VTK_LIBRARIES}
  ${GEO3DML_LIBRARIES}
  ${G3DXML_LIBRARIES}
  ${G3DVTK_LIBRARIES}
)