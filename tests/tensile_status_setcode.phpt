--TEST--
Tensile\Status::setCode method
--FILE--
<?php
$status = new Tensile\Status;
$status->setCode(10, "hello tf!");
echo $status->getCode(), "\n";
echo $status->getMessage(), "\n";

$status->setCode(20);
echo $status->getCode(), "\n";
echo ($status->getMessage() ?: "null"), "\n";
?>
--EXPECT--
10
hello tf!
20
null
