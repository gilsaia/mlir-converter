#include "quant-ext-opt/Pipeline/Passes.h"

void mlir::quant_ext::registerPipelines() {
  mlir::PassPipelineRegistration<>(
      "lower-onnx-to-quant-mlir-pipeline",
      "Pipeline lowering ONNX object to MLIR with quant-ext.",
      mlir::quant_ext::createONNXTToQuantMLIRPipeline);
  mlir::PassPipelineRegistration<>(
      "lower-torch-to-llvmir-pipeline",
      "Pipeline lowering torch object to LLVM IR.",
      mlir::quant_ext::createTorchToLLVMIRPipeline);
}