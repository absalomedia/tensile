--TEST--
Tensile\Buffer::__construct method
--FILE--
<?php
$buffer = new Tensile\Buffer();
echo ($buffer->__toString() ?: "(null)"), "\n";
$buffer = new Tensile\Buffer("hello tf!!");
echo ($buffer->__toString() ?: "(null)"), "\n";

?>
--EXPECT--
(null)
hello tf!!
