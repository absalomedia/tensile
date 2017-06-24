--TEST--
Tensile\OperationDescription::setAttrBoolList method
--FILE--
<?php
$desc = new Tensile\OperationDescription(new Tensile\Graph(), "Const", "scalar");
$desc->setAttrBoolList("pass", []);
$desc->setAttrBoolList("pass", [true]);
$desc->setAttrBoolList("pass", [false]);
$desc->setAttrBoolList("pass", [false, true]);
$desc->setAttrBoolList("pass", [true, false]);
$desc->setAttrBoolList("pass", [true, true]);
$desc->setAttrBoolList("pass", [false, false]);
try {
    $desc->setAttrBoolList("fail", [false, false, 1]);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), "\n";
}

?>
--EXPECT--
values must be array of bool
