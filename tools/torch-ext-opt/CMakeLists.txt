add_llvm_executable(torch-ext-opt torch-ext-opt.cpp)

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

target_link_libraries(torch-ext-opt PRIVATE 
${dialect_libs}
${conversion_libs}
MLIROptLib
TorchMLIRInitAll
TorchMLIRTorchDialect
TorchMLIRTorchPasses
TorchMLIRTorchUtils
TorchMLIRConversionPasses TorchMLIRConversionUtils TorchMLIRTorchConversionDialect
${TORCH_MLIR_LIB_FILES}
${HLO_MLIR_LIB_FILES})
