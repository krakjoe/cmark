--TEST--
CommonMark\Node\CustomBlock isset onLeave
--FILE--
<?php
$custom = new CommonMark\Node\CustomBlock;

$f = function() use($custom) {
	return isset($custom->onLeave);
};

var_dump($custom->onLeave);
var_dump($f());

$custom->onLeave = "OK";

var_dump($custom->onLeave);
var_dump($f());
?>
--EXPECT--
NULL
bool(false)
string(2) "OK"
bool(true)
