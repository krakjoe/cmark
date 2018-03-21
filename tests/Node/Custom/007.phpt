--TEST--
CommonMark\Node\Custom incorrect isset
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

$zero = 0;

var_dump(isset($block->$zero));
?>
--EXPECT--
bool(false)
