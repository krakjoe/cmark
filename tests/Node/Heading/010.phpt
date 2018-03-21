--TEST--
CommonMark\Node\Heading incorrect isset
--FILE--
<?php
$heading = new CommonMark\Node\Heading();

$zero = 0;

var_dump(isset($heading->$zero));
?>
--EXPECT--
bool(false)
