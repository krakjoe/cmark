--TEST--
CommonMark\Node\Text incorrect isset
--FILE--
<?php
$text = new CommonMark\Node\Text();

$zero = 0;

var_dump(isset($text->$zero));
?>
--EXPECT--
bool(false)
