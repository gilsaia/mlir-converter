#ifndef QUANTEXTMLIR_CONVERSION_PASSES
#define QUANTEXTMLIR_CONVERSION_PASSES

include "mlir/Pass/PassBase.td"

def ConvertONNXToQuant:Pass<"convert-onnx-to-quant","mlir::func::FuncOp"> {
    let summary="Convert recognized ONNX ops to quant ops";
    let constructor="mlir::quant_ext::createConvertONNXToQuantPass()";
}

#endif
