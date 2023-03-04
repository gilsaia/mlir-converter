cmake_minimum_required(VERSION 3.10)

project(MLIR-Converter VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(UNIX)
  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    add_compile_options(-Wno-unused-but-set-variable)
  endif()
endif()

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
set(TORCH_MLIR_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/build/tools/torch-mlir/include 
${CMAKE_SOURCE_DIR}/3rdparty/torch-mlir/include 
${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/build/tools/torch-mlir-dialects/include
${CMAKE_SOURCE_DIR}/3rdparty/torch-mlir/externals/llvm-external-projects/torch-mlir-dialects/include
${CMAKE_SOURCE_DIR}/3rdparty/llvm-project/build/tools/torch-mlir/mlir-hlo
${CMAKE_SOURCE_DIR}/3rdparty/torch-mlir/externals/mlir-hlo)
set(MLIR_LIB_DIR ${MLIR_DIR}/../../)
list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
file(GLOB MLIR_LIB_FILES LIST_DIRECTORIES false RELATIVE ${MLIR_LIB_DIR} ${MLIR_LIB_DIR}/libMLIR*.a)
file(GLOB TORCH_MLIR_LIB_FILES LIST_DIRECTORIES false RELATIVE ${MLIR_LIB_DIR} ${MLIR_LIB_DIR}/libTorch*.a)
file(GLOB HLO_MLIR_LIB_FILES LIST_DIRECTORIES false RELATIVE ${MLIR_LIB_DIR} ${MLIR_LIB_DIR}/lib*hlo*.a)
string(REPLACE "lib" "" TORCH_MLIR_LIB_FILES "${TORCH_MLIR_LIB_FILES}")
string(REPLACE ".a" "" TORCH_MLIR_LIB_FILES "${TORCH_MLIR_LIB_FILES}")
string(REPLACE "lib" "" HLO_MLIR_LIB_FILES "${HLO_MLIR_LIB_FILES}")
string(REPLACE ".a" "" HLO_MLIR_LIB_FILES "${HLO_MLIR_LIB_FILES}")

find_program(LLVM_TABLEGEN_EXE "llvm-tblgen" ${LLVM_TOOLS_BINARY_DIR}
    NO_DEFAULT_PATH)

include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
include_directories(${TORCH_MLIR_INCLUDE_DIRS})
link_directories(${MLIR_LIB_DIR})
#-------------------------------------------------------------------------------

# ONNX MLIR Configuration
add_subdirectory(3rdparty/onnx-mlir)
set(ONNX_MLIR_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/3rdparty/onnx-mlir ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/onnx-mlir)
include_directories(${ONNX_MLIR_INCLUDE_DIRS})
#-------------------------------------------------------------------------------

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(converter)
add_subdirectory(tools)