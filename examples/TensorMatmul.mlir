func.func @main() {
  %A = arith.constant dense<[[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]]> : tensor<2x3xf32>
  %B = arith.constant dense<[[1.0, 2.0, 3.0, 4.0],
                       [5.0, 6.0, 7.0, 8.0],
                       [9.0, 10.0, 11.0, 12.0]]> : tensor<3x4xf32>
  %C = arith.constant dense<1000.0> : tensor<2x4xf32>

  %D = linalg.matmul ins(%A, %B: tensor<2x3xf32>, tensor<3x4xf32>)
                     outs(%C: tensor<2x4xf32>) -> tensor<2x4xf32>

  %unranked = tensor.cast %D : tensor<2x4xf32> to tensor<*xf32>
  call @printMemrefF32(%unranked) : (tensor<*xf32>) -> ()

  return
}

func.func private @printMemrefF32(%ptr : tensor<*xf32>)