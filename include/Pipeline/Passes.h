#ifndef QUANTEXTMLIR_PIPELINES_PASSES_H
#define QUANTEXTMLIR_PIPELINES_PASSES_H
namespace mlir {
namespace quant_ext {
void createONNXTToQuantMLIRPipeline();
void registerPipelines();
} // namespace quant_ext
} // namespace mlir

#endif