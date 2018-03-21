--TEST--
CommonMark\Node\Text isset
--FILE--
<?php
$text = new CommonMark\Node\Text();

var_dump(isset($text->literal));

$text->literal = "OK";

var_dump(isset($text->literal));
?>
--EXPECT--
bool(false)
bool(true)
