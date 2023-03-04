#ifndef QUANTEXTMLIR_CONVERSION_ONNXTOQUANT_H
#define QUANTEXTMLIR_CONVERSION_ONNXTOQUANT_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"
#include <memory>

namespace mlir {
namespace quant_ext {
std::unique_ptr<mlir::OperationPass<mlir::func::FuncOp>>
createConvertONNXToQuantPass();
}
} // namespace mlir

#endif