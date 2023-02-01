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
add_subdirectory(converter)