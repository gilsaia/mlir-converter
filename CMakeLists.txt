cmake_minimum_required(VERSION 3.10)

project(MLIR-Converter VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_PYTHON_FRONTEND "use python frontend" ON)

if(USE_PYTHON_FRONTEND)
  add_definitions(-DUSE_PYTHON_FRONTEND)
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

  include_directories(${PYTHON_INCLUDE_DIRS})
  link_libraries(${PYTHON_LIBRARIES})
endif()

add_subdirectory(3rdparty/gflags)

# MLIR/LLVM Configuration
set(MLIR_DIR ${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/build/lib/cmake/mlir)
set(LLVM_DIR ${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/build/lib/cmake/llvm)
find_package(MLIR REQUIRED CONFIG)

set(LLVM_MLIR_BINARY_DIR ${MLIR_DIR}/../../../bin)
set(LLVM_MLIR_SOURCE_DIR ${MLIR_DIR}/../../../../mlir)
set(LLVM_PROJECT_SOURCE_DIR ${MLIR_DIR}/../../../../)

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

find_program(LLVM_TABLEGEN_EXE "llvm-tblgen" ${LLVM_TOOLS_BINARY_DIR}
    NO_DEFAULT_PATH)

include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
#-------------------------------------------------------------------------------

add_subdirectory(converter)