#include <string>
#include "frontend.h"

char *get_mlir_simple_net() {
  std::string path = "predefined/SampleNet.mlir";
  FILE *fp = fopen(path.c_str(), "r");

  fseek(fp, 0, SEEK_END);
  int length = ftell(fp);
  char *data = (char *)malloc((length + 1) * sizeof(char));
  rewind(fp);
  fread(data, 1, length, fp);
  data[length] = '\0';
  fclose(fp);
  return data;
}