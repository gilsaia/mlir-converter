#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <gflags/gflags.h>

#include "utils.h"
#ifdef USE_PYTHON_FRONTEND
#include "python_frontend/frontend.h"
#endif

DEFINE_string(frontend, "torch", "the original model type");
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

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  char *source;
  if (FLAGS_frontend == "torch") {
    if (FLAGS_model == "SimpleNet") {
#ifdef USE_PYTHON_FRONTEND
      source = get_simple_net();
#else
      throw NotWithPython();
#endif
    } else {
      throw NotImplemented();
    }
  } else {
    throw NotImplemented();
  }
  FILE *fp = fopen(FLAGS_o.c_str(), "w");
  fputs(source, fp);
  fclose(fp);
  return 0;
}