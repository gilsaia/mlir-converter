#include "mlir/Pass/PassManager.h"

#include "src/Pass/Passes.hpp"

void lowerONNXToMLIR(OpPassManager &pm) {
  pm.addInstrumentation(
      std::make_unique<DisposableGarbageCollector>(pm.getContext()));

  pm.addNestedPass<func::FuncOp>(onnx_mlir::createDecomposeONNXToONNXPass());
}

void registerMyPasses() {
  // Register an existing pipeline builder function.
  PassPipelineRegistration<>("argument", "description", lowerONNXToMLIR);
}