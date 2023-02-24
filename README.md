A basic MLIR-based converter project

Now target is to transform quant model (use fp16/int8/int4/bf32/bf8 precision)

## build llvm dep

To build the project, it is necessary to pre-build LLVM and its corresponding dependencies.

```bash
$ cd buddy-mlir
$ mkdir llvm/build
$ cd llvm/build
$ cmake -G Ninja ../llvm \
    -DLLVM_ENABLE_PROJECTS="mlir;clang" \
    -DLLVM_TARGETS_TO_BUILD="host;RISCV" \
    -DLLVM_EXTERNAL_PROJECTS="torch-mlir;torch-mlir-dialects" \
    -DLLVM_EXTERNAL_TORCH_MLIR_SOURCE_DIR=../../torch-mlir \
    -DLLVM_EXTERNAL_TORCH_MLIR_DIALECTS_SOURCE_DIR=../../torch-mlir/externals/llvm-external-projects/torch-mlir-dialects \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DCMAKE_BUILD_TYPE=RELEASE \
    -DLLVM_ENABLE_RTTI=ON
$ ninja check-mlir check-clang check-torch-mlir
```

If your target machine includes a Nvidia GPU, you can use the following configuration:

```bash
$ cmake -G Ninja ../llvm \
    -DLLVM_ENABLE_PROJECTS="mlir;clang" \
    -DLLVM_TARGETS_TO_BUILD="host;RISCV;NVPTX" \
    -DMLIR_ENABLE_CUDA_RUNNER=ON \
    -DLLVM_EXTERNAL_PROJECTS="torch-mlir;torch-mlir-dialects" \
    -DLLVM_EXTERNAL_TORCH_MLIR_SOURCE_DIR=../../torch-mlir \
    -DLLVM_EXTERNAL_TORCH_MLIR_DIALECTS_SOURCE_DIR=../../torch-mlir/externals/llvm-external-projects/torch-mlir-dialects \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DCMAKE_BUILD_TYPE=RELEASE \
    -DLLVM_ENABLE_RTTI=ON
```