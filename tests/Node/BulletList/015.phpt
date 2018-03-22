--TEST--
CommonMark\Node\BulletList isset delimiter
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

$f = function() use($list) {
	return isset($list->delimiter);
};

var_dump($list->delimiter);
var_dump($f());

$list->delimiter = CommonMark\Node\Lists\Delimit\Period;

var_dump($list->delimiter);
var_dump($f());
?>
--EXPECT--
int(0)
bool(false)
int(1)
bool(true)
