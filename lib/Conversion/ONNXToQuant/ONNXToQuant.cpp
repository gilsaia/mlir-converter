#include "quant-ext-opt/Conversion/ONNXToQuant/ONNXToQuant.h"

#include "../PassDetail.h"

std::unique_ptr<OperationPass<func::FuncOp>>
mlir::quant_ext::createConvertONNXToQuantPass() {}