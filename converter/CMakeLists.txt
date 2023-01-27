project(converter)

add_executable(converter converter.cpp frontend.h frontend.cpp)

target_include_directories(converter PRIVATE ${PYTHON_INCLUDE_DIRS})

target_link_libraries(converter PRIVATE ${PYTHON_LIBRARIES})