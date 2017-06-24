--TEST--
Tensile\OperationDescription::setDevice method
--FILE--
<?php
$desc = new Tensile\OperationDescription(new Tensile\Graph(), "Const", "scalar");
$desc->setDevice("device");

?>
--EXPECT--
