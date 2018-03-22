--TEST--
CommonMark\Node\BulletList isset tight
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

$f = function() use($list) {
	return isset($list->tight);
};

var_dump($list->tight);
var_dump($f());

$list->tight = true;

var_dump($list->tight);
var_dump($f());
?>
--EXPECT--
bool(false)
bool(true)
bool(true)
bool(true)
