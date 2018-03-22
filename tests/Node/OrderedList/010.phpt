--TEST--
CommonMark\Node\OrderedList isset invalid
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$zero = 0;

var_dump(isset($list->$zero));
?>
--EXPECT--
bool(false)
