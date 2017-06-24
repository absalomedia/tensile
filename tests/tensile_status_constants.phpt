--TEST--
Tensile\Status::CODE_* Constants
--FILE--
<?php
echo Tensile\Status::CODE_OK, "\n";
echo Tensile\Status::CODE_CANCELLED, "\n";
echo Tensile\Status::CODE_UNKNOWN, "\n";
echo Tensile\Status::CODE_INVALID_ARGUMENT, "\n";
echo Tensile\Status::CODE_DEADLINE_EXCEEDED, "\n";
echo Tensile\Status::CODE_NOT_FOUND, "\n";
echo Tensile\Status::CODE_ALREADY_EXISTS, "\n";
echo Tensile\Status::CODE_PERMISSION_DENIED, "\n";
echo Tensile\Status::CODE_RESOURCE_EXHAUSTED, "\n";
echo Tensile\Status::CODE_FAILED_PRECONDITION, "\n";
echo Tensile\Status::CODE_ABORTED, "\n";
echo Tensile\Status::CODE_OUT_OF_RANGE, "\n";
echo Tensile\Status::CODE_UNIMPLEMENTED, "\n";
echo Tensile\Status::CODE_INTERNAL, "\n";
echo Tensile\Status::CODE_UNAVAILABLE, "\n";
echo Tensile\Status::CODE_DATA_LOSS, "\n";
echo Tensile\Status::CODE_UNAUTHENTICATED, "\n";
?>
--EXPECT--
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
