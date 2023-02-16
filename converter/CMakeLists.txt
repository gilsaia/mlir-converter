project(converter)

set (copy_file python_frontend/predefined_model.py mlir_frontend/SampleNet.mlir)

file(COPY ${copy_file} DESTINATION predefined)

file(GLOB_RECURSE CONVERTER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

if(NOT USE_PYTHON_FRONTEND)
    list(FILTER CONVERTER_FILES EXCLUDE REGEX ".*python_frontend.*")
endif()

add_executable(converter ${CONVERTER_FILES})

target_include_directories(converter PRIVATE)
target_link_libraries(converter PRIVATE gflags::gflags MLIRIR MLIRParser MLIRFuncDialect TorchMLIRTorchDialect TorchMLIRTorchUtils)