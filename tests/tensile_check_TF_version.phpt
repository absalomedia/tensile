--TEST--
check bundled Tensorflow version
--SKIPIF--
<?php if (!extension_loaded("tensile")) print "skip"; ?>
--FILE--
<?php

echo version_compare(Tensile::getVersion(), '1.2.0')

?>
--EXPECT--
0
