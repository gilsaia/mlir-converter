module attributes {llvm.data_layout = ""} {
  llvm.func @malloc(i64) -> !llvm.ptr<i8>
  llvm.mlir.global private constant @__constant_2x4xf32(dense<1.000000e+03> : tensor<2x4xf32>) {addr_space = 0 : i32} : !llvm.array<2 x array<4 x f32>>
  llvm.mlir.global private constant @__constant_3x4xf32(dense<[[1.000000e+00, 2.000000e+00, 3.000000e+00, 4.000000e+00], [5.000000e+00, 6.000000e+00, 7.000000e+00, 8.000000e+00], [9.000000e+00, 1.000000e+01, 1.100000e+01, 1.200000e+01]]> : tensor<3x4xf32>) {addr_space = 0 : i32} : !llvm.array<3 x array<4 x f32>>
  llvm.mlir.global private constant @__constant_2x3xf32(dense<[[1.000000e+00, 2.000000e+00, 3.000000e+00], [4.000000e+00, 5.000000e+00, 6.000000e+00]]> : tensor<2x3xf32>) {addr_space = 0 : i32} : !llvm.array<2 x array<3 x f32>>
  llvm.func @main() {
    %0 = llvm.mlir.constant(false) : i1
    %1 = llvm.mlir.constant(64 : index) : i64
    %2 = llvm.mlir.constant(4 : index) : i64
    %3 = llvm.mlir.constant(0 : index) : i64
    %4 = llvm.mlir.constant(0 : index) : i64
    %5 = llvm.mlir.constant(2 : index) : i64
    %6 = llvm.mlir.constant(1 : index) : i64
    %7 = llvm.mlir.constant(4 : index) : i64
    %8 = llvm.mlir.constant(3 : index) : i64
    %9 = llvm.mlir.constant(2 : index) : i64
    %10 = llvm.mlir.constant(3 : index) : i64
    %11 = llvm.mlir.constant(1 : index) : i64
    %12 = llvm.mlir.addressof @__constant_2x3xf32 : !llvm.ptr<array<2 x array<3 x f32>>>
    %13 = llvm.getelementptr %12[0, 0, 0] : (!llvm.ptr<array<2 x array<3 x f32>>>) -> !llvm.ptr<f32>
    %14 = llvm.mlir.addressof @__constant_3x4xf32 : !llvm.ptr<array<3 x array<4 x f32>>>
    %15 = llvm.getelementptr %14[0, 0, 0] : (!llvm.ptr<array<3 x array<4 x f32>>>) -> !llvm.ptr<f32>
    %16 = llvm.mlir.addressof @__constant_2x4xf32 : !llvm.ptr<array<2 x array<4 x f32>>>
    %17 = llvm.getelementptr %16[0, 0, 0] : (!llvm.ptr<array<2 x array<4 x f32>>>) -> !llvm.ptr<f32>
    %18 = llvm.mlir.null : !llvm.ptr<f32>
    %19 = llvm.getelementptr %18[8] : (!llvm.ptr<f32>) -> !llvm.ptr<f32>
    %20 = llvm.ptrtoint %19 : !llvm.ptr<f32> to i64
    %21 = llvm.add %20, %1  : i64
    %22 = llvm.call @malloc(%21) : (i64) -> !llvm.ptr<i8>
    %23 = llvm.bitcast %22 : !llvm.ptr<i8> to !llvm.ptr<f32>
    %24 = llvm.ptrtoint %23 : !llvm.ptr<f32> to i64
    %25 = llvm.sub %1, %11  : i64
    %26 = llvm.add %24, %25  : i64
    %27 = llvm.urem %26, %1  : i64
    %28 = llvm.sub %26, %27  : i64
    %29 = llvm.inttoptr %28 : i64 to !llvm.ptr<f32>
    %30 = llvm.mlir.undef : !llvm.struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)>
    %31 = llvm.insertvalue %23, %30[0] : !llvm.struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)> 
    %32 = llvm.insertvalue %29, %31[1] : !llvm.struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)> 
    %33 = llvm.insertvalue %3, %32[2] : !llvm.struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)> 
    %34 = llvm.insertvalue %9, %33[3, 0] : !llvm.struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)> 
    %35 = llvm.insertvalue %2, %34[3, 1] : !llvm.struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)> 
    %36 = llvm.insertvalue %2, %35[4, 0] : !llvm.struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)> 
    %37 = llvm.insertvalue %11, %36[4, 1] : !llvm.struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)> 
    %38 = llvm.mul %9, %11  : i64
    %39 = llvm.mul %38, %2  : i64
    %40 = llvm.mlir.null : !llvm.ptr<f32>
    %41 = llvm.getelementptr %40[1] : (!llvm.ptr<f32>) -> !llvm.ptr<f32>
    %42 = llvm.ptrtoint %41 : !llvm.ptr<f32> to i64
    %43 = llvm.mul %39, %42  : i64
    "llvm.intr.memcpy"(%29, %17, %43, %0) : (!llvm.ptr<f32>, !llvm.ptr<f32>, i64, i1) -> ()
    llvm.br ^bb1(%4 : i64)
  ^bb1(%44: i64):  // 2 preds: ^bb0, ^bb8
    %45 = llvm.icmp "slt" %44, %5 : i64
    llvm.cond_br %45, ^bb2, ^bb9
  ^bb2:  // pred: ^bb1
    llvm.br ^bb3(%4 : i64)
  ^bb3(%46: i64):  // 2 preds: ^bb2, ^bb7
    %47 = llvm.icmp "slt" %46, %7 : i64
    llvm.cond_br %47, ^bb4, ^bb8
  ^bb4:  // pred: ^bb3
    llvm.br ^bb5(%4 : i64)
  ^bb5(%48: i64):  // 2 preds: ^bb4, ^bb6
    %49 = llvm.icmp "slt" %48, %8 : i64
    llvm.cond_br %49, ^bb6, ^bb7
  ^bb6:  // pred: ^bb5
    %50 = llvm.mul %44, %10  : i64
    %51 = llvm.add %50, %48  : i64
    %52 = llvm.getelementptr %13[%51] : (!llvm.ptr<f32>, i64) -> !llvm.ptr<f32>
    %53 = llvm.load %52 : !llvm.ptr<f32>
    %54 = llvm.mul %48, %2  : i64
    %55 = llvm.add %54, %46  : i64
    %56 = llvm.getelementptr %15[%55] : (!llvm.ptr<f32>, i64) -> !llvm.ptr<f32>
    %57 = llvm.load %56 : !llvm.ptr<f32>
    %58 = llvm.mul %44, %2  : i64
    %59 = llvm.add %58, %46  : i64
    %60 = llvm.getelementptr %29[%59] : (!llvm.ptr<f32>, i64) -> !llvm.ptr<f32>
    %61 = llvm.load %60 : !llvm.ptr<f32>
    %62 = llvm.fmul %53, %57  : f32
    %63 = llvm.fadd %61, %62  : f32
    %64 = llvm.mul %44, %2  : i64
    %65 = llvm.add %64, %46  : i64
    %66 = llvm.getelementptr %29[%65] : (!llvm.ptr<f32>, i64) -> !llvm.ptr<f32>
    llvm.store %63, %66 : !llvm.ptr<f32>
    %67 = llvm.add %48, %6  : i64
    llvm.br ^bb5(%67 : i64)
  ^bb7:  // pred: ^bb5
    %68 = llvm.add %46, %6  : i64
    llvm.br ^bb3(%68 : i64)
  ^bb8:  // pred: ^bb3
    %69 = llvm.add %44, %6  : i64
    llvm.br ^bb1(%69 : i64)
  ^bb9:  // pred: ^bb1
    %70 = llvm.alloca %11 x !llvm.struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)> : (i64) -> !llvm.ptr<struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)>>
    llvm.store %37, %70 : !llvm.ptr<struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)>>
    %71 = llvm.bitcast %70 : !llvm.ptr<struct<(ptr<f32>, ptr<f32>, i64, array<2 x i64>, array<2 x i64>)>> to !llvm.ptr<i8>
    %72 = llvm.mlir.undef : !llvm.struct<(i64, ptr<i8>)>
    %73 = llvm.insertvalue %9, %72[0] : !llvm.struct<(i64, ptr<i8>)> 
    %74 = llvm.insertvalue %71, %73[1] : !llvm.struct<(i64, ptr<i8>)> 
    llvm.call @printMemrefF32(%9, %71) : (i64, !llvm.ptr<i8>) -> ()
    llvm.return
  }
  llvm.func @printMemrefF32(i64, !llvm.ptr<i8>) attributes {sym_visibility = "private"}
}

