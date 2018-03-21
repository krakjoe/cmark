--TEST--
CommonMark\Node\Text cached unset
--FILE--
<?php
$text = new CommonMark\Node\Text();

$f = function() use($text) {
	unset($text->literal);
};

$text->literal = "OK";

var_dump($text->literal);
$f();
var_dump($text->literal);

$text->literal = "KO";

var_dump($text->literal);
$f();
var_dump($text->literal);
?>
--EXPECT--
string(2) "OK"
NULL
string(2) "KO"
NULL
