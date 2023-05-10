#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"
#include "mlir/Conversion/ControlFlowToLLVM/ControlFlowToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVM.h"
#include "mlir/Conversion/LinalgToLLVM/LinalgToLLVM.h"
#include "mlir/Conversion/Passes.h"
#include "mlir/Conversion/ReconcileUnrealizedCasts/ReconcileUnrealizedCasts.h"
#include "mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"
#include "mlir/Conversion/TosaToArith/TosaToArith.h"
#include "mlir/Conversion/TosaToLinalg/TosaToLinalg.h"
#include "mlir/Conversion/VectorToLLVM/ConvertVectorToLLVM.h"
#include "mlir/Conversion/VectorToSCF/VectorToSCF.h"
#include "mlir/Dialect/Arith/Transforms/Passes.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Func/Transforms/Passes.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/Dialect/SCF/Transforms/Passes.h"
#include "mlir/Dialect/Tensor/Transforms/Passes.h"
#include "mlir/Dialect/Tosa/Transforms/Passes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"

#include "quant-ext-opt/Pipeline/Passes.h"

#include "torch-mlir/Dialect/TorchConversion/Transforms/Passes.h"

using namespace mlir;
void quant_ext::createTorchToLLVMIRPipeline(OpPassManager &pm) {
  torch::TorchConversion::createTorchBackendToTosaBackendPipeline(pm);
  pm.addPass(tosa::createTosaLayerwiseConstantFoldPass());
  pm.addPass(tosa::createTosaMakeBroadcastablePass());
  pm.addPass(tosa::createTosaToArith(true, true));
  tosa::addTosaToLinalgPasses(pm, false);
  pm.addNestedPass<func::FuncOp>(createCanonicalizerPass());
  pm.addNestedPass<func::FuncOp>(createCSEPass());
  pm.addPass(bufferization::createEmptyTensorToAllocTensorPass());
  pm.addPass(createLinalgBufferizePass());
  pm.addPass(createSCFBufferizePass());
  pm.addPass(arith::createArithBufferizePass());
  pm.addPass(createTensorBufferizePass());
  pm.addPass(func::createFuncBufferizePass());
  pm.addPass(bufferization::createFinalizingBufferizePass());
  // pm.addPass(bufferization::createOneShotBufferizePass());
  pm.addNestedPass<func::FuncOp>(createCanonicalizerPass());
  pm.addNestedPass<func::FuncOp>(createCSEPass());
  // pm.addNestedPass<func::FuncOp>(bufferization::createBufferDeallocationPass());
  // pm.addNestedPass<func::FuncOp>(createConvertVectorToSCFPass());
  pm.addNestedPass<func::FuncOp>(createConvertLinalgToLoopsPass());
  // pm.addNestedPass<func::FuncOp>(createCanonicalizerPass());
  pm.addNestedPass<func::FuncOp>(createConvertSCFToCFPass());
  pm.addPass(createConvertLinalgToLLVMPass());
  pm.addPass(memref::createExpandStridedMetadataPass());
  pm.addPass(createArithToLLVMConversionPass());
  pm.addNestedPass<func::FuncOp>(createConvertSCFToCFPass());
  pm.addPass(createFinalizeMemRefToLLVMConversionPass());
  pm.addPass(createConvertFuncToLLVMPass());
  pm.addPass(createReconcileUnrealizedCastsPass());
}