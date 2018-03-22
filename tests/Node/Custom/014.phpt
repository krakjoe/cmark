--TEST--
CommonMark\Node\CustomBlock isset onEnter
--FILE--
<?php
$custom = new CommonMark\Node\CustomBlock;

$f = function() use($custom) {
	return isset($custom->onEnter);
};

var_dump($custom->onEnter);
var_dump($f());

$custom->onEnter = "OK";

var_dump($custom->onEnter);
var_dump($f());
?>
--EXPECT--
NULL
bool(false)
string(2) "OK"
bool(true)
