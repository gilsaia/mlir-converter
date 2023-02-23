#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "torch-mlir-dialects/Dialect/TMTensor/IR/TMTensorDialect.h"
#include "torch-mlir-dialects/Dialect/TMTensor/Transforms/Passes.h"
#include "torch-mlir/Conversion/Passes.h"
#include "torch-mlir/Dialect/Torch/IR/TorchDialect.h"
#include "torch-mlir/Dialect/Torch/Transforms/Passes.h"
#include "torch-mlir/Dialect/TorchConversion/IR/TorchConversionDialect.h"
#include "torch-mlir/Dialect/TorchConversion/Transforms/Passes.h"
#include "torch-mlir/InitAll.h"
#include "torch-mlir/RefBackend/Passes.h"

#include "mhlo/transforms/passes.h"

using namespace mlir;

int main(int argc, char **argv) {
  registerAllPasses();
  mlir::torch::registerAllPasses();
  // mlir::torch::registerTorchPasses();
  // mlir::torch::registerTorchConversionPasses();
  // mlir::torch::registerConversionPasses();
  // mlir::torch::RefBackend::registerRefBackendPasses();
  // mlir::torch::TMTensor::registerPasses();
  // mlir::mhlo::registerSymbolicShapeOptimizationPass();
  // mlir::mhlo::registerStablehloLegalizeToHloPass();
  // mlir::mhlo::registerChloLegalizeToHloPass();
  // mlir::mhlo::registerHloLegalizeToLinalgPass();

  DialectRegistry registry;
  registerAllDialects(registry);
  // registry.insert<mlir::torch::Torch::TorchDialect>();
  // registry.insert<mlir::torch::TorchConversion::TorchConversionDialect>();
  // registry.insert<mlir::torch::TMTensor::TMTensorDialect>();
  mlir::torch::registerAllDialects(registry);

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "MLIR modular optimizer driver\n", registry,
                        /*preloadDialectsInContext=*/false));
}