#ifndef QUANTEXTMLIR_CONVERSION_PASSDETAIL_H
#define QUANTEXTMLIR_CONVERSION_PASSDETAIL_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/Pass/Pass.h"

#define GEN_PASS_DEF_CONVERTONNXTOQUANT
#include "quant-ext-opt/Conversion/Passes.h.inc"

#endif