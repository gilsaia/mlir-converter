#ifndef QUANTEXTMLIR_PIPELINES_PASSES_H
#define QUANTEXTMLIR_PIPELINES_PASSES_H
#include "mlir/Pass/Pass.h"
#include "quant-ext-opt/Conversion/ONNXToQuant/ONNXToQuant.h"
#include "quant-ext-opt/Conversion/Passes.h"
namespace mlir {
namespace quant_ext {
void createTorchToLLVMIRPipeline(OpPassManager &pm);
void createONNXTToQuantMLIRPipeline(OpPassManager &pm);
void registerPipelines();
} // namespace quant_ext
} // namespace mlir

#endif