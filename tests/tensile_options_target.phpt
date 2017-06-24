--TEST--
Tensile\SessionOptions::setTarget method
--FILE--
<?php
$sessionOptions = new Tensile\SessionOptions();
$sessionOptions->setTarget("local");

?>
--EXPECT--
