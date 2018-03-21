--TEST--
CommonMark\Node\Text cached write
--FILE--
<?php
$text = new CommonMark\Node\Text();

$f = function($value) use($text) {
	return $text->literal = $value;
};

var_dump($f("OK"));
var_dump($f("KO"));
?>
--EXPECT--
string(2) "OK"
string(2) "KO"
