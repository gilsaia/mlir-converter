project(converter)

file(COPY python_frontend/predefined_model.py DESTINATION predefined)

file(GLOB_RECURSE CONVERTER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(converter ${CONVERTER_FILES})

target_include_directories(converter PRIVATE ${PYTHON_INCLUDE_DIRS})

target_link_libraries(converter PRIVATE ${PYTHON_LIBRARIES} gflags::gflags)