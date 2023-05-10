set(LLVM_LINK_COMPONENTS
  Core
  Support
  nativecodegen
  native
  )
  
add_llvm_executable(quant-ext-cpu-runner quant-ext-cpu-runner.cpp)
target_link_libraries(quant-ext-cpu-runner PRIVATE
MLIRAnalysis
# MLIRBuiltinToLLVMIRTranslation
MLIRExecutionEngine
MLIRIR
MLIRJitRunner
MLIRLLVMDialect
MLIRLLVMToLLVMIRTranslation
MLIRToLLVMIRTranslationRegistration
MLIRParser
MLIRTargetLLVMIRExport
MLIRSupport
)