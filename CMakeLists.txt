cmake_minimum_required(VERSION 3.10)

project(MLIR-Converter VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT REQUIRED)

execute_process(
  COMMAND
  	${PYTHON_EXECUTABLE} "-c" "import torch_mlir"
  RESULT_VARIABLE _py_torch_mlir_status
  OUTPUT_VARIABLE _py_torch_mlir_out
  ERROR_QUIET
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(_py_torch_mlir_status)
    MESSAGE(FATAL_ERROR "Python package torch-mlir is required.Please install torch-mlir first.")
endif()


add_subdirectory(converter)