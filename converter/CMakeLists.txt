project(converter)

set (copy_file python_frontend/predefined_model.py mlir_frontend/SampleNet.mlir)

file(COPY ${copy_file} DESTINATION predefined)

file(GLOB_RECURSE CONVERTER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

if(NOT USE_PYTHON_FRONTEND)
    list(FILTER CONVERTER_FILES EXCLUDE REGEX ".*python_frontend.*")
endif()

add_executable(converter ${CONVERTER_FILES})

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

target_link_libraries(converter PRIVATE gflags::gflags ${MLIR_LIB_FILES}
# MLIRIR MLIRParser MLIRFuncDialect MLIRPass MLIRTransforms MLIRTosaDialect MLIRSupport
TorchMLIRTorchDialect TorchMLIRTorchUtils TorchMLIRTorchToLinalg
TorchMLIRConversionPasses TorchMLIRConversionUtils TorchMLIRTorchConversionDialect
TorchMLIRTorchConversionPasses)