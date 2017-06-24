--TEST--
Tensile\OperationDescription::setAttrInt method
--FILE--
<?php
$desc = new Tensile\OperationDescription(new Tensile\Graph(), "Const", "scalar");
$desc->setAttrInt("pass", 1);
$desc->setAttrInt("pass", 2);
$desc->setAttrInt("pass", 3);
$desc->setAttrInt("pass", "1.1");

$desc->setAttrInt(new stdClass);

?>
--EXPECTF--
Warning: Tensile\OperationDescription::setAttrInt() expects exactly 2 parameters, 1 given in %s on line %d
