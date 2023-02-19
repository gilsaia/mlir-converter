#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "torch-mlir/InitAll.h"

using namespace mlir;

int main(int argc, char **argv) {
  registerAllPasses();
  //   mlir::torch::registerAllPasses();

  DialectRegistry registry;
  registerAllDialects(registry);
  //   mlir::torch::registerAllDialects(registry);

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "MLIR modular optimizer driver\n", registry,
                        /*preloadDialectsInContext=*/false));
}