#ifndef QUANTEXTMLIR_PIPELINES_PASSES_H
#define QUANTEXTMLIR_PIPELINES_PASSES_H
#include "mlir/Pass/Pass.h"
namespace mlir {
namespace quant_ext {
void createONNXTToQuantMLIRPipeline(OpPassManager &pm);
void registerPipelines();
} // namespace quant_ext
} // namespace mlir

#endif