--TEST--
CommonMark\Node\BulletList invalid isset
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

$zero = 0;

var_dump(isset($list->$zero));
?>
--EXPECT--
bool(false)
