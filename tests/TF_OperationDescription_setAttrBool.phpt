--TEST--
Tensile\OperationDescription::setAttrBool method
--FILE--
<?php
$desc = new Tensile\OperationDescription(new Tensile\Graph(), "Const", "scalar");
$desc->setAttrBool("true", true);
$desc->setAttrBool("false", false);
$desc->setAttrBool("false", "sdfasdf");
$desc->setAttrBool("false", 1);
$desc->setAttrBool("false", 2);

$desc->setAttrBool("string", new stdClass);

?>
--EXPECTF--
Warning: Tensile\OperationDescription::setAttrBool() expects parameter 2 to be boolean, object given in %s on line %d
