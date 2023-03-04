#ifndef QUANTEXTMLIR_CONVERSION_PASSDETAIL_H
#define QUANTEXTMLIR_CONVERSION_PASSDETAIL_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"

namesapce mlir {
  namesapce quant_ext {

#define GEN_PASS_DECL
#include "quant-ext-opt/Conversion/Passes.h.inc"
  }
}

#endif