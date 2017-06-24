--TEST--
Tensile\OperationDescription::setAttrTypeList method
--FILE--
<?php
$desc = new Tensile\OperationDescription(new Tensile\Graph(), "Const", "scalar");
$desc->setAttrTypeList("pass", []);
$desc->setAttrTypeList("pass", [1]);
$desc->setAttrTypeList("pass", [1, 2]);
try {
    $desc->setAttrTypeList("fail", ["string"]);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), "\n";
}
try {
    $desc->setAttrTypeList("fail", [0, 21]);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), "\n";
}

?>
--EXPECT--
dtypes must be array of integer
each dtype must be from 1 to 20
