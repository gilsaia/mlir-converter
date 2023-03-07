#include "mlir/Dialect/Quant/QuantOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/DialectConversion.h"

#include "quant-ext-opt/Conversion/ONNXToQuant/ONNXToQuant.h"
#include "src/Dialect/ONNX/ONNXOps.hpp"

#include "../PassDetail.h"

namespace {
class ConvertQuantizeLinearOp
    : public mlir::OpConversionPattern<mlir::ONNXQuantizeLinearOp> {
public:
  using OpConversionPattern::OpConversionPattern;
  mlir::LogicalResult
  matchAndRewrite(mlir::ONNXQuantizeLinearOp op,
                  mlir::ONNXQuantizeLinearOpAdaptor adaptor,
                  mlir::ConversionPatternRewriter &rewriter) const override {
    rewriter.replaceOpWithNewOp<mlir::quant::QuantizeCastOp>(
        op, getTypeConverter()->convertType(op.getType()), adaptor.getX());
    return mlir::success();
  }
};
} // namespace

namespace {
class ConvertONNXToQuant
    : public impl::ConvertONNXToQuantBase<ConvertONNXToQuant> {
  void getDependentDialects(mlir::DialectRegistry &registry) const override {
    registry.insert<mlir::ONNXDialect>();
    registry.insert<mlir::quant::QuantizationDialect>();
  }
  void runOnOperation() override {
    mlir::MLIRContext *context = &getContext();
    mlir::ConversionTarget target(*context);
    target
        .addLegalDialect<mlir::ONNXDialect, mlir::quant::QuantizationDialect>();

    mlir::TypeConverter typeConverter;
    typeConverter.addConversion([](mlir::Type type) { return type; });

    mlir::RewritePatternSet patterns(context);
    target.addIllegalOp<mlir::ONNXQuantizeLinearOp>();
    patterns.add<ConvertQuantizeLinearOp>(typeConverter, context);
    if (failed(applyPartialConversion(getOperation(), target,
                                      std::move(patterns)))) {
      return signalPassFailure();
    }
  }
};
} // namespace

std::unique_ptr<mlir::OperationPass<mlir::func::FuncOp>>
mlir::quant_ext::createConvertONNXToQuantPass() {
  return std::make_unique<ConvertONNXToQuant>();
}