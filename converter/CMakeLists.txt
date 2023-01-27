project(converter)

add_executable(converter converter.cpp python_frontend/frontend.h python_frontend/frontend.cpp)

target_include_directories(converter PRIVATE ${PYTHON_INCLUDE_DIRS})

target_link_libraries(converter PRIVATE ${PYTHON_LIBRARIES})