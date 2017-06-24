--TEST--
Tensile\OperationDescription::__construct method
--FILE--
<?php
$desc = new Tensile\OperationDescription(new Tensile\Graph(), "Const", "scalar");
?>
--EXPECT--
