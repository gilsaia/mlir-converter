add_mlir_conversion_library(QuantExtMLIRONNXToQuant
ONNXToQuant.cpp

ADDITIONAL_HEADER_DIRS
${PROJECT_SOURCE_DIR}/include/quant-ext-opt/Conversion/ONNXToQuant

DEPENDS
QuantExtConversionPassIncGen

LINK_COMPONENTS
Core

LINK_LIBS PUBLIC
MLIRIR
MLIRPass
MLIRFuncDialect
OMONNXOps
MLIRQuantDialect
)