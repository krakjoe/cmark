--TEST--
CommonMark\Node\Text cached read
--FILE--
<?php
$text = new CommonMark\Node\Text();
$text->literal = "OK";

$f = function() use($text) {
	return $text->literal;
};

var_dump($f());
var_dump($f());
?>
--EXPECT--
string(2) "OK"
string(2) "OK"
