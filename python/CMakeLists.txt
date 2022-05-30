add_subdirectory(pybind11)

add_definitions(-DASTYLE_LIB)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../src)
pybind11_add_module(pyastyle pyastyle.cpp)
target_link_libraries(pyastyle PRIVATE astyle)
