#include <fstream>
#include <gflags/gflags.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"

#include "torch-mlir/Conversion/TorchToLinalg/TorchToLinalg.h"
#include "torch-mlir/Conversion/TorchToTosa/TorchToTosa.h"
#include "torch-mlir/Dialect/Torch/IR/TorchDialect.h"
#include "torch-mlir/Dialect/TorchConversion/IR/TorchConversionDialect.h"

#include "utils.h"
#ifdef USE_PYTHON_FRONTEND
#include "python_frontend/frontend.h"
#endif
#include "mlir_frontend/frontend.h"

DEFINE_string(frontend, "mlir", "the original model type");
DEFINE_string(model, "SimpleNet", "Default torch to use");
DEFINE_string(o, "output.mlir", "Output file name");

static bool ValidateFrontend(const char *flagname, const std::string &value) {
  if (value == "torch" || value == "mlir") {
    return true;
  }
  printf("Invalid value for %s,only accept torch/mlir\n", flagname);
  return false;
}

static bool ValidateModel(const char *flagname, const std::string &value) {
  if (value == "SimpleNet") {
    return true;
  }
  printf("Invalid value for %s,only accept SimpleNet\n", flagname);
  return false;
}

DEFINE_validator(frontend, &ValidateFrontend);
DEFINE_validator(model, &ValidateModel);

void loadMLIR(mlir::MLIRContext &context, llvm::StringRef &source,
              mlir::OwningOpRef<mlir::ModuleOp> &module) {
  context.loadDialect<mlir::func::FuncDialect>();
  context.loadDialect<mlir::torch::Torch::TorchDialect>();
  context.loadDialect<mlir::torch::TorchConversion::TorchConversionDialect>();
  module = mlir::parseSourceString<mlir::ModuleOp>(source, &context);
  return;
}

void processMLIR(mlir::MLIRContext &context,
                 mlir::OwningOpRef<mlir::ModuleOp> &module) {
  mlir::PassManager pm(module.get()->getName());
  pm.addPass(mlir::createInlinerPass());
  // pm.addPass(mlir::torch::createConvertTorchToLinalgPass());
  if (mlir::failed(pm.run(*module))) {
    llvm::errs() << "convert failed\n";
  }
}

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  char *source;
  if (FLAGS_frontend == "torch") {
    if (FLAGS_model == "SimpleNet") {
#ifdef USE_PYTHON_FRONTEND
      source = get_py_simple_net();
#else
      throw NotWithPython();
#endif
    } else {
      throw NotImplemented();
    }
  } else {
    if (FLAGS_model == "SimpleNet") {
      source = get_mlir_simple_net();
    } else {
      throw NotImplemented();
    }
  }

  mlir::MLIRContext context;
  mlir::OwningOpRef<mlir::ModuleOp> module;
  llvm::StringRef source_l(source);
  loadMLIR(context, source_l, module);
  module->dump();
  processMLIR(context, module);
  module->dump();

  llvm::StringRef filename(FLAGS_o);
  std::error_code ec;
  llvm::raw_fd_ostream fs(filename, ec);
  module->print(fs);

  // std::ofstream fp;
  // FILE *fp = fopen(FLAGS_o.c_str(), "w");
  // fputs(source, fp);
  // fclose(fp);
  // fp.close();
  return 0;
}