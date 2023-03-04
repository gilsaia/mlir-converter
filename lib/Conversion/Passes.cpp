#include "quant-ext-opt/Conversion/Passes.h"

#include "quant-ext-opt/Conversion/ONNXToQuant/ONNXToQuant.h"

namespace {
#define GEN_PASS_REGISTRATION
#include "quant-ext-opt/Conversion/Passes.h.inc"
} // namespace

void mlir::quant_ext::registerConversionPasses() { ::registerPasses(); }