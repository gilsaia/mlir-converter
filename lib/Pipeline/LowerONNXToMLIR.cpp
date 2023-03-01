#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"

#include "src/Pass/Passes.hpp"

#include "quant-ext-opt/Pipeline/Passes.h"

void mlir::quant_ext::createONNXTToQuantMLIRPipeline(mlir::OpPassManager &pm) {
  pm.addNestedPass<mlir::func::FuncOp>(
      onnx_mlir::createDecomposeONNXToONNXPass());
  pm.addPass(onnx_mlir::createShapeInferencePass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(onnx_mlir::createShapeInferencePass());
  // There are more opportunities for const propagation once all tensors have
  // inferred shapes.
  pm.addNestedPass<func::FuncOp>(
      onnx_mlir::createConstPropONNXToONNXPass(true));
  pm.addPass(onnx_mlir::createONNXOpTransformPass(3, true, false, true));

  // Simplify shape-related ops.
  pm.addPass(onnx_mlir::createSimplifyShapeRelatedOpsPass(true));

  // Clean dead code.
  pm.addPass(mlir::createSymbolDCEPass());

  // Replace every DisposableElementsAttr with DenseElementsAttr.
  pm.addPass(onnx_mlir::createScrubDisposablePass());

  pm.addPass(mlir::createCSEPass());
  // Verify ONNX ops before lowering to Krnl.
  pm.addNestedPass<func::FuncOp>(onnx_mlir::createONNXPreKrnlVerifyPass());

  pm.addNestedPass<func::FuncOp>(onnx_mlir::createInstrumentPass());

  pm.addPass(onnx_mlir::createLowerToKrnlPass(0, true));

  pm.addPass(mlir::createCanonicalizerPass());

  pm.addNestedPass<func::FuncOp>(
      onnx_mlir::createDisconnectKrnlDimFromAllocPass());
  pm.addPass(mlir::createCanonicalizerPass());

  pm.addNestedPass<func::FuncOp>(
      onnx_mlir::krnl::createConvertKrnlToAffinePass());
}