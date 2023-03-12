#include "mlir/Conversion/LinalgToLLVM/LinalgToLLVM.h"
#include "mlir/Conversion/TosaToArith/TosaToArith.h"
#include "mlir/Conversion/TosaToLinalg/TosaToLinalg.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/Dialect/SCF/Transforms/Passes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"

#include "quant-ext-opt/Pipeline/Passes.h"

#include "torch-mlir/Dialect/TorchConversion/Transforms/Passes.h"

using namespace mlir;
void quant_ext::createTorchToLLVMIRPipeline(OpPassManager &pm) {
  torch::TorchConversion::createTorchBackendToTosaBackendPipeline(pm);
  tosa::addTosaToLinalgPasses(pm, false);
  pm.addPass(tosa::createTosaToArith(true, true));
  pm.addPass(createCanonicalizerPass());
  pm.addPass(createCSEPass());
  pm.addPass(bufferization::createEmptyTensorToAllocTensorPass());
  pm.addPass(bufferization::createOneShotBufferizePass());
  pm.addPass(createCanonicalizerPass());
  pm.addPass(createCSEPass());
  pm.addPass(memref::createExpandStridedMetadataPass());
  pm.addPass(memref::createExpandOpsPass());
  pm.addPass(createConvertLinalgToParallelLoopsPass());
  pm.addPass(createParallelLoopFusionPass());
  pm.addPass(createCanonicalizerPass());
  pm.addPass(createCSEPass());
  // pm.addPass(createConvertLinalgToLLVMPass());
}