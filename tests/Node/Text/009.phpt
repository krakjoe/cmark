--TEST--
CommonMark\Node\Text isset
--FILE--
<?php
$text = new CommonMark\Node\Text();

$f  = function() use($text) {
	return isset($text->literal);
};

var_dump($f());

$text->literal = "OK";

var_dump($f());
?>
--EXPECT--
bool(false)
bool(true)
