--TEST--
CommonMark\Node\OrderedList isset start
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$f = function() use($list) {
	return isset($list->start);
};

var_dump($list->start);
var_dump($f());

$list->start = 10;

var_dump($list->start);
var_dump($f());
?>
--EXPECT--
int(0)
bool(false)
int(10)
bool(true)
