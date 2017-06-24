--TEST--
Example Add
--FILE--
<?php

// function scalarConst(TensorFlow $graph, $n) {
//     $tensor = new Tensile\Tensor(Tensile\DTYPE_INT32, NULL, $n); // 0 차원은 일반 상수.
//     $desc = new Tensile\OperationDescription($graph, "Const", "scalar");
//     $desc->setAttrTensor("value", $tensor, NULL);
//     $desc->setAttrType("dtype", Tensile\DTYPE_INT32);
//     return $desc->finishOperation(NULL);
// }

// $graph = new Tensile\Graph();

// scalarConst($graph, 20);

?>
--EXPECT--
